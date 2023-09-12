#include <stdlib.h>
#include "Tree.h"

Node *createEmptyNode(char *name)
{
    return createNode(name, 0);
}

Node *createNode(char *name, int numChildren)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->name = name;
    node->numChildren = numChildren;
    Node *array[numChildren];
    node->children = array;
    return node;
}

void addChild(Node *parent, Node *child)
{
    parent->children[parent->numChildren] = child;
    parent->numChildren++;
}