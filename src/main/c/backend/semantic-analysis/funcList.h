#ifndef FUNC_LIST_H
#define FUNC_LIST_H


#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "linkedListADT.h"

void funcListInit();

Block * getNextFunc();

void funcListDestroy();

bool funcListAdd(Block * fdefBlock);

int getFuncLength();


void funcIterBegin();

#endif