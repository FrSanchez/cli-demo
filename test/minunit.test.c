#include <stdio.h>
#include "minunit.h"
#include "stringUtils.test.h"
#include "fsNode.test.h"

int tests_run = 0;

char *all_tests()
{
    mu_run_test(test_getFilename);
    mu_run_test(test_getFilename2);
    mu_run_test(test_getFilename3);
    mu_run_test(testCreateNode_empty);
    mu_run_test(testCreateNode_File);
    return 0;
}

int main()
{
    char *result = all_tests();
    if (result != 0)
    {
        printf("TEST RAN: %s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
