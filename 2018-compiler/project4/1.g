grammar myCompiler;

options {
    language = Java;
}

@header {
    // import packages here.
    import java.util.HashMap;
    import java.util.ArrayList;
}

@members {
    boolean TRACEON = false;
    HashMap<String,Integer> symtab = new HashMap<String,Integer>();
    int labelCount = 0;

    public enum TypeInfo {
        STRINGCONSTANT,
        INTEGER,
		FLOAT,
		UNKNOWN,
		NO_EXIST,
		ERROR
    }

    /* attr_type:
       1 => integer,
       2 => float,
       3 => String constant,
       -1 => do not exist,
       -2 => error
     */

    List<String> DataCode = new ArrayList<String>();
    List<String> TextCode = new ArrayList<String>();

    public static register reg = new register(0, 10);

    /*
     * Output prologue.
     */
    void prologue(String id)
    {
   	   TextCode.add("\n\n/* Text section */");
       TextCode.add("\t.section .text");
       TextCode.add("\t.global " + id);
       TextCode.add("\t.type " + id + ",@function");
       TextCode.add(id + ":");

       /* Follow x86 calling convention */
       TextCode.add("\t pushq \%rbp");
       TextCode.add("\t movq \%rsp,\%rbp");
       TextCode.add("\t pushq \%rbx"); //callee saved registers.
       TextCode.add("\t pushq \%r12"); //callee saved registers.
       TextCode.add("\t pushq \%r13"); //callee saved registers.
       TextCode.add("\t pushq \%r14"); //callee saved registers.
       TextCode.add("\t pushq \%r15"); //callee saved registers.
       TextCode.add("\t subq $8,\%rsp\n"); // aligned 16-byte boundary.
    }

    /*
     * Output epilogue.
     */
    void epilogue()
    {
       /* handle epilogue */

       /* Follow x86 calling convention */
       TextCode.add("\n\t addq $8,\%rsp");
       TextCode.add("\t popq \%r15");
       TextCode.add("\t popq \%r14");
       TextCode.add("\t popq \%r13");
       TextCode.add("\t popq \%r12");
       TextCode.add("\t popq \%rbx");
       TextCode.add("\t popq \%rbp");
	     TextCode.add("\t ret");
    }


    /* Generate a new label */
    String newLabel()
    {
       labelCount ++;
       return (new String("L")) + Integer.toString(labelCount);
    }


    public List<String> getDataCode()
    {
       return DataCode;
    }

    public List<String> getTextCode()
    {
       return TextCode;
    }
}

program
    : function_definition+
    ;

function_definition
    : declaration '(' declaration_list ')' {prologue($declaration.text);} compound_statement {epilogue();}
    ;

declaration_list
    :
    | declaration (',' declaration)*
    ;

argument_expr_list
    : assignment_expression (',' assignment_expression)*
    ;

statement_list
    : statement+
    ;

statement
    : declaration_statement
    | expression_statement
    | compound_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    ;

declaration_statement
    : declaration ';'
    ;

expression_statement
    : ';'
    | expression ';'
    ;

compound_statement
    : '{' statement_list '}'
    ;

selection_statement
    : 'if' '(' expression ')' statement (('else')=> 'else' statement)?
    ;

iteration_statement
    : 'while' '(' expression ')' statement
    | 'for' '(' expression_statement expression_statement expression? ')' statement
    ;

jump_statement
    : 'continue' ';'
    | 'break' ';'
    | 'return' ';'
    | 'return' expression ';'
    ;

declaration
    : type ID
        {
            if (symtab.containsKey($ID.text)) {
                System.out.println("Type Error: " + $ID.start.getLine() + ": Redeclared identifier.");
            } else {
                symtab.put($ID.text, $type.attr_type);
            }
            switch ($type.attr_type) {
            case 1:
                DataCode.add("\t .common " + $ID.text + ",4,4\n");
                break;
            case 2:
                DataCode.add("\t .common " + $ID.text + ",4,4\n");
                break;
            default:
            }
        }
    ;

type returns [int attr_type]
    : 'void'    {$attr_type = 0;}
    | 'int'     {$attr_type = 1;}
    | 'char'    {$attr_type = 2;}
    | 'float'   {$attr_type = 3;}
    ;

expression returns [int attr_type, int reg_num, String str]
    : assignment_expression
        {
            $attr_type = $assignment_expression.attr_type;
            $reg_num = $assignment_expression.reg_num;
            $str = $assignment_expression.str;
        }
    ;

assignment_expression returns [int attr_type, int reg_num, String str]
    : ID ASSIGN_OP additive_expr
        {
            if (symtab.containsKey($ID.text)) {
                $attr_type = symtab.get($ID.text);
            } else {
                // add codes to report and handle this error
                System.out.println("Error: " + $ID.start.getLine() + ": variable undefined.");
                $attr_type = -2;
            }

            if ($attr_type != $additive_expr.attr_type) {
                System.out.println("Type Erro: " + $additive_expr.start.getLine() + ": Type mismatch for the two side operands in an assignment statement.");
                $attr_type = -2;
            }

            TextCode.add("\t movl " + "\%" + $additive_expr.reg_num + "," + $ID.text + "(\%rip)");
        }
    | additive_expr
        {
            $attr_type = $additive_expr.attr_type;
            $reg_num = $additive_expr.reg_num;
            $str = $additive_expr.str;
        }
    ;

