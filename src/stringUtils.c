#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Function to split a string into an array of strings
 */
char **splitString(char *str, char *seps, int *size)
{
    char **res = NULL;
    char *p = strtok(str, seps);
    int n_spaces = 0;

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

    if (size != NULL)
    {
        *size = n_spaces;
    }
    return res;
}

char *toUpper(const char *input)
{
    char *output = malloc(strlen(input) + 1);
    strcpy(output, input);
    for (size_t i = 0; i < strlen(output); i++)
    {
        output[i] = toupper(output[i]);
    }
    return output;
}
