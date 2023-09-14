#include <stdio.h>
#include <string.h>
#include "fsNode.h"
#include "fsNode.test.h"

char *testCreateNode_empty()
{
    puts("testCreateNode_empty");
    FSNODE *empty = createNewNode("", 'D');
    mu_assert("node should not be null", empty != NULL);
    mu_assert("node should not have a name", strlen(empty->name) == 0);
    mu_assert("node should not have a child", empty->child == NULL);
    mu_assert("node should not have a sibling", empty->sibling == NULL);
    mu_assert("node should not have a parent", empty->parent == NULL);
    return 0;
}

char *testCreateNode_File()
{
    puts("testCreateNode_File");
    FSNODE *file = createNewNode("", 'F');
    mu_assert("node should not be null", file != NULL);
    mu_assert("node should not have a name", strlen(file->name) == 0);
    mu_assert("node should not have a child", file->child == NULL);
    mu_assert("node should not have a sibling", file->sibling == NULL);
    mu_assert("node should not have a parent", file->parent == NULL);
    return 0;
}