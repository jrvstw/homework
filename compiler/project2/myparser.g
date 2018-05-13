grammar myparser;

options {
  language = Java;
}


/*----------------------*/
/*   Parser Section     */
/*----------------------*/

//program: preprocess statement ;
//preprocess: (include | define) preprocess | ;
//include: '#include'

//program: functions ;

//functions: function WS functions | ;

//function: TYPE WS ID '(' declarations ')' WS '{' WS statements WS '}' ;

//declarations: declaration declarations2 ;
//declarations2: ',' WS declaration declarations2 | ;
//declaration: TYPE ' ' ID ;

//expressions: expression WS expressions | ;

function_definition
    : type ID '(' declaration
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
    ;

type
    : 'void'
    | 'int'
    | 'char'
    | 'float'
    ;

expression
    : assignment_expression
    ;

assignment_expression
    : ID ASSIGN_OP relational_expr
    | relational_expr
    ;

relational_expr
    : additive_expr ( RELATION_OP  additive_expr)?
    ;

additive_expr
    : multiplicative_expr ( ADDITIVE_OP  multiplicative_expr)*
    ;

multiplicative_expr
    : primary_expr ( MULTIPLI_OP  primary_expr)*
    ;

primary_expr
    : ID
    | constant
    | '(' additive_expr ')'
    ;

constant
    : DEC_NUM
    | FLOAT_NUM
    ;

/*----------------------*/
/*  Compound Operators  */
/*----------------------*/

RELATION_OP : '<' | '<=' | '==' | '>=' | '>' | '!=' ;
ASSIGN_OP   : '=' ;
ADDITIVE_OP : '+' | '-' ;
MULTIPLI_OP : '*' | '/' | '%' ;
//LOGIC_OP  : '!' | '&&' | '||';

DEC_NUM     : ('0' | ('1'..'9')(DIGIT)*) ;
FLOAT_NUM   : DEC_NUM '.' (DIGIT)+ ;
ID          : (LETTER)(LETTER | DIGIT)*;
LITERAL     : '"' ~('\n'|'\r')* '"';
COMMENT     : '/*' (options{greedy=false;}: .)* '*/' {$channel=HIDDEN;};
WS          : (' ' | '\r' | '\t' | '\n') {$channel=HIDDEN;};

fragment DIGIT  : '0'..'9';
fragment LETTER : 'a'..'z' | 'A'..'Z' | '_';

