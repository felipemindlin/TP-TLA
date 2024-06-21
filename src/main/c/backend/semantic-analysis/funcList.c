#include "funcList.h"


static Logger * _logger = NULL;
static LinkedListADT funcList = NULL;


void funcListInit(){
    funcList = createLinkedListADT();
}

void funcIterBegin(){
    begin(funcList);
}

Block * getNextFunc(){
    return (Block * )next(funcList);
}

void funcListDestroy(){
    freeLinkedListADTDeep(funcList);
}

bool funcListAdd(Block * fdefBlock){
    if (appendElement(funcList, (void *)fdefBlock) == NULL)
        return false;
    else
        return true;
}

int getFuncLength(){
    return getLength(funcList);
}