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
	Program * program;
	Variable * variable;
	Parameters * parameters;
	FunctionCall * functionCall;
	MethodCall * methodCall;
	FieldGetter * fieldGetter;
	Object * object;
	Tuple * tuple;
	List * list;
	VariableCall * variableCall;
	Sentence * sentence;
    Block * block;
    FunctionDefinition * functionDefinition;
    ClassDefinition * classDefinition;
	Depth * depth;
	Newline * newline;
	WhileBlock * whileBlock;
    ForBlock * forBlock;
    ConditionalBlock * conditionalBlock;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */


%destructor { releaseConstant($$); } <constant>
%destructor { releaseExpression($$); } <expression>
%destructor { releaseSentence($$); } <sentence>
%destructor { releaseProgram($$); } <program>
%destructor { releaseVariable($$); } <variable>
%destructor { releaseVariableCall($$); } <variableCall>
%destructor { releaseMethodCall($$); } <methodCall>
%destructor { releaseFunctionCall($$); } <functionCall>
%destructor { releaseParameters($$); } <parameters>
%destructor { releaseNewline($$); } <newline>
%destructor { releaseDepth($$); } <depth>
%destructor { releaseTuple($$); } <tuple>
%destructor { releaseFunctionDefinition($$); } <functionDefinition>
%destructor { releaseClassDefinition($$); } <classDefinition>
%destructor { releaseBlock($$); } <block>
%destructor { releaseObject($$); } <object>





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
%type <constant> constant
%type <variable> variable
%type <expression> expression
%type <program> program
%type <parameters> parameters
%type <functionCall> functionCall
%type <methodCall> methodCall
%type <fieldGetter> fieldGetter
%type <object> object
%type <tuple> tuple
%type <list> list
%type <variableCall> variableCall
%type <sentence> sentence
%type <block> block
%type <block> nextCondBlock
%type <functionDefinition> functionDefinition
%type <classDefinition> classDefinition
%type <depth> depth
%type <newline> newline
%type <whileBlock> whileBlock
%type <forBlock> forBlock
%type <conditionalBlock> ifBlock
%type <conditionalBlock> elifBlock
%type <conditionalBlock> elseBlock

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 * @also see https://www.geeksforgeeks.org/precedence-and-associativity-of-operators-in-python/ for Python
 */
%right INTEGER
%right FLOAT
%right BOOLEAN
%right STRING
%precedence COMMA
%precedence IDENTIFIER
%right LOGICAL_OR
%right LOGICAL_AND
%right LOGICAL_NOT
%right ASSIGN_WALRUS
%right IN NOT_IN IS IS_NOT COMPARISON_LT COMPARISON_LTE COMPARISON_GT COMPARISON_GTE COMPARISON_EQ COMPARISON_NEQ
%left  BITWISE_OR
%left  BITWISE_XOR
%left  BITWISE_AND
%left  BITWISE_LSHIFT BITWISE_RSHIFT
%left  ADD SUB
%left  MUL DIV FLOOR_DIV MOD
%right BITWISE_NOT
%right NEWLINE_TOKEN
%right EXP
%right DOT
%right IF ELIF ELSE
%right OPEN_BRACE CLOSE_BRACE
%right OPEN_PARENTHESIS CLOSE_PARENTHESIS
%%

program:  depth sentence program							{ $$ = GeneralProgramSemanticAction(currentCompilerState(), $1, $2, $3); }
	| YYEOF				                                    { $$ = FinishedProgramSemanticAction(currentCompilerState()); }
	;

sentence: expression												{ $$ = ExpressionSentenceSemanticAction($1); }
	| variable														{ $$ = VariableSentenceSemanticAction($1); }
    | block                                                         { $$ = BlockSentenceSemanticAction($1); }

