#pragma once

typedef struct _node
{
    char *name;
    int numChildren;
    struct _node **children;
    struct _node *parent;
} Node;

Node *createEmptyNode(const char *name);
Node *createNode(const char *name, int numChildren);
void addChild(Node *parent, Node *child);
Node *hasChild(Node *parent, char *child);
void removeChild(Node *parent, Node *child);
