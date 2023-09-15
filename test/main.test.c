#include <stdio.h>
#include "minunit.h"
#include "stringUtils.test.h"
#include "fsNode.test.h"
#include "mkdir.test.h"

int tests_run = 0;

char *all_tests()
{

    mu_run_test(test_getFilename);
    mu_run_test(test_getFilename2);
    mu_run_test(test_getFilename3);
    mu_run_test(test_splitString);
    mu_run_test(testCreateNode_empty);
    mu_run_test(testCreateNode_File);
    mu_run_test(testAddChild_Multiple);
    mu_run_test(testRemoveFirstChild);
    mu_run_test(testRemoveMiddleChild);
    mu_run_test(test_mkDir_emptyRoot);
    mu_run_test(test_mkDir_invalid);
    mu_run_test(test_mkDir_noPath);
    mu_run_test(test_mkDir_absolute);
    mu_run_test(test_mkDir_relative);
    mu_run_test(test_mkDir_noDupes);
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
        printf("\n\nALL TESTS PASSED!!\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
