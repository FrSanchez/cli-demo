#include <stdlib.h>
#include <string.h>
#include "Tree.h"

Node *createEmptyNode(const char *name)
{
    return createNode(name, 0);
}

Node *createNode(const char *name, int numChildren)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->name = (char *)malloc(sizeof(char *) * strlen(name) + 1);
    strcpy(node->name, name);
    node->numChildren = numChildren;
    node->children = (Node **)malloc(sizeof(Node *) * numChildren);
    node->parent = NULL;
    return node;
}

void addChild(Node *parent, Node *child)
{
    parent->children = (Node **)realloc(parent->children, sizeof(Node *) * (parent->numChildren + 1));
    parent->children[parent->numChildren] = child;
    parent->numChildren++;
    child->parent = parent;
}

Node *hasChild(Node *parent, char *child)
{
    for (int i = 0; i < parent->numChildren; i++)
    {
        if (strcmp(parent->children[i]->name, child) == 0)
        {
            return parent->children[i];
        }
    }
    return NULL;
}

void removeChild(Node *parent, Node *child)
{
    for (int i = 0; i < parent->numChildren; i++)
    {
        if (strcmp(parent->children[i]->name, child->name) == 0)
        {
            for (int j = i; j < parent->numChildren - 1; j++)
            {
                parent->children[j] = parent->children[j + 1];
            }
            parent->numChildren--;
            parent->children = (Node **)realloc(parent->children, sizeof(Node *) * parent->numChildren);
            break;
        }
    }
    free(child);
}