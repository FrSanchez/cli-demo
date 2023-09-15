#include <stdio.h>
#include "minunit.h"
#include "mkdir.test.h"
#include "fsNode.h"

extern FSNODE *root;

char *test_mkDir_emptyRoot()
{
    puts("test_mkDir_emptyRoot");
    int result = f_mkdir("");
    mu_assert("Error: mkDir_emptyRoot failed", result == 1);
    return 0;
}

char *test_mkDir_invalid()
{
    puts("test_mkDir_invalid");
    int result = f_mkdir("/");
    mu_assert("Error: mkDir_invalid failed", result == 1);
    return 0;
}

char *test_mkDir_noPath()
{
    puts("test_mkDir_noPath");
    initUserCommands();
    int result = f_mkdir("a/b/c/d");
    mu_assert("Error: mkDir_noPath failed", result == 1);
    return 0;
}

char *test_mkDir_absolute()
{
    puts("test_mkDir_absolute");
    initUserCommands();
    int result = f_mkdir("/a");
    mu_assert("Error: mkDir /a failed", result == 0);
    result = f_mkdir("/a/b");
    mu_assert("Error: mkDir /a/b failed", result == 0);
    result = f_mkdir("/a/b/c");
    mu_assert("Error: mkDir /a/b/c failed", result == 0);
    FSNODE *dirA = hasChild(root, "a");
    mu_assert("Can't find folder a", dirA != NULL);
    return 0;
}

char *test_mkDir_relative()
{
    puts("test_mkDir_relative");
    initUserCommands();
    int result = f_mkdir("a");
    mu_assert("Error: mkDir a failed", result == 0);
    result = f_mkdir("a/b");
    mu_assert("Error: mkDir a/b failed", result == 0);
    result = f_mkdir("a/b/c");
    mu_assert("Error: mkDir a/b/c failed", result == 0);
    FSNODE *dirA = hasChild(root, "a");
    mu_assert("Can't find folder a", dirA != NULL);
    return 0;
}

char *test_mkDir_noDupes()
{
    puts("test_mkDir_noDupes");
    initUserCommands();
    int result = f_mkdir("a");
    mu_assert("Error: mkDir a failed", result == 0);
    result = f_mkdir("a");
    mu_assert("Error: mkDir a didn't fail", result == 1);
    return 0;
}