%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	int integer;
	double fp_number;
	boolean boolean;
    char * string;
	char * var_name;
	Token token;

	/** Non-terminals. */
	Constant * constant;
	Expression * expression;
    List * list;
    List * tuple;
    Block * block;
	Conditional * conditional;
	Factor * factor;
    While * while_block;
    For * for_block;
	Program * program;
	Variable * variable;
    Object * object;
	Parameters * parameters;
	FunctionDefinition * functionDefinition;
	ClassDefinition * classDefinition;
	FunctionCall * functionCall;
	VariableCall * variableCall;
	Sentence * sentence;
	Depth * depth;

	Newline * newline;

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
%token <string> STRING

%token <var_name> IDENTIFIER
%token <var_name> BUILTIN_IDENTIFIER

%token <token> NONE

%token <token> COMMA

%token <token> NEWLINE_TOKEN
%token <token> TAB
%token <token> COLON
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_BRACKET
%token <token> CLOSE_BRACKET
%token <token> OPEN_BRACE
%token <token> CLOSE_BRACE
%token <token> DOT

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

%token <token> DEF
%token <token> RETURNS
%token <token> CLASS

%token <token> RAISE_KEYWORD_TOKEN
%token <token> TRY_KEYWORD_TOKEN
%token <token> EXCEPT_KEYWORD_TOKEN
%token <token> FINALLY_KEYWORD_TOKEN
%token <token> RETURN_KEYWORD_TOKEN
%token <token> PASS_KEYWORD_TOKEN
%token <token> YIELD_KEYWORD_TOKEN
%token <token> MATCH_KEYWORD_TOKEN
%token <token> CASE_KEYWORD_TOKEN
%token <token> TYPE_KEYWORD_TOKEN
%token <token> ASSERT_KEYWORD_TOKEN
%token <token> UNKNOWN

/** Non-terminals. */
%type <object> object
%type <constant> constant
%type <variable> variable
%type <list> list;
%type <tuple> tuple;
%type <conditional> conditional
%type <block> block
%type <for_block> for_block
%type <while_block> while_block
%type <expression> expression
%type <factor> factor
%type <program> program
%type <parameters> parameters
%type <functionDefinition> functionDefinition
%type <classDefinition> classDefinition
%type <functionCall> functionCall
%type <variableCall> variableCall
%type <sentence> sentence
%type <depth> depth
%type <newline> newline

%type <list> empty_list
%type <list> typed_list
%type <tuple> empty_tuple
%type <tuple> typed_tuple


/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 * @also see https://www.geeksforgeeks.org/precedence-and-associativity-of-operators-in-python/ for Python
 */
%right ASSIGN_WALRUS
%left  LOGICAL_OR
%left  LOGICAL_AND
%left  LOGICAL_NOT
%left  IN NOT_IN IS IS_NOT COMPARISON_LT COMPARISON_LTE COMPARISON_GT COMPARISON_GTE COMPARISON_EQ COMPARISON_NEQ
%left  BITWISE_OR
%left  BITWISE_XOR
%left  BITWISE_AND
%left  BITWISE_LSHIFT BITWISE_RSHIFT
%left  ADD SUB
%left  MUL DIV FLOOR_DIV MOD
%right BITWISE_NOT
%right EXP


%%

program: expression													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| depth sentence program
	;

block: functionDefinition[blck] COLON NEWLINE_TOKEN TAB program[prog]   { $$ = FunctionDefinitionBlockSemanticAction($blck, $prog); }
     | classDefinition[blck] COLON NEWLINE_TOKEN TAB program[prog]      { $$ = ClassDefinitionBlockSemanticAction($blck, $prog); }
     | conditional[blck] COLON NEWLINE_TOKEN TAB program[prog]          { $$ = ConditionalBlockSemanticAction($blck, $prog); }
     | while_block[blck] COLON NEWLINE_TOKEN TAB program[prog]          { $$ = ForDefinitionBlockSemanticAction($blck, $prog); }
     | for_block[blck] COLON NEWLINE_TOKEN TAB program[prog]            { $$ = WhileDefinitionBlockSemanticAction($blck, $prog); }
     ;

