#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Node* makeTreeNode(char* content){
    Node* node = (Node*)malloc(sizeof(Node));
    VAL(node) = content;
    CHILDREN(node) = makeNodeList();
    return node;
}

void addChild(Node* parent,ListNode* child){
    if(SIZE(CHILDREN(parent)) == 0)
        FIRST(CHILDREN(parent)) = LAST(CHILDREN(parent)) = child;
    else{
        NEXT(LAST(CHILDREN(parent))) = child;
        LAST(CHILDREN(parent)) = child;
    }
    SIZE(CHILDREN(parent))++;
}

ListNode* makeListNode(Node* node,ListNode* next){
    ListNode* list = (ListNode*)malloc(sizeof(ListNode));
    NEXT(list) = next;
    NODE(list) = node;
    return list;
}

NodeList* makeNodeList(){
    NodeList* list = (NodeList*)malloc(sizeof(NodeList));
    SIZE(list) = 0;
    FIRST(list) = LAST(list) = NULL;
    return list;
}

void giveS(int n){
    for(int i = 0; i < n; i++) printf(" ");
}

void printNode(Node* root,int n){
    giveS(n);
    printf("%s\n",VAL(root));
    ListNode* curr = FIRST(CHILDREN(root));
    while(curr != NULL){
        printNode(curr,n+2);
        curr = NEXT(curr);
        if(!curr) break;
    }
}