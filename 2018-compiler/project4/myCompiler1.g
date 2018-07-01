grammar myparser;

options {
  language = Java;
}

program
    : {System.out.println("program");} function_definition+
    ;

function_definition
    : {System.out.println("func_def");} declaration '(' declaration_list ')' compound_statement
    ;

declaration_list
    :
    | {System.out.println("declar_list");} declaration (',' declaration)*
    ;

argument_expr_list
    : {System.out.println("argu_list");} assignment_expression (',' assignment_expression)*
    ;

statement_list
    : {System.out.println("stmt_list");} statement+
    ;

statement
    : {System.out.println("statement");} declaration_statement
    | {System.out.println("statement");} expression_statement
    | {System.out.println("statement");} compound_statement
    | {System.out.println("statement");} selection_statement
    | {System.out.println("statement");} iteration_statement
    | {System.out.println("statement");} jump_statement
    ;

declaration_statement
    : {System.out.println("declar_stmt");} declaration ';'
    ;

expression_statement
    : {System.out.println("expr_stmt");} ';'
    | {System.out.println("expr_stmt");} expression ';'
    ;

compound_statement
    : {System.out.println("comp_stmt");} '{' statement_list '}'
    ;

selection_statement
    : {System.out.println("sele_stmt");} 'if' '(' expression ')' statement (('else')=> 'else' statement)?
    ;

iteration_statement
    : {System.out.println("iter_stmt");} 'while' '(' expression ')' statement
    | {System.out.println("iter_stmt");} 'for' '(' expression_statement expression_statement expression? ')' statement
    ;

jump_statement
    : {System.out.println("jump_stmt");} 'continue' ';'
    | {System.out.println("jump_stmt");} 'break' ';'
    | {System.out.println("jump_stmt");} 'return' ';'
    | {System.out.println("jump_stmt");} 'return' expression ';'
    ;

declaration
    : {System.out.println("declaration");} type ID
    ;

type
    : {System.out.println("type(void)");} 'void'
    | {System.out.println("type(int )");} 'int'
    | {System.out.println("type(char)");} 'char'
    | {System.out.println("type(float");} 'float'
    ;

expression
    : {System.out.println("expression");} assignment_expression
    ;

assignment_expression
    : {System.out.println("assign_expr");} ID ASSIGN_OP relational_expr
    | {System.out.println("assign_expr");} relational_expr
    ;

relational_expr
    : {System.out.println("rela_expr");} additive_expr ( RELATION_OP  additive_expr)?
    ;

additive_expr
    : {System.out.println("addi_expr");} multiplicative_expr ( ADDITIVE_OP  multiplicative_expr)*
    ;

multiplicative_expr
    : {System.out.println("mult_expr");} postfix_expr ( MULTIPLI_OP  postfix_expr)*
    ;

postfix_expr
    : {System.out.println("post_expr");} primary_expr ('(' argument_expr_list ')')?
    ;

primary_expr
    : {System.out.println("prim_expr");} ID
    | {System.out.println("prim_expr");} LITERAL
    | {System.out.println("prim_expr");} constant
    | {System.out.println("prim_expr");} '(' additive_expr ')'
    ;

constant
    : {System.out.println("constant");} DEC_NUM
    | {System.out.println("constant");} FLOAT_NUM
    ;

RELATION_OP : '<' | '<=' | '==' | '>=' | '>' | '!=' ;
ASSIGN_OP   : '=' ;
ADDITIVE_OP : '+' | '-' ;
MULTIPLI_OP : '*' | '/' | '%' ;
//LOGIC_OP  : '!' | '&&' | '||';

DEC_NUM     : ('0' | ('1'..'9')(DIGIT)*) ;
FLOAT_NUM   : DEC_NUM '.' (DIGIT)+ ;
ID          : {System.out.println("ID");} (LETTER)(LETTER | DIGIT)*;
LITERAL     : '"' (.)* '"';
//LITERAL     : '"' ~('\n'|'\r')* '"';
COMMENT     : '/*' (options{greedy=false;}: .)* '*/' {$channel=HIDDEN;};
WS          : (' ' | '\r' | '\t' | '\n') {$channel=HIDDEN;};

fragment DIGIT  : '0'..'9';
fragment LETTER : 'a'..'z' | 'A'..'Z' | '_';