functionDefinition: DEF IDENTIFIER[id] OPEN_PARENTHESIS parameters[args] CLOSE_PARENTHESIS                              		{ $$ = FunctionDefinitionSemanticAction($id, $args, DATA_INFERRED, NULL); }
                  | DEF IDENTIFIER[id] OPEN_PARENTHESIS parameters[args] CLOSE_PARENTHESIS RETURNS object[retObj]   			{ $$ = FunctionDefinitionSemanticAction($id, $args, DATA_OBJECT, $retObj); }
				  ;

classDefinition: CLASS IDENTIFIER[id]                                                    		{ $$ = ClassDefinitionSemanticAction($id, NULL); }
               | CLASS IDENTIFIER[id] OPEN_PARENTHESIS object[obj] CLOSE_PARENTHESIS	        { $$ = ClassDefintionSemanticAction($id, $obj); }
               ;

conditional: conditional[left] LOGICAL_AND conditional[right]       { $$ = ConditionalBooleanSemanticAction($left, $right, LOGIC_AND); }
	| conditional[left] LOGICAL_OR conditional[right]	            { $$ = ConditionalBooleanSemanticAction($left, $right, LOGIC_OR); }
    | LOGICAL_NOT conditional[cond]                                 { $$ = ConditionalBooleanSemanticAction($cond, NULL, LOGIC_NOT); }
    | variableCall[left] LOGICAL_AND variableCall[right]            { $$ = ConditionalBooleanVariableSemanticAction($left, $right, LOGIC_AND); }
	| variableCall[left] LOGICAL_OR variableCall[right]	            { $$ = ConditionalBooleanVariableSemanticAction($left, $right, LOGIC_OR); }
    | LOGICAL_NOT variableCall[cond]                                { $$ = ConditionalBooleanVariableSemanticAction($cond, NULL, LOGIC_NOT); }
    | conditional[left] LOGICAL_AND variableCall[right]             { $$ = ConditionalBooleanAndVariableSemanticAction($right, $left, LOGIC_AND); }
	| conditional[left] LOGICAL_OR variableCall[right]	            { $$ = ConditionalBooleanSemanticAction($right, $left, LOGIC_OR); }
    | variableCall[left] LOGICAL_AND conditional[right]             { $$ = ConditionalBooleanAndVariableSemanticAction($left, $right, LOGIC_AND); }
	| variableCall[left] LOGICAL_OR conditional[right]	            { $$ = ConditionalBooleanSemanticAction($left, $right, LOGIC_OR); }
    | expression[left] COMPARISON_EQ expression[right]              { $$ = ConditionalExpressionSemanticAction($left, $right, EQUALS_COMPARISON); }
    | expression[left] COMPARISON_NEQ expression[right]             { $$ = ConditionalExpressionSemanticAction($left, $right, NOT_EQUALS_COMPARISON); }
    | expression[left] COMPARISON_GT expression[right]              { $$ = ConditionalExpressionSemanticAction($left, $right, GREATER_THAN_COMPARISON); }
    | expression[left] COMPARISON_GTE expression[right]             { $$ = ConditionalExpressionSemanticAction($left, $right, GREATER_THAN_OR_EQUALS_COMPARISON); }
    | expression[left] COMPARISON_LT expression[right]              { $$ = ConditionalExpressionSemanticAction($left, $right, LESS_THAN_COMPARISON); }
    | expression[left] COMPARISON_LTE expression[right]             { $$ = ConditionalExpressionSemanticAction($left, $right, LESS_THAN_OR_EQUALS_COMPARISON); }
    | expression[left] IN expression[right]                         { $$ = ConditionalExpressionSemanticAction($left, $right, IN_COMPARISON); }
    | expression[left] NOT_IN expression[right]                     { $$ = ConditionalExpressionSemanticAction($left, $right, NOT_IN_COMPARISON); }
    | variableCall[left] COMPARISON_EQ variableCall[right]          { $$ = ConditionalExpressionVariableSemanticAction($left, $right, EQUALS_COMPARISON); }
    | variableCall[left] COMPARISON_NEQ variableCall[right]         { $$ = ConditionalExpressionVariableSemanticAction($left, $right, NOT_EQUALS_COMPARISON); }
    | variableCall[left] COMPARISON_GT variableCall[right]          { $$ = ConditionalExpressionVariableSemanticAction($left, $right, GREATER_THAN_COMPARISON); }
    | variableCall[left] COMPARISON_GTE variableCall[right]         { $$ = ConditionalExpressionVariableSemanticAction($left, $right, GREATER_THAN_OR_EQUALS_COMPARISON); }
    | variableCall[left] COMPARISON_LT variableCall[right]          { $$ = ConditionalExpressionVariableSemanticAction($left, $right, LESS_THAN_COMPARISON); }
    | variableCall[left] COMPARISON_LTE variableCall[right]         { $$ = ConditionalExpressionVariableSemanticAction($left, $right, LESS_THAN_OR_EQUALS_COMPARISON); }
    | variableCall[left] IN variableCall[right]                     { $$ = ConditionalExpressionVariableSemanticAction($left, $right, IN_COMPARISON); }
    | variableCall[left] NOT_IN variableCall[right]                 { $$ = ConditionalExpressionVariableSemanticAction($left, $right, NOT_IN_COMPARISON); }
    | variableCall[left] COMPARISON_EQ expression[right]            { $$ = ConditionalExpressionAndVariableSemanticAction($left, $right, EQUALS_COMPARISON); }
    | variableCall[left] COMPARISON_NEQ expression[right]           { $$ = ConditionalExpressionAndVariableSemanticAction($left, $right, NOT_EQUALS_COMPARISON); }
    | variableCall[left] COMPARISON_GT expression[right]            { $$ = ConditionalExpressionAndVariableSemanticAction($left, $right, GREATER_THAN_COMPARISON); }
    | variableCall[left] COMPARISON_GTE expression[right]           { $$ = ConditionalExpressionAndVariableSemanticAction($left, $right, GREATER_THAN_OR_EQUALS_COMPARISON); }
    | variableCall[left] COMPARISON_LT expression[right]            { $$ = ConditionalExpressionAndVariableSemanticAction($left, $right, LESS_THAN_COMPARISON); }
    | variableCall[left] COMPARISON_LTE expression[right]           { $$ = ConditionalExpressionAndVariableSemanticAction($left, $right, LESS_THAN_OR_EQUALS_COMPARISON); }
    | variableCall[left] IN expression[right]                       { $$ = ConditionalExpressionAndVariableSemanticAction($left, $right, IN_COMPARISON); }
    | variableCall[left] NOT_IN expression[right]                   { $$ = ConditionalExpressionAndVariableSemanticAction($left, $right, NOT_IN_COMPARISON); }
    | expression[left] COMPARISON_EQ variableCall[right]            { $$ = ConditionalExpressionAndVariableSemanticAction($right, $left, EQUALS_COMPARISON); }
    | expression[left] COMPARISON_NEQ variableCall[right]           { $$ = ConditionalExpressionAndVariableSemanticAction($right, $left, NOT_EQUALS_COMPARISON); }
    | expression[left] COMPARISON_GT variableCall[right]            { $$ = ConditionalExpressionAndVariableSemanticAction($right, $left, GREATER_THAN_COMPARISON); }
    | expression[left] COMPARISON_GTE variableCall[right]           { $$ = ConditionalExpressionAndVariableSemanticAction($right, $left, GREATER_THAN_OR_EQUALS_COMPARISON); }
    | expression[left] COMPARISON_LT variableCall[right]            { $$ = ConditionalExpressionAndVariableSemanticAction($right, $left, LESS_THAN_COMPARISON); }
    | expression[left] COMPARISON_LTE variableCall[right]           { $$ = ConditionalExpressionAndVariableSemanticAction($right, $left, LESS_THAN_OR_EQUALS_COMPARISON); }
    | expression[left] IN variableCall[right]                       { $$ = ConditionalExpressionAndVariableSemanticAction($right, $left, IN_COMPARISON); }
    | expression[left] NOT_IN variableCall[right]                   { $$ = ConditionalExpressionAndVariableSemanticAction($right, $left, NOT_IN_COMPARISON); }
    | expression                                                    { $$ = ConditionalSingleExpressionSemanticAction($1); }
    | object                                                        { $$ = ConditionalSingleObjectSemanticAction($1); }
    | object[left] IS object[right]                                 { $$ = ConditionalObjectSemanticAction($left, $right, IS_COND); }
    | object[left] IS_NOT object[right]                             { $$ = ConditionalObjectSemanticAction($left, $right, IS_NOT_COND); }
    | variableCall[left] IS variableCall[right]                     { $$ = ConditionalObjectVariableSemanticAction($left, $right, IS_COND); }
    | variableCall[left] IS_NOT variableCall[right]                 { $$ = ConditionalObjectVariableSemanticAction($left, $right, IS_NOT_COND); }
    | variableCall[left] IS object[right]                           { $$ = ConditionalObjectAndVariableSemanticAction($left, $right, IS_COND); }
    | variableCall[left] IS_NOT object[right]                       { $$ = ConditionalObjectAndVariableSemanticAction($left, $right, IS_NOT_COND); }
    | object[left] IS variableCall[right]                           { $$ = ConditionalObjectAndVariableSemanticAction($right, $left, IS_COND); }
    | object[left] IS_NOT variableCall[right]                       { $$ = ConditionalObjectAndVariableSemanticAction($right, $left, IS_NOT_COND); }
    | variableCall[var]                                             { $$ = ConditionalVariableSemanticAction($var);}
	;

