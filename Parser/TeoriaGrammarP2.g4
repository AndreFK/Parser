grammar TeoriaGrammarP2;

prog: optional_func_dec;

optional_func_dec:
	func_head body
	| func_head body optional_func_dec;

func_head: func_name param_list_opt;

func_name: func_type ID;

func_type: func_modifiers decl_type;

func_modifiers: func_mods |;

func_mods: STATIC_TKN;

decl_type:
	INT_TYPE
	| ANYTYPE_TYPE
	| BOOLEAN_TYPE
	| VOID_TYPE
	| REAL_TYPE
	| STRING_TYPE
	| DATE_TYPE;

param_list_opt: param_list |;

param_list: decl_param | param_list ',' decl_param;

decl_param: decl_type ID;

body: '{' stmt_list '}';

stmt_list: stmts |;

stmts: stmt | stmts stmt;

stmt:
	compound_stmt
	| while_stmt
	| if_stmt
	| expr_stmt
	| return_stmt;

compound_stmt: '{' stmt_list '}';

while_stmt: while_test stmt;

while_test: WHILE '(' bool_expr ')';

if_stmt: else_stmt | if_conds;

if_conds: if_cond stmt;

if_cond: IF '(' bool_expr ')';

else_stmt: else_r stmt;

else_r: if_conds ELSE;

expr_stmt: asg_stmt ';' | function ';' | eval ';';

asg_stmt: ID ASIG bool_expr | field ASIG bool_expr;

return_stmt: RETURN ';' | RETURN bool_expr ';';

bool_expr: bool_expr LOG_OP expr | expr;

expr: simple_expr REL_OP simple_expr | simple_expr;

simple_expr: simple_expr ADD_OP term | term;

term: term MULT_OP factor | factor;

factor: '(' bool_expr ')' | constant | field | function | eval;

constant:
	INT_LITERAL
	| REAL_LITERAL
	| DATE_LITERAL
	| STRING_LITERAL
	| TRUE_LITERAL
	| FALSE_LITERAL
	| qualifier ID;

field: qualifier ID | ID;

qualifier: eval PERIOD | ID PERIOD | ID DDPERIOD;

eval: eval_name par_list ')';

eval_name: ID '(';

par_list: prm_list |;

prm_list: bool_expr | prm_list ',' bool_expr;

function: ID '(' par_list ')' | qualifier ID '(' par_list ')';

COMMENT: '//' ~[\r\n]* '\r'? '\n' -> skip;
WHITESPACE: [ \t\r\n]+ -> skip;
ID: (LETTER | '_') (LETTER | DIGIT)*;
ADD_OP: '+' | '-';
MULT_OP: '*' | '/';
LOG_OP: '||' | '&&';
REL_OP: '>' | '<' | '==' | '<=' | '>=';
ASIG: ':=';
PERIOD: '.';
DDPERIOD: '::';
INCR: '++';
FALSE_LITERAL: 'false';
TRUE_LITERAL: 'true';
INT_LITERAL: (DIGIT)+;
REAL_LITERAL: (DIGIT)+ '.' (DIGIT)+;
STRING_LITERAL:
	'"' (
		LETTER
		| DIGIT
		| ' '
		| '%'
		| '@'
		| ','
		| '-'
		| '='
		| '('
		| ')'
		| '_'
	)* '"';
DATE_LITERAL:
	DIGIT DIGIT '/' DIGIT DIGIT '/' DIGIT DIGIT DIGIT DIGIT;

WHILE: 'while';
IF: 'if';
ELSE: 'else';
RETURN: 'EXIT';
INICIO: 'BEGIN';
IF_THEN: 'THEN';
DO: 'DO';
END: 'END';

SEMICOLON: ';';
PAR_OP: '(';
PAR_CL: ')';
BRACK_OP: '{';
BRACK_CL: '}';
COMA: ',';
EPSILON: 'E';

STATIC_TKN: 'static';

INT_TYPE: 'int';
ANYTYPE_TYPE: 'anytype';
BOOLEAN_TYPE: 'boolean';
VOID_TYPE: 'void';
REAL_TYPE: 'real';
STRING_TYPE: 'String';
DATE_TYPE: 'date';
fragment DIGIT: [0-9];
fragment LETTER: [a-zA-Z];
