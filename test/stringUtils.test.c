#include <stdio.h>
#include "minunit.h"
#include "stringUtils.h"

char *test_getFilename()
{
    puts("test_getFilename");
    char *c = getFilename("/a/b/c");
    mu_assert("filename should be c", strcmp(c, "c") == 0);
    return 0;
}

char *test_getFilename2()
{
    puts("test_getFilename2");
    char *c = getFilename("/abc");
    mu_assert("filename should be abc", strcmp(c, "abc") == 0);
    return 0;
}

char *test_getFilename3()
{
    puts("test_getFilename3");
    char *c = getFilename("abc");
    mu_assert("filename should be abc", strcmp(c, "abc") == 0);
    return 0;
}