while_block: conditional[cond]                                      { $$ = WhileBlockSemanticAction($cond); }

for_block: expression[left] IN expression[right]                    { $$ = ForFactorBlockSemanticAction($left, $right); }
         | variableCall[left] IN variableCall[right]                { $$ = ForVariableBlockSemanticAction($left, $right); }
         | variableCall[left] IN factor[right]                      { $$ = ForFactorAndVariableBlockSemanticAction($left, $right, VARIABLE_ON_THE_LEFT); }
         | factor[left] IN variableCall[right]                      { $$ = ForFactorAndVariableBlockSemanticAction($right, $left, FACTOR_ON_THE_LEFT); }

expression: expression[left] ADD expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
	| expression[left] DIV expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, DIVISION); }
	| expression[left] MUL expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, MULTIPLICATION); }
	| expression[left] SUB expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, SUBTRACTION); }
	| expression[left] EXP expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, EXPONENTIATION); }
	| expression[left] FLOOR_DIV expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, TRUNCATED_DIVISION); }
	| expression[left] MOD expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, MODULO); }
	| expression[left] BITWISE_AND expression[right]				{ $$ = ArithmeticExpressionSemanticAction($left, $right, BIT_ARITHMETIC_AND); }
	| expression[left] BITWISE_OR expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, BIT_ARITHMETIC_OR); }
	| expression[left] BITWISE_XOR expression[right]				{ $$ = ArithmeticExpressionSemanticAction($left, $right, BIT_ARITHMETIC_XOR); }
	| expression[left] BITWISE_LSHIFT expression[right]				{ $$ = ArithmeticExpressionSemanticAction($left, $right, BIT_ARITHMETIC_LEFT_SHIFT); }
	| expression[left] BITWISE_RSHIFT expression[right]				{ $$ = ArithmeticExpressionSemanticAction($left, $right, BIT_ARITHMETIC_RIGHT_SHIFT); }
	| factor        												{ $$ = FactorExpressionSemanticAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorSemanticAction($2); }
	| constant														{ $$ = ConstantFactorSemanticAction($1); }
    | variableCall                                                  { $$ = VariableCallFactorSemanticAction($1); }
    | methodCall                                                    { $$ = MethodCallFactorSemanticAction($1); }
    | functionCall                                                  { $$ = FunctionCallFactorSemanticAction($1); }
    | fieldGetter                                                   { $$ = FieldGetterFactorSemanticAction($1); }
    | object                                                        { $$ = ObjectFactorSemanticAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	| BOOLEAN														{ $$ = BooleanConstantSemanticAction($1); }
    | STRING                                                        { $$ = StringConstantSemanticAction($1); }
    | FLOAT                                                         { $$ = FloatConstantSemanticAction($1); }
	;

sentence: DEF IDENTIFIER[id] OPEN_PARENTHESIS parameters[params] CLOSE_PARENTHESIS COLON newline			{ $$ = FunctionDefinitionSentenceSemanticAction($id, $params, FUNCTION_DEFINITION); }
	| functionCall newline																					{ $$ = FunctionCallSentenceSemanticAction($1, FUNCTION_CALL); }

variableCall: IDENTIFIER[id]										{ $$ = VariableCallSemanticAction($id); }

list: empty_list                                                    { $$ = EmptyListSemanticAction(); }
    | typed_list                                                    { $$ = TypedListSemanticAction($1); }
    | OPEN_BRACKET parameters[params] CLOSE_BRACKET                 { $$ = ListSemanticAction($params); }
    ;


empty_list: OPEN_BRACKET CLOSE_BRACKET                              { $$ = EmptyListSemanticAction(); }
typed_list: OPEN_BRACKET object[id] CLOSE_BRACKET                   { $$ = TypedDefinitionListSemanticAction($id); }

tuple: empty_tuple                                                      { $$ = EmptyTupleSemanticAction(); }
     | typed_tuple                                                      { $$ = TypedTupleSemanticAction($1) }
     | OPEN_PARENTHESIS parameters[params] CLOSE_PARENTHESIS            { $$ = TupleSemanticAction($params); }

empty_tuple: OPEN_PARENTHESIS CLOSE_PARENTHESIS                         { $$ = EmptyTupleSemanticAction(); }
typed_tuple: OPEN_PARENTHESIS BUILTIN_IDENTIFIER[id] CLOSE_PARENTHESIS  { $$ = TypedTupleSemanticAction($id); }

functionCall: IDENTIFIER[id] OPEN_PARENTHESIS parameters[params] CLOSE_PARENTHESIS 	{ $$ = FunctionCallSemanticAction($id, $params); }
	        ;

object: BUILTIN_IDENTIFIER                                          { $$ = BuiltInObjectSemanticAction($1); }
      | IDENTIFIER[id]                                              { $$ = ObjectSemanticAction($id); }
      | tuple                                                       { $$ = ListObjectSemanticAction($1); }
      | list                                                        { $$ = TupleObjectSemanticAction($1); }
      ;

methodCall: object[obj] DOT functionCall[func]                      { $$ = ObjectMethodCallSemanticAction($obj, $func, OBJECT_TRIGGER); }
          | variableCall[var] DOT functionCall[func]                { $$ = VariableMethodCallSemanticAction($var, $func, VARIABLE_TRIGGER); }
          ;

fieldGetter: object[obj] DOT variableCall[field]                    { $$ = ObjectFieldGetterSemanticAction($obj, $field); }
          | variableCall[var] DOT variableCall[field]               { $$ = VariableFieldGetterSemanticAction($obj, $field)}
          ;


parameters: %empty												    { $$ = ParametersSemanticAction(NULL, NULL, EMPTY); }
	      | expression[left] COMMA parameters[right]				{ $$ = ParametersSemanticAction($left, $right, NOT_FINAL); }
	      | expression[left]										{ $$ = ParametersSemanticAction($left, NULL, FINAL); }
          ;

variable: IDENTIFIER[id] ASSIGN expression[fact]                    { $$ = ExpressionVariableSemanticAction($id, $fact);}
        | IDENTIFIER[id] ASSIGN functionCall[fcall]                 { $$ = FunctionCallVariableSemanticAction($id, $fcall); }
        | IDENTIFIER[id] ASSIGN methodCall[method]                  { $$ = MethodCallVariableSemanticAction($id, $method); }
        | IDENTIFIER[id] ASSIGN fieldGetter[field]                  { $$ = FieldGetterVariableSemanticAction($id, $method); }
        | IDENTIFIER[id] ASSIGN object[obj]                         { $$ = ObjectVariableSemanticAction($id, $obj); }
        | IDENTIFIER[id] ASSIGN variableCall[var]                   { $$ = VariableCallVariableSemanticAction($id, $var); }

depth: %empty														{ $$ = DepthSemanticAction(END_DEPTH); }
	| TAB depth														{ $$ = DepthSemanticAction(TAB_DEPTH); }

newline: NEWLINE_TOKEN												{ $$ = NewlineSemanticAction(FINAL_NEWLINE); }

%%

	/* | FLOAT 														{ $$ = FloatConstantSemanticAction($1); }
	| BOOLEAN														{ $$ = BooleanConstantSemanticAction($1); } */

/**
*
	  expression[left] ASSIGN expression[right]						{ $$ = AssignmentExpressionSemanticAction($left, $right, ASSIGNMENT); }
	| expression[left] ASSIGN_ADD expression[right]					{ $$ = AssignmentExpressionSemanticAction($left, $right, ADDITION_ASSIGNMENT); }
	| expression[left] ASSIGN_SUB expression[right]					{ $$ = AssignmentExpressionSemanticAction($left, $right, SUBTRACTION_ASSIGNMENT); }
	| expression[left] ASSIGN_MUL expression[right]					{ $$ = AssignmentExpressionSemanticAction($left, $right, MULTIPLICATION_ASSIGNMENT); }
	| expression[left] ASSIGN_DIV expression[right]					{ $$ = AssignmentExpressionSemanticAction($left, $right, DIVISION_ASSIGNMENT); }
	| expression[left] ASSIGN_MOD expression[right]					{ $$ = AssignmentExpressionSemanticAction($left, $right, MODULO_ASSIGNMENT); }
	| expression[left] ASSIGN_EXP expression[right]					{ $$ = AssignmentExpressionSemanticAction($left, $right, EXPONENTIATION_ASSIGNMENT); }
	| expression[left] ASSIGN_FLOOR_DIV expression[right]			{ $$ = AssignmentExpressionSemanticAction($left, $right, TRUNCATED_DIVISION_ASSIGNMENT); }
	| expression[left] ASSIGN_BITWISE_AND expression[right]			{ $$ = AssignmentExpressionSemanticAction($left, $right, BITWISE_AND_ASSIGNMENT); }
	| expression[left] ASSIGN_BITWISE_OR expression[right]			{ $$ = AssignmentExpressionSemanticAction($left, $right, BITWISE_OR_ASSIGNMENT); }
	| expression[left] ASSIGN_BITWISE_XOR expression[right]			{ $$ = AssignmentExpressionSemanticAction($left, $right, BITWISE_XOR_ASSIGNMENT); }
	| expression[left] ASSIGN_BITWISE_LSHIFT expression[right]		{ $$ = AssignmentExpressionSemanticAction($left, $right, BITWISE_LEFT_SHIFT_ASSIGNMENT); }
	| expression[left] ASSIGN_BITWISE_RSHIFT expression[right]		{ $$ = AssignmentExpressionSemanticAction($left, $right, BITWISE_RIGHT_SHIFT_ASSIGNMENT); }
	| expression[left] ASSIGN_WALRUS expression[right]				{ $$ = AssignmentExpressionSemanticAction($left, $right, RETURNED_ASSIGNMENT); }
	| expression[left] COMPARISON_EQ expression[right]				{ $$ = ComparisonExpressionSemanticAction($left, $right, EQUALS_COMPARISON); }
	| expression[left] COMPARISON_NEQ expression[right]				{ $$ = ComparisonExpressionSemanticAction($left, $right, NOT_EQUALS_COMPARISON); }
	| expression[left] COMPARISON_GT expression[right]				{ $$ = ComparisonExpressionSemanticAction($left, $right, GREATER_THAN_COMPARISON); }
	| expression[left] COMPARISON_GTE expression[right]				{ $$ = ComparisonExpressionSemanticAction($left, $right, GREATER_THAN_OR_EQUALS_COMPARISON); }
	| expression[left] COMPARISON_LT expression[right]				{ $$ = ComparisonExpressionSemanticAction($left, $right, LESS_THAN_COMPARISON); }
	| expression[left] COMPARISON_LTE expression[right]				{ $$ = ComparisonExpressionSemanticAction($left, $right, LESS_THAN_OR_EQUALS_COMPARISON); }
*/
