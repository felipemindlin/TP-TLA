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
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * FactorExpressionSemanticAction(Factor * factor);
Factor * ConstantFactorSemanticAction(Constant * constant);
Factor * ExpressionFactorSemanticAction(Expression * expression);
Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression);
Conditional * ConditionalEvalSemanticAction(Conditional * leftCond, Conditional * rightCond, CondType type);

Sentence * FunctionCallSentenceSemanticAction(FunctionCall * functionCall, SentenceType type);
Sentence * FunctionDefinitionSentenceSemanticAction(const char * functionName, Parameters * parameters, SentenceType type);
VariableCall * VariableCallSemanticAction(const char * variableName);
FunctionCall * FunctionCallSemanticAction(const char * functionName, Parameters * parameters);
Parameters * ParametersSemanticAction(Expression * leftExpression, Parameters * nextParameters, ParamType type);

Depth * DepthSemanticAction(DepthType type);
Newline * NewlineSemanticAction(NewlineType type);

#endif
