#ifndef NODE_H
#define NODE_H

#define NAMENODE(N) ((N)->name)
#define NEXTNODE(N) ((N)->next)

typedef struct _node{
    char* name;
    struct _node* next;
}Node;

Node* makeNode(char*);
void freeNode(Node*,Node*);

#endif