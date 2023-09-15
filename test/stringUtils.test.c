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

char *test_splitString()
{
    puts("test_splitString");
    int count = 1;
    char **words = splitString("a/b/c", "/", &count);
    for (int i = 0; i < count; i++)
    {
        puts(words[i]);
    }
    mu_assert("counst should be 3", count == 3);
    mu_assert("c should be a", strcmp(words[0], "a") == 0);
    freeWords(words);
    return 0;
}