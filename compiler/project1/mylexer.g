lexer grammar mylexer;

options {
  language = Java;
}

/*----------------------*/
/*   Reserved Keywords  */
/*----------------------*/

VOID_TYPE   : 'void';
INT_TYPE    : 'int';
CHAR_TYPE   : 'char';
FLOAT_TYPE  : 'float';
IF_         : 'if';
ELSE_       : 'else';
WHILE_      : 'while';

RETURN_     : 'return';
CONTINUE_   : 'continue';
BREAK_      : 'break';

/*----------------------*/
/*  Compound Operators  */
/*----------------------*/

EQ_OP : '==';
LE_OP : '<=';
GE_OP : '>=';
NE_OP : '!=';

LS_OP : '<';
GT_OP : '>';

ASSIGN      : '=';
OPERATOR    : '+' | '-' | '*' | '/';

SEMICOLON   : ';';
COMA        : ',';
BRACKLETS   : '{' | '}' | '[' | ']' | '(' | ')' | '<' | '>';
WS          : (' ' | '\r' | '\t' | '\n')+;

DEC_NUM     : ('0' | ('1'..'9')(DIGIT)*);
ID          : (LETTER)(LETTER | DIGIT)*;
FLOAT_NUM   : FLOAT_NUM1 | FLOAT_NUM2 | FLOAT_NUM3;
COMMENT     : '/*' (options{greedy=false;}: .)* '*/';
LITERAL     : '"' (.)* '"';

fragment LETTER : 'a'..'z' | 'A'..'Z' | '_';
fragment DIGIT  : '0'..'9';
fragment FLOAT_NUM1: (DIGIT)+'.'(DIGIT)*;
fragment FLOAT_NUM2: '.'(DIGIT)+;
fragment FLOAT_NUM3: (DIGIT)+;

