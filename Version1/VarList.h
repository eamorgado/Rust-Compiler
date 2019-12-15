#include "Node.h"
#ifndef VARLIST_H
#define VARLIST_H

#define FIRSTVAR(L) ((L)->first)
#define LASTVAR(L) ((L)->last)
#define SIZEVARLIST(L) ((L)->size)

typedef struct _varlist{
    Node* first;
    Node* last;
    int size;
}VarList;


VarList* makeVarList();
int isEmptyVarList(VarList*);
int containsVarList(char*,VarList*);
Node* headVarList(VarList*);
Node* tailVarList(VarList*);
void appendVarList(char*,VarList*);
void prependVarList(char*,VarList*);
void removeFirstVarList(VarList*);
void removeLastVarList(VarList*);
void freeVarList(VarList*);

#endif