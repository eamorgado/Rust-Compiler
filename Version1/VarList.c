#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Node.h"
#include "VarList.h"

VarList* makeVarList(){
    VarList* list = (VarList*)malloc(sizeof(VarList));
    if(!list) perror("makeVarList: ERROR creating list");
    FIRSTVAR(list) = LASTVAR(list) = NULL;
    SIZEVARLIST(list) = 0;

}
int isEmptyVarList(VarList* list){return SIZEVARLIST(list) == 0;}

int containsVarList(char* name,VarList* list){
    if(isEmptyVarList(list)) return 0;
    Node* node = FIRSTVAR(list);
    while(node && strcmp(name,NAMENODE(node)) != 0) node = NEXTNODE(node);
    return (node == NULL || strcmp(name,NAMENODE(node)) != 0) ? 0 : 1;
}
Node* headVarList(VarList* list){
    if(isEmptyVarList(list)) return NULL;
    return FIRSTVAR(list);
}
Node* tailVarList(VarList* list){
    if(isEmptyVarList(list)) return NULL;
    if(SIZEVARLIST(list) == 1) return headVarList(list);
    return LASTVAR(list);
}

void appendVarList(char* name,VarList* list){
    Node* node = makeNode(name);
    if(isEmptyVarList(list)) FIRSTVAR(list) = node;
    else NEXTNODE(LASTVAR(list)) = node;
    LASTVAR(list) = node;
    SIZEVARLIST(list)++;
}
void prependVarList(char* name,VarList* list){
    Node* node = makeNode(name);
    if(isEmptyVarList(list)) LASTVAR(list) = node;
    else NEXTNODE(node) = FIRSTVAR(list);
    FIRSTVAR(list) = node;
    SIZEVARLIST(list)++;
}
void removeFirstVarList(VarList* list){
    if(isEmptyVarList(list)) return;
    Node* node = FIRSTVAR(list);
    FIRSTVAR(list) = NEXTNODE(node);
    free(node);
    SIZEVARLIST(list)--;
}
void removeLastVarList(VarList* list){
    if(isEmptyVarList(list)) return;
    if(SIZEVARLIST(list) == 1){removeFirstVarList(list); return;}
    Node* node = FIRSTVAR(list);
    while(NEXTNODE(NEXTNODE(node)) != NULL) node = NEXTNODE(node);
    LASTVAR(list) = node;
    free(NEXTNODE(LASTVAR(list)));
    NEXTNODE(LASTVAR(list)) = NULL;
    SIZEVARLIST(list)--;
}

void printVarList(VarList* list){
    printf("[");
    if(isEmptyVarList(list)){
        printf("]"); return;
    }
    Node* node = FIRSTVAR(list);
    while(node){
        printf("%s,",NAMENODE(node));
        node = NEXTNODE(node);
    }
    printf("]\n");
    return;
}

void freeVarList(VarList* list){
    if(!isEmptyVarList(list))
        freeNode(NULL,FIRSTVAR(list));
    free(list);
}