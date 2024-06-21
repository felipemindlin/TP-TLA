#include "utils.h"

bool isDeclared(const char *varName) {
    for (int i = 0; i < declaredVariablesCount; ++i) {
        if (strcmp(declaredVariables[i], varName) == 0) {
            return true;
        }
    }
    return false;
}

bool isAlreadyArithmetic(const char *varName) {
    for (int i = 0; i < arithmeticCount; ++i) {
        if (strcmp(detectedInArithmeticExpressions[i], varName) == 0) {
            return true;
        }
    }
    return false;
}

bool isAlreadyBoolean(const char *varName) {
    for (int i = 0; i < booleanCount; ++i) {
        if (strcmp(detectedInBooleanExpressions[i], varName) == 0) {
            return true;
        }
    }
    return false;
}

void markDeclared(const char *varName) {
    if (!isDeclared(varName)) {
        declaredVariables[declaredVariablesCount++] = strdup(varName);
    }
}


void markArith(const char *varName) {
    if (!isAlreadyArithmetic(varName)) {
        detectedInArithmeticExpressions[arithmeticCount++] = strdup(varName);
    }
}


void markBoolean(const char *varName) {
    if (!isAlreadyBoolean(varName)) {
        detectedInBooleanExpressions[booleanCount++] = strdup(varName);
    }
}