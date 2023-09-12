#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Function to split a string into an array of strings
 */
char **splitString(char *str, char *seps)
{
    char **res = NULL;
    char *p = strtok(str, seps);
    int n_spaces = 0, i;

    while (p)
    {
        res = (char **)realloc(res, sizeof(char *) * ++n_spaces);
        if (res == NULL)
        {
            fprintf(stderr, "splitString: memory allocation failed\n");
            exit(-1); /* memory allocation failed */
        }
        res[n_spaces - 1] = p;
        p = strtok(NULL, seps);
    }

    /* realloc one extra element for the last NULL */
    res = (char **)realloc(res, sizeof(char *) * (n_spaces + 1));
    res[n_spaces] = 0;

    return res;
}