block: functionDefinition[fdef] COLON NEWLINE_TOKEN TAB program[prog]               { $$ = FunctionDefinitionBlockSemanticAction($fdef, $prog); }
     | classDefinition[cdef] COLON NEWLINE_TOKEN TAB program[prog]                  { $$ = ClassDefinitionBlockSemanticAction($cdef, $prog); }
	 | ifBlock[cblock] COLON NEWLINE_TOKEN TAB program[prog] nextCondBlock[next]    { $$ = ConditionalBlockSemanticAction($cblock, $prog, $next); }
     | whileBlock[wblock] COLON NEWLINE_TOKEN TAB program[prog]                     { $$ = WhileLoopBlockSemanticAction($wblock, $prog); }
     | forBlock[fblock] COLON NEWLINE_TOKEN TAB program[prog]                       { $$ = ForLoopBlockSemanticAction($fblock, $prog); }
	 ;

nextCondBlock: %empty
             | elifBlock[elif] COLON NEWLINE_TOKEN TAB program[prog] nextCondBlock[next]    { $$ = ConditionalBlockSemanticAction($elif, $prog, $next); }
             | elseBlock[els] COLON NEWLINE_TOKEN TAB program[prog]                         { $$ = ConditionalBlockSemanticAction($els, $prog, NULL); }

ifBlock: IF expression[exp]                                             { $$ = ConditionalSemanticAction(CB_IF, $exp); }

elifBlock: ELIF expression[exp]                                         { $$ = ConditionalSemanticAction(CB_ELIF, $exp); }

elseBlock: ELSE expression[exp]                                         { $$ = ConditionalSemanticAction(CB_ELSE, $exp); }

forBlock: FOR expression[exp1] IN expression[exp2]                      { $$ = ForBlockSemanticAction($exp1, $exp2); }

whileBlock: WHILE expression[cond] 									    { $$ = WhileBlockSemanticAction($cond); }
	      ;

functionDefinition: DEF IDENTIFIER[id] OPEN_PARENTHESIS parameters[params] CLOSE_PARENTHESIS                                { $$ = GenericFunctionDefinitionSemanticAction($id, $params); }
                  | DEF IDENTIFIER[id] OPEN_PARENTHESIS parameters[params] CLOSE_PARENTHESIS RETURNS object[retObj]         { $$ = ObjectFunctionDefinitionSemanticAction($id, $params, $retObj); }
                  | DEF IDENTIFIER[id] OPEN_PARENTHESIS parameters[params] CLOSE_PARENTHESIS RETURNS variableCall[retVar]   { $$ = VariableCallFunctionDefinitionSemanticAction($id, $params, $retVar); }
                  | DEF IDENTIFIER[id] OPEN_PARENTHESIS parameters[params] CLOSE_PARENTHESIS RETURNS tuple[tupleVar]        { $$ = TupleFunctionDefinitionSemanticAction($id, $params, $tupleVar); }
                  | DEF IDENTIFIER[id] OPEN_PARENTHESIS parameters[params] CLOSE_PARENTHESIS RETURNS list[listVar]          { $$ = ListFunctionDefinitionSemanticAction($id, $params, $listVar); }

