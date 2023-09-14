#include <stdlib.h>
#include <string.h>
#include "logger.h"
#include "fsNode.h"

FSNODE *createNewNode(const char *name, char type)
{
    if (type != 'D' && type != 'F')
    {
        logError("Invalid type %c\n", type);
        return NULL;
    }
    FSNODE *newNode = (FSNODE *)malloc(sizeof(FSNODE));
    strcpy(newNode->name, name);
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->parent = NULL;
    newNode->type = type;
    return newNode;
}

void addSibling(FSNODE *node, FSNODE *sibling)
{
    if (node->sibling == NULL)
    {
        node->sibling = sibling;
    }
    else
    {
        addSibling(node->sibling, sibling);
    }
}

void addChildren(FSNODE *parent, FSNODE *child)
{
    if (parent->child == NULL)
    {
        parent->child = child;
    }
    else
    {
        addSibling(parent->child, child);
    }
    child->parent = parent;
}

void removeSibling(FSNODE *node, FSNODE *sibling)
{
    if (sibling->child)
    {
        logError("Cannot remove node with children\n");
        return;
    }
    if (node->sibling == sibling)
    {
        node->sibling = sibling->sibling;
    }
    else
    {
        removeSibling(node->sibling, sibling);
    }
}

void removeChildren(FSNODE *node, FSNODE *child)
{
    if (node->child == child)
    {
        node->child = child->sibling;
    }
    else
    {
        removeSibling(node->child, child);
    }
}

FSNODE *hasChild(FSNODE *parent, char *child)
{
    if (parent->child == NULL)
    {
        return NULL;
    }
    if (strcmp(parent->child->name, child) == 0)
    {
        return parent->child;
    }
    return hasSibling(parent->child, child);
}

FSNODE *hasSibling(FSNODE *node, char *sibling)
{
    if (node->sibling == NULL)
    {
        return NULL;
    }
    if (strcmp(node->sibling->name, sibling) == 0)
    {
        return node->sibling;
    }
    return hasSibling(node->sibling, sibling);
}