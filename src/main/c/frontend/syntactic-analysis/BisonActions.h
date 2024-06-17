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
Expression * FunctionCallExpressionSemanticAction(FunctionCall * fcall);
Expression * MethodCallExpressionSemanticAction(MethodCall * methodCall);
Expression * FieldGetterExpressionSemanticAction(FieldGetter * fieldGetter);
Expression * LogicalOrExpressionSemanticAction(Expression * left, Expression * right);
Expression * LogicalAndExpressionSemanticAction(Expression * left, Expression * right);
Expression * LogicalNotExpressionSemanticAction(Expression * notExp);
Expression * ExpressionComparisonSemanticAction(BinaryComparatorType compType, Expression * left, Expression * right);

Program * GeneralProgramSemanticAction(CompilerState * compilerState, Depth * dp, Sentence * sentence, Program * nprog);
Program * FinishedProgramSemanticAction(CompilerState * compilerState);

VariableCall * VariableCallSemanticAction(const char * variableName);
FunctionCall * FunctionCallSemanticAction(const char * functionName, Parameters * parameters);
FunctionCall * ObjectFunctionCallSemanticAction(Object * obj, Parameters * parameters);
Parameters * ParametersSemanticAction(Expression * leftExpression, Parameters * nextParameters, ParamType type);

Depth * DepthSemanticAction(DepthType type);
Newline * NewlineSemanticAction(NewlineType type);

/** SENTENCE SECTION **/
Sentence * ExpressionSentenceSemanticAction(Expression * exp, Sentence * sentence);
Sentence * VariableSentenceSemanticAction(Variable * var, Sentence * sentence);
Sentence * BlockSentenceSemanticAction(Block * block, Sentence * sentence);
Sentence * ReturnSentenceSemanticAction(Expression * exp, Sentence * sentence);
Sentence * EndOfSentencesSemanticAction();

/** BLOCK SECTION **/
Block * FunctionDefinitionBlockSemanticAction(FunctionDefinition * fdef, Sentence * nextProg);
Block * ClassDefinitionBlockSemanticAction(ClassDefinition * cdef, Sentence * nextProg);
Block * ConditionalBlockSemanticAction(ConditionalBlock * cond, Sentence * nextProg, Block * nextConditinoal);
Block * WhileLoopBlockSemanticAction(WhileBlock * wblock, Sentence * nextProg);
Block * ForLoopBlockSemanticAction(ForBlock * fblock, Sentence * nextProg);

/** CONDITIONAL SECTION **/
ConditionalBlock * ConditionalSemanticAction(ConditionalType type, Expression * exp);

/** WHILE BLOCK SECTION **/
WhileBlock * WhileBlockSemanticAction(Expression * cond);

/** FOR BLOCK SECTION **/
ForBlock * ForBlockSemanticAction(Expression * left, Expression * right);

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

/** METHOD CALL SECTION **/
MethodCall * VariableMethodCallSemanticAction(VariableCall *, FunctionCall *);
MethodCall * ConstantMethodCallSemanticAction(Constant * cons, FunctionCall * func);

/** FIELD GETTER SECTION **/
FieldGetter * VariableFieldGetterSemanticAction(VariableCall *, VariableCall *);
FieldGetter * ConstantFieldGetterSemanticAction(Constant * cons, VariableCall * field);

/** OBJECT SECTION **/
Object * ObjectSemanticAction(BuiltinDefinition def, ObjectType type);

/** LIST SECTION **/
List * ParametrizedListSemanticAction(Parameters * params);
List * TypedListSemanticAction(Object * obj);

/** TUPLE SECTION **/
Tuple * ParametrizedTupleSemanticAction(Parameters * params);
Tuple * TypedTupleSemanticAction(Object * obj);

/** BINARY COMPARATOR SECTION **/
BinaryComparator * BinaryComparatorSemanticAction(BinaryComparatorType type);

/** COMPARABLE VALUE SECTION **/
ComparableValue * VariableComparableValueSemanticAction(VariableCall * var, ComparableValueType type);
ComparableValue * ExpressionComparableValueSemanticAction(Expression * expr, ComparableValueType type);

#endif
