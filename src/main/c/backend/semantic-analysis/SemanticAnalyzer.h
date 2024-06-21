#ifndef _SEMANTIC_ANALYZER_H_
#define _SEMANTIC_ANALYZER_H_

#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/Logger.h"
#include "SaDataTypes.h"
#include "SymbolTable.h"
#include "funcList.h"
#include <limits.h>

/**
 * @brief Initialize the module's internal state.
 */
void initializeSemanticAnalyzerModule();

/**
 * @brief Shutdown the module's internal state.
 */
void shutdownSemanticAnalyzerModule();

/**
 * @brief Check if a function with an operator WITH string support is defined for the given operands.
 * @param left The left operand.
 * @param right The right operand.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult binaryArithmeticOperatorW(SaComputationResult left, SaComputationResult right);

/**
 * @brief Check if a function with an operator WITHOUT string support is defined for the given operands.
 * @param left The left operand.
 * @param right The right operand.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult binaryArithmeticOperatorWO(SaComputationResult left, SaComputationResult right);

/**
 * @brief Check if a program is semantically correct.
 * @param program The program to be computed.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult computeProgram(Program * program);

/**
 * @brief Check if a sentence is semantically correct.
 * @param sentence The sentence to be computed.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult computeSentence(Sentence * sentence);

/**
 * @brief Check if an expression is semantically correct.
 * @param expression The expression to be computed.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult computeExpression(Expression * expression);

/**
 * @brief Check if a variable call is semantically correct.
 * @param vCall The variable call to be computed.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult computeVariableCall(VariableCall * vCall);

/**
 * @brief Check if a function/method call is semantically correct.
 * @param fCall The function call to be computed.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult computeFunctionCall(FunctionCall * fCall);

/**
 * @brief Check if a code block is semantically correct.
 * @param block The code block to be computed.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult computeBlock(Block * block);

/**
 * @brief Check if a conditional block is semantically correct.
 * @param conditional The conditional block to be computed.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult computeConditionalBlock(ConditionalBlock * conditional);

/**
 * @brief Check if a function definition is semantically correct.
 * @param fdef The function definition to be computed.
 * @param body The body of the function.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult computeFunctionDefinition(FunctionDefinition * fdef, Sentence * body);

/***
 * @brief Generate a computation result for a constant.
 * @param constant The constant to be computed.
 * @return A computation result of the constant with its data type.
 */
SaComputationResult computeConstant(Constant * constant);

/**
 * @brief Check if a variable declaration is semantically correct.
 * @param var The variable declaration to be computed.
 * @return A computation result of the variable declaration with its data type if successful.
 */
SaComputationResult computeVariableDeclaration(Variable * var);
#endif