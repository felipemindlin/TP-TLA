%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	int integer;
	double fp_number;
	boolean boolean;
	char * var_name;
	Token token;

	/** Non-terminals. */

	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
/*
%destructor { releaseConstant($$); } <constant>
%destructor { releaseExpression($$); } <expression>
%destructor { releaseFactor($$); } <factor>
%destructor { releaseProgram($$); } <program>
*/

/** Terminals. */
%token <integer> INTEGER
%token <fp_number> FLOAT
%token <boolean> BOOLEAN
%token <var_name> IDENTIFIER

%token <token> NONE

%token <token> TAB
%token <token> COLON
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_BRACKET
%token <token> CLOSE_BRACKET
%token <token> OPEN_BRACE
%token <token> CLOSE_BRACE

%token <token> ADD
%token <token> SUB
%token <token> MUL
%token <token> DIV
%token <token> EXP
%token <token> FLOOR_DIV
%token <token> MOD

%token <token> ASSIGN
%token <token> ASSIGN_ADD
%token <token> ASSIGN_SUB
%token <token> ASSIGN_MUL
%token <token> ASSIGN_DIV
%token <token> ASSIGN_MOD
%token <token> ASSIGN_EXP
%token <token> ASSIGN_FLOOR_DIV
%token <token> ASSIGN_BITWISE_AND
%token <token> ASSIGN_BITWISE_OR
%token <token> ASSIGN_BITWISE_XOR
%token <token> ASSIGN_BITWISE_LSHIFT
%token <token> ASSIGN_BITWISE_RSHIFT
%token <token> ASSIGN_WALRUS

%token <token> COMPARISON_EQ
%token <token> COMPARISON_NEQ
%token <token> COMPARISON_GT
%token <token> COMPARISON_GTE
%token <token> COMPARISON_LT
%token <token> COMPARISON_LTE

%token <token> LOGICAL_AND
%token <token> LOGICAL_OR
%token <token> LOGICAL_NOT

%token <token> IS
%token <token> IS_NOT

%token <token> IN
%token <token> NOT_IN

%token <token> BITWISE_AND
%token <token> BITWISE_OR
%token <token> BITWISE_XOR
%token <token> BITWISE_NOT
%token <token> BITWISE_LSHIFT
%token <token> BITWISE_RSHIFT

%token <token> IF
%token <token> ELIF
%token <token> ELSE

%token <token> FOR
%token <token> WHILE
%token <token> BREAK
%token <token> CONTINUE

%token <token> UNKNOWN

/** Non-terminals. */
%type <constant> constant
%type <expression> expression
%type <factor> factor
%type <program> program

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV

%%

program: expression													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

expression: expression[left] ADD expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
	| expression[left] DIV expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, DIVISION); }
	| expression[left] MUL expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, MULTIPLICATION); }
	| expression[left] SUB expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, SUBTRACTION); }
	| factor														{ $$ = FactorExpressionSemanticAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorSemanticAction($2); }
	| constant														{ $$ = ConstantFactorSemanticAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	;

%%
