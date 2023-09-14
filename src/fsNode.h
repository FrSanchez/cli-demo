#pragma once

typedef struct _fsNode
{
    char name[64];
    char type; // D for directory, F for file
    struct _fsNode *child;
    struct _fsNode *parent;
    struct _fsNode *sibling;
} FSNODE;

FSNODE *createNewNode(const char *name, char type);
void addSibling(FSNODE *node, FSNODE *sibling);
void addChildren(FSNODE *node, FSNODE *child);
void removeSibling(FSNODE *node, FSNODE *sibling);
void removeChildren(FSNODE *node, FSNODE *child);
FSNODE *hasChild(FSNODE *parent, char *child);
FSNODE *hasSibling(FSNODE *node, char *sibling);
