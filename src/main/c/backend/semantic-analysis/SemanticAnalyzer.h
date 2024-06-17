#ifndef _SEMANTIC_ANALYZER_H_
#define _SEMANTIC_ANALYZER_H_

#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/Logger.h"
#include "SaDataTypes.h"
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
 * @param program The sentence to be computed.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult computeSentence(Sentence * sentence);

/**
 * @brief Check if an expression is semantically correct.
 * @param program The program to be computed.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult computeExpression(Expression * expression);

/***
 * @brief Generate a computation result for a constant.
 * @param constant The constant to be computed.
 * @return A computation result of the constant with its data type.
 */
SaComputationResult computeConstant(Constant * constant);

#endif