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
    logDebug("Adding sibling %s to %s\n", sibling->name, node->name);
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
    logDebug("Adding child %s to %s\n", child->name, parent->name);
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
    logDebug("Removing sibling %s from %s\n", sibling->name, node->name);
    if (sibling->child)
    {
        logError("Cannot remove node with children\n");
        return;
    }
    if (node->sibling == sibling)
    {
        node->sibling = sibling->sibling;
        free(sibling);
    }
    else
    {
        removeSibling(node->sibling, sibling);
    }
}

void removeChildren(FSNODE *node, FSNODE *child)
{
    logDebug("Removing child %s from %s\n", child->name, node->name);
    if (node->child == child)
    {
        node->child = child->sibling;
        free(child);
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
