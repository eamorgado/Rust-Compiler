#include <stdlib.h>
#include "Node.h"

Node* makeNode(char* varname){
    Node* node = (Node*)malloc(sizeof(Node));
    if(!node) perror("makeNode: ERROR creating Node");
    NAMENODE(node) = varname;
    NEXTNODE(node) = NULL;
    return node;
}
void freeNode(Node* parent,Node* son){
    if(NEXTNODE(son) == NULL){
        NEXTNODE(parent) = NULL;
        free(son);
        return;
    }
    freeNode(son,NEXTNODE(son));
}