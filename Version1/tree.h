#ifndef TREE_H
#define TREE_H

#define VAL(N) ((N)->val)
#define CHILDREN(N) ((N)->children)

#define NODE(L) ((L)->node)
#define NEXT(L) ((L)->next)

#define FIRST(NL) ((NL)->first)
#define LAST(NL) ((NL)->last)
#define SIZE(NL) ((NL)->size)

typedef struct node{
    char* val;
    struct nodelist* children;
}Node;

typedef struct listnode{
    Node* node;
    struct listnode* next;
}ListNode;

typedef struct nodelist{
    int size;
    ListNode* first;
    ListNode* last;
}NodeList;

Node* makeTreeNode(char*);
void addChild(Node*,ListNode*);

ListNode* makeListNode(Node*,ListNode*);
NodeList* makeNodeList();




void printNode();
#endif