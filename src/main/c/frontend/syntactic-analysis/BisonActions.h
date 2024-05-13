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
Constant * ListConstantSemanticAction(List * lst);
Constant * TupleConstantSemanticAction(Tuple * tpl);

/** EXPRESSION SECTION **/
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * ConstantExpressionSemanticAction(Constant * constant);

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

/** VARIABLE SECTION **/
Variable * ExpressionVariableSemanticAction(char * restrict id, Expression * expr);
Variable * FunctionCallVariableSemanticAction(char * restrict id, FunctionCall * functionCall);
Variable * MethodCallVariableSemanticAction(char * restrict id, MethodCall * methodCall);
Variable * FieldGetterVariableSemanticAction(char * restrict id, FieldGetter * fieldGetter);
Variable * ObjectVariableSemanticAction(char * restrict id, Object * obj);

/** METHOD CALL SECTION **/
MethodCall * VariableMethodCallSemanticAction(VariableCall *, FunctionCall *);

/** FIELD GETTER SECTION **/
FieldGetter * VariableFieldGetterSemanticAction(VariableCall *, VariableCall *);

/** OBJECT SECTION **/
Object * ObjectSemanticAction(char * restrict id, ObjectType type);

/** LIST SECTION **/
List * ParametrizedListSemanticAction(Parameters * params);
List * TypedListSemanticAction(Object * obj);

/** TUPLE SECTION **/
Tuple * ParametrizedTupleSemanticAction(Parameters * params);
Tuple * TypedTupleSemanticAction(Object * obj);

#endif
