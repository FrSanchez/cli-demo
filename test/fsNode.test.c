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

char *testAddChild_Multiple()
{
    puts("testAddChild_Multiple");
    FSNODE *parent = createNewNode("parent", 'D');
    FSNODE *child1 = createNewNode("child1", 'D');
    FSNODE *child2 = createNewNode("child2", 'D');
    FSNODE *child3 = createNewNode("child3", 'D');
    addChildren(parent, child1);
    addChildren(parent, child2);
    addChildren(parent, child3);
    mu_assert("parent should have chilred", parent->child != NULL);
    mu_assert("parent should have 3 children", parent->child->sibling->sibling != NULL);
    FSNODE *child = hasChild(parent, "child3");
    mu_assert("child3 is found", child == child3);
    child = hasSibling(child1, "child2");
    mu_assert("child2 is found", child == child2);
    return 0;
}

char *testRemoveFirstChild()
{
    puts("testRemoveChild");
    FSNODE *parent = createNewNode("parent", 'D');
    FSNODE *child1 = createNewNode("child1", 'D');
    FSNODE *child2 = createNewNode("child2", 'D');
    addChildren(parent, child1);
    addChildren(parent, child2);
    removeChildren(parent, child1);
    mu_assert("parent should have chilred", parent->child != NULL);
    mu_assert("parent should have 1 child", parent->child->sibling == NULL);
    FSNODE *child = hasChild(parent, "child1");
    mu_assert("child 1 should be null", child == NULL);
    child = hasChild(parent, "child2");
    mu_assert("child 2 should be found", child == child2);
    return 0;
}

char *testRemoveMiddleChild()
{
    puts("testRemoveMiddleChild");
    FSNODE *parent = createNewNode("parent", 'D');
    FSNODE *child1 = createNewNode("child1", 'D');
    FSNODE *child2 = createNewNode("child2", 'D');
    FSNODE *child3 = createNewNode("child3", 'D');
    addChildren(parent, child1);
    addChildren(parent, child2);
    addChildren(parent, child3);
    removeChildren(parent, child2);
    mu_assert("parent should have chilred", parent->child != NULL);
    mu_assert("parent should have 2 children", parent->child->sibling->sibling == NULL);
    FSNODE *child = hasChild(parent, "child2");
    mu_assert("child 2 should be null", child == NULL);
    child = hasChild(parent, "child3");
    mu_assert("child 3 should be found", child == child3);
    return 0;
}