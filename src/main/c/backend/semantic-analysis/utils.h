#ifndef UTILS_H
#define UTILS_H
#include "stdbool.h"

#define MAX_VARIABLES 1000

static char *declaredVariables[MAX_VARIABLES];

static char *detectedInArithmeticExpressions[MAX_VARIABLES];

static char *detectedInBooleanExpressions[MAX_VARIABLES];

static int declaredVariablesCount = 0;

static int arithmeticCount = 0;

static int booleanCount = 0;

bool isDeclared(const char *varName);

bool isAlreadyArithmetic(const char *varName);

bool isAlreadyBoolean(const char *varName);

void markDeclared(const char *varName);

void markArith(const char *varName);


void markBoolean(const char *varName);

#endif