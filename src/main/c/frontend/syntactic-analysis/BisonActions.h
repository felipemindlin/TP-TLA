#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();

/**
 * Bison semantic actions.
 */

/** CONSTANT SECTION**/
Constant * IntegerConstantSemanticAction(const int value);
Constant * BooleanConstantSemanticAction(const boolean value);
Constant * FloatConstantSemanticAction(const double decimal);
Constant * StringConstantSemanticAction(char * restrict str);
Constant * ListConstantSemanticAction(List * lst);
Constant * TupleConstantSemanticAction(Tuple * tpl);

/** EXPRESSION SECTION **/
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * ConstantExpressionSemanticAction(Constant * constant);
Expression * VariableCallExpressionSemanticAction(VariableCall * var);

Program * GeneralProgramSemanticAction(CompilerState * compilerState, Depth * dp, Sentence * sentence, Program * nprog);
Program * FinishedProgramSemanticAction(CompilerState * compilerState);
Conditional * ConditionalEvalSemanticAction(Conditional * leftCond, Conditional * rightCond, CondType type);

VariableCall * VariableCallSemanticAction(const char * variableName);
FunctionCall * FunctionCallSemanticAction(const char * functionName, Parameters * parameters);
Parameters * ParametersSemanticAction(Expression * leftExpression, Parameters * nextParameters, ParamType type);

Depth * DepthSemanticAction(DepthType type);
Newline * NewlineSemanticAction(NewlineType type);

/** SENTENCE SECTION **/
Sentence * ExpressionSentenceSemanticAction(Expression * exp);
Sentence * VariableSentenceSemanticAction(Variable * var);
Sentence * BlockSentenceSemanticAction(Block * block);

/** BLOCK SECTION **/
Block * FunctionDefinitionBlockSemanticAction(FunctionDefinition * fdef, Program * nextProg);
Block * ClassDefinitionBlockSemanticAction(ClassDefinition * cdef, Program * nextProg);

/** FUNCTION DEFINITION SECTION **/
FunctionDefinition * GenericFunctionDefinitionSemanticAction(char * restrict id, Parameters * params);
FunctionDefinition * ObjectFunctionDefinitionSemanticAction(char * restrict id, Parameters * params, Object * object);
FunctionDefinition * VariableCallFunctionDefinitionSemanticAction(char * restrict id, Parameters * params, VariableCall * retVar);
FunctionDefinition * TupleFunctionDefinitionSemanticAction(char * restrict id, Parameters * params, Tuple * tupleVar);
FunctionDefinition * ListFunctionDefinitionSemanticAction(char * restrict id, Parameters * params, List * listVar);

/** CLASS DEFINITION SECTION **/
ClassDefinition * ClassDefinitionSemanticAction(char * restrict id);
ClassDefinition * TupleClassDefinitionSemanticAction(char * restrict id, Tuple * tpl);

/** VARIABLE SECTION **/
Variable * ExpressionVariableSemanticAction(char * restrict id, Expression * expr);
Variable * FunctionCallVariableSemanticAction(char * restrict id, FunctionCall * functionCall);
Variable * MethodCallVariableSemanticAction(char * restrict id, MethodCall * methodCall);
Variable * FieldGetterVariableSemanticAction(char * restrict id, FieldGetter * fieldGetter);
Variable * ObjectVariableSemanticAction(char * restrict id, Object * obj);
Variable * VariableCallVariableSemanticAction(char * restrict id, VariableCall * var);

/** METHOD CALL SECTION **/
MethodCall * VariableMethodCallSemanticAction(VariableCall *, FunctionCall *);
MethodCall * ConstantMethodCallSemanticAction(Constant * cons, FunctionCall * func);

/** FIELD GETTER SECTION **/
FieldGetter * VariableFieldGetterSemanticAction(VariableCall *, VariableCall *);
FieldGetter * ConstantFieldGetterSemanticAction(Constant * cons, VariableCall * field);

/** OBJECT SECTION **/
Object * ObjectSemanticAction(char * restrict id, ObjectType type);

/** LIST SECTION **/
List * ParametrizedListSemanticAction(Parameters * params);
List * TypedListSemanticAction(Object * obj);

/** TUPLE SECTION **/
Tuple * ParametrizedTupleSemanticAction(Parameters * params);
Tuple * TypedTupleSemanticAction(Object * obj);

#endif
