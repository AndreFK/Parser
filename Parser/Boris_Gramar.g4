PROGRAM: OPTIONAL_FDEF 

OPTIONAL_FDEF: FDEF | OPTIONAL_FDEF FDEF 

FDEF: FHEAD BODY 

FHEAD: FNAME '(' PARAM_LIST_OPT ')' 

FNAME: FTYPE id 

FTYPE: FMODIFIERS DECL_TYPE 

FMODIFIERS: static | empty 

DECL_TYPE: 
		int
		| anytype
		| boolean
		| void
		| real
		| string
		| date 
		
PARAM_LIST_OPT: 
		PARAM_LIST
		| empty 

PARAM_LIST: 
		DECL_PARAM
		| PARAM_LIST ',' DECL_PARAM 
		
DECL_PARAM: DECL_TYPE id 

BODY: COMPOUND_STMT 

STMT_LIST_OPT: STMT_LIST | empty 

STMT_LIST: STMT | STMT_LIST STMT 

STMT: COMPOUND_STMT | WHILE_STMT | IF_STMT | EXPR_STMT | RETURN_STMT 

COMPOUND_STMT: '{' STMT_LIST_OPT '}' 

WHILE_STMT: 'while' '(' BEXPR ')' STMT

IF_STMT: 'if' '(' BEXPR ')' STMT ELSE_STMT 

ELSE_STMT: 'else' STMT | empty 

EXPR_STMT: ASSIGN_STMT ';' | FUNCTION ';' | EVAL ';'

ASSIGN_STMT: 'id' '=' BEXPR | FIELD '=' BEXPR 

RETURN_STMT: 'return' ';' | 'return' BEXPR ';'

BEXPR: 
	BEXPR '<' EXPR | 
	BEXPR '<=' EXPR | 
	BEXPR '>=' EXPR | 
	BEXPR '>' EXPR | 
	BEXPR '==' EXPR | 
	EXPR 
	
EXPR: 
	EXPR '+' TERM |
	EXPR '-' TERM |
	EXPR '||' TERM |
	TERM

TERM: 
	TERM '/' FACTOR |
	TERM '*' FACTOR |
	TERM '&&' FACTOR |
	FACTOR 
	
FACTOR: CONSTANT | FIELD | FUNCTION | EVAL | '(' BEXPR ')' 

CONSTANT: 
	int_literal | 
	real_literal | 
	date_literal | 
	string_literal | 
	BOOLCONST | 
	QUALIFIER 'id' 
	
BOOLCONST: 'true' | 'false' 

FIELD: QUALIFIER 'id' | 'id' 

QUALIFIER: EVAL ':' | 'id' ':' | 'id' '::' 

EVAL: 'id' '(' PAR_LIST ')' 

PAR_LIST: PRM_LIST | empty 

PRM_LIST: BEXPR | PRM_LIST ',' BEXPR 

FUNCTION: 'id' '(' PAR_LIST ')' | QUALIFIER 'id' '(' PAR_LIST')'