/*
relational_expr
    : additive_expr ( RELATION_OP  additive_expr)?
    ;
*/

additive_expr returns [int attr_type, int reg_num, String str]
    : a = multiplicative_expr
	        {
	            $attr_type = $a.attr_type;
                $reg_num = $a.reg_num;
                $str = $a.str;
            }
        ( '+' b = multiplicative_expr
            {
	            if ($a.attr_type != $b.attr_type) {
			        System.out.println("Type Error: " + $a.start.getLine() + ": Type mismatch for the operator + in an expression.");
                    $attr_type = -2;
                }

                /* code generation */
                TextCode.add("\t addl " + "\%" + $b.reg_num + ", \%" + $reg_num);
            }
        | '-' c = multiplicative_expr
            {
                if ($a.attr_type != $c.attr_type) {
                    System.out.println("Type Error: " + $a.start.getLine() + ": Type mismatch for the operator + in an expression.");
                    $attr_type = -2;
                }
                // verify it
                TextCode.add("\t sub " + "\%" + $c.reg_num + ", \%" + $reg_num);
            }
        )*
    ;

multiplicative_expr returns [int attr_type, int reg_num, String str]
    : a = postfix_expr //( MULTIPLI_OP  b = postfix_expr)*
            {
                 $attr_type = $a.attr_type;
                 $reg_num = $a.reg_num;
                 $str = $a.str;
            }
        ( '*' b = postfix_expr
            {
                if ($a.attr_type != $b.attr_type) {
                    System.out.println("Type Error: " + $a.start.getLine() + ": Type mismatch for the operator + in an expression.");
                    $attr_type = -2;
                }
                TextCode.add("\t mulx " + "\%" + $b.reg_num + ", \%" + $reg_num); // verify it
            }
        | '/' c = postfix_expr
            // improve it
        )*
    ;

postfix_expr returns [int attr_type, int reg_num, String str]
    : primary_expr ('(' argument_expr_list ')')? // improve it
	  {
	     $attr_type = $primary_expr.attr_type;
	     $reg_num = $primary_expr.reg_num;
	     $str = $primary_expr.str;
	  }
    ;

primary_expr returns [int attr_type, int reg_num, String str]
    : ID
        {
            //$attr_type = symtab.get($ID.text);  // fix it
            $str = null;
            $reg_num = reg.get();
            TextCode.add("\t movl " + $ID.text + "(\%rip), \%" + $reg_num); // does it work?
        }
    | LITERAL
        {
            $attr_type = 2;
            $str = $LITERAL.text;
            $reg_num = reg.get();
            //TextCode.add("\t movl " + $LITERAL // fix it
        }
    | constant
        {
            $attr_type = $constant.attr_type;
            $str = $constant.str;
            $reg_num = $constant.reg_num;
        }
    | '(' additive_expr ')'
        // fix it: add back
    /*
        {
            $attr_type = $additive_expr.attr_type;
            $str = $additive_expr.str;
            $reg_num = $additive_expr.reg_num;
        }
        */
    ;

constant returns [int attr_type, int reg_num, String str]
    : DEC_NUM
        {
            $attr_type = 1;
            $str = null;

            /* code generation */
            $reg_num = reg.get();
            TextCode.add("\t movl" + "\$" + $DEC_NUM.text + ", \%" + $reg_num);
        }
    | FLOAT_NUM
        {
            /* fix it */
            $attr_type = 3;
            $str = null;
            $reg_num = reg.get();
            TextCode.add("\t movl " + "\$" + $FLOAT_NUM.text + ", \%" + $reg_num);
        }
    ;

RELATION_OP : '<' | '<=' | '==' | '>=' | '>' | '!=' ;
ASSIGN_OP   : '=' ;
//ADDITIVE_OP : '+' | '-' ;
//MULTIPLI_OP : '*' | '/' | '%' ;
//LOGIC_OP  : '!' | '&&' | '||';

DEC_NUM     : ('0' | ('1'..'9')(DIGIT)*) ;
FLOAT_NUM   : DEC_NUM '.' (DIGIT)+ ;
ID          : (LETTER)(LETTER | DIGIT)*;
LITERAL     : '"' (.)* '"';
//LITERAL     : '"' ~('\n'|'\r')* '"';
COMMENT     : '/*' (options{greedy=false;}: .)* '*/' {$channel=HIDDEN;};
WS          : (' ' | '\r' | '\t' | '\n') {$channel=HIDDEN;};

fragment DIGIT  : '0'..'9';
fragment LETTER : 'a'..'z' | 'A'..'Z' | '_';

