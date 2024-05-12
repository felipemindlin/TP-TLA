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

Constant * IntegerConstantSemanticAction(const int value);
Constant * BooleanConstantSemanticAction(const int value);
Constant * StringConstantSemanticAction(const char * value);
Constant * FloatConstantSemanticAction(const float value);
Constant * TupleConstantSemanticAction(List * value);
Constant * TupleConstantSemanticAction(List * value);
Constant * ListConstantSemanticAction(Tuple * value);
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * FactorExpressionSemanticAction(Factor * factor);
Factor * ConstantFactorSemanticAction(Constant * constant);
Factor * ExpressionFactorSemanticAction(Expression * expression);
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression);
Conditional * ConditionalEvalSemanticAction(Conditional * leftCond, Conditional * rightCond, CondType type);
Object * ObjectSemanticAction(const char * className);

Sentence * FunctionCallSentenceSemanticAction(FunctionCall * functionCall, SentenceType type);
Sentence * FunctionDefinitionSentenceSemanticAction(const char * functionName, Parameters * parameters, SentenceType type);

List * ListSemanticAction(Parameters * parameters);
Tuple * TupleSemanticAction(Parameters * parameters);

List * EmptyListSemanticAction();
List * TypedListSemanticAction(Object * objectType);
Tuple * EmptyTupleSemanticAction();
Tuple * TypedTupleSemanticAction(Object * objectType);


Conditional * ConditionalBooleanSemanticAction(Conditional * left, Conditional * right, const BooleanCond booleanCond);
Conditional * ConditionalBooleanVariableSemanticAction(VariableCall * left, VariableCall * right, const BooleanCond booleanCond);
Conditional * ConditionalBooleanAndVariableSemanticAction(VariableCall * var, Conditional * cond, const BooleanCond booleanCond);

Conditional * ConditionalExpressionSemanticAction(Expression * left, Expression * right, const ComparisonCond comparisonCond);
Conditional * ConditionalExpressionVariableSemanticAction(VariableCall * left, VariableCall * right, const ComparisonCond comparisonCond);
Conditional * ConditionalExpressionAndVariableSemanticAction(VariableCall * var, Expression * fact, const ComparisonCond comparisonCond);

Conditional * ConditionalSingleFactorSemanticAction(Factor * factor);

Conditional * ConditionalObjectSemanticAction(Object * left, Object * right, const ObjectCond objectCond);
Conditional * ConditionalObjectVariableSemanticAction(VariableCall * left, VariableCall * right, const ObjectCond objectCond);
Conditional * ConditionalObjectAndVariableSemanticAction(VariableCall * var, Object * obj, const ObjectCond objectCond);

Conditional * ConditionalSingleObjectSemanticAction(Object * object);

Conditional * ConditionalVariableSemanticAction(VariableCall * variable);

While * WhileBlockSemanticAction(Conditional * conditional);

For * ForFactorBlockSemanticAction(Factor * left, Factor * right);
For * ForVariableBlockSemanticAction(VariableCall * left, VariableCall * right);
For * ForFactorAndVariableBlockSemanticAction(VariableCall * var, Factor * fact, Which which);
ClassDefinition * ClassDefinitionSemanticAction(const char * className, const char * parent);
FunctionDefinition * FunctionDefinitionSemanticAction(const char * functionName, Parameters * parameters, DataType returnType, Object * objectReturnType);
VariableCall * VariableCallSemanticAction(const char * variableName);
FunctionCall * FunctionCallSemanticAction(const char * functionName, Parameters * parameters);
Parameters * ParametersSemanticAction(Expression * leftExpression, Parameters * nextParameters, ParamType type);

Depth * DepthSemanticAction(DepthType type);
Newline * NewlineSemanticAction(NewlineType type);



#endif