classDefinition: CLASS IDENTIFIER[id]                               { $$ = ClassDefinitionSemanticAction($id); }
               | CLASS IDENTIFIER[id] tuple[tpl]                    { $$ = TupleClassDefinitionSemanticAction($id, $tpl); }
               ;

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
    | constant                                                      { $$ = ConstantExpressionSemanticAction($1); }
    | variableCall                                                  { $$ = VariableCallExpressionSemanticAction($1); }
    | functionCall                                                  { $$ = FunctionCallExpressionSemanticAction($1); }
    | methodCall[method]                                            { $$ = MethodCallExpressionSemanticAction($method); }
    | fieldGetter[field]                                            { $$ = FieldGetterExpressionSemanticAction($field); }
    | expression[left] LOGICAL_AND expression[right]                { $$ = LogicalAndExpressionSemanticAction($left, $right); }
    | expression[left] LOGICAL_OR expression[right]                 { $$ = LogicalOrExpressionSemanticAction($left, $right); }
    | LOGICAL_NOT expression[exp]                                   { $$ = LogicalNotExpressionSemanticAction($exp); }
    | expression[left] COMPARISON_EQ expression[right]	            { $$ = ExpressionComparisonSemanticAction(BCT_EQU, $left, $right); }
    | expression[left] COMPARISON_NEQ expression[right]	            { $$ = ExpressionComparisonSemanticAction(BCT_NEQ, $left, $right); }
    | expression[left] COMPARISON_GT expression[right]	            { $$ = ExpressionComparisonSemanticAction(BCT_GT, $left, $right); }
    | expression[left] COMPARISON_GTE expression[right]	            { $$ = ExpressionComparisonSemanticAction(BCT_GTE, $left, $right); }
    | expression[left] COMPARISON_LT expression[right]	            { $$ = ExpressionComparisonSemanticAction(BCT_LT, $left, $right); }
    | expression[left] COMPARISON_LTE expression[right]	            { $$ = ExpressionComparisonSemanticAction(BCT_LTE, $left, $right); }
    | expression[left] IN expression[right]	                        { $$ = ExpressionComparisonSemanticAction(BCT_MEMBER, $left, $right); }
    | expression[left] NOT_IN expression[right]	                    { $$ = ExpressionComparisonSemanticAction(BCT_NMEMBER, $left, $right); }
    | expression[left] IS expression[right]	                        { $$ = ExpressionComparisonSemanticAction(BCT_IDENTITY, $left, $right); }
    | expression[left] IS_NOT expression[right]	                    { $$ = ExpressionComparisonSemanticAction(BCT_NIDENTITY, $left, $right); }
	;

variable: IDENTIFIER[id] ASSIGN expression[expr]                    { $$ = ExpressionVariableSemanticAction($id, $expr);}
		;

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	    | BOOLEAN													{ $$ = BooleanConstantSemanticAction($1); }
        | FLOAT                                                     { $$ = FloatConstantSemanticAction($1); }
        | STRING                                                    { $$ = StringConstantSemanticAction($1); }
        | list                                                      { $$ = ListConstantSemanticAction($1); }
        | tuple                                                     { $$ = TupleConstantSemanticAction($1); }
	    ;

methodCall: variableCall[var] DOT functionCall[func]				{ $$ = VariableMethodCallSemanticAction($var, $func); }
          | constant[cons] DOT functionCall[func]                   { $$ = ConstantMethodCallSemanticAction($cons, $func); }
          ;

fieldGetter: variableCall[var] DOT variableCall[field]				{ $$ = VariableFieldGetterSemanticAction($var, $field); }
           | constant[cons] DOT variableCall[field]                 { $$ = ConstantFieldGetterSemanticAction($cons, $field);}
           ;

object: BUILTIN_IDENTIFIER  										{ $$ = ObjectSemanticAction($1, OT_BUILTIN); }
	;

list: OPEN_BRACE parameters[params] CLOSE_BRACE			            { $$ = ParametrizedListSemanticAction($params); }
    | OPEN_BRACE object[type] CLOSE_BRACE           				{ $$ = TypedListSemanticAction($type); }
    ;

tuple: OPEN_PARENTHESIS parameters[params] CLOSE_PARENTHESIS         { $$ =  ParametrizedTupleSemanticAction($params); }
     | OPEN_PARENTHESIS object[type] CLOSE_PARENTHESIS               { $$ =  TypedTupleSemanticAction($type); }
     ;

variableCall: IDENTIFIER 											{ $$ = VariableCallSemanticAction($1); }

functionCall: IDENTIFIER[id] OPEN_PARENTHESIS parameters[params] CLOSE_PARENTHESIS 	{ $$ = FunctionCallSemanticAction($id, $params); }
	;

parameters: %empty													{ $$ = ParametersSemanticAction(NULL, NULL, EMPTY); }
	| 	expression[left] COMMA parameters[right]				    { $$ = ParametersSemanticAction($left, $right, NOT_FINAL); }
	|   expression[left]											{ $$ = ParametersSemanticAction($left, NULL, FINAL); }

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
