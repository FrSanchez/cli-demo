#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

char *getFilename(char *str)
{
    int n = strlen(str);
    char *suffix = str + n;
    while (0 < n && str[--n] != '/')
        ;
    suffix = str + n;
    if (str[n] == '/')
    {
        suffix += 1;
    }
    char *answer = malloc(strlen(suffix) + 1);
    strcpy(answer, suffix);
    return answer;
}

char freeWords(char **words)
{
    for (int i = 0; words[i] != NULL; i++)
    {
        free(words[i]);
    }
    free(words);
}
/**
 * Function to split a string into an array of strings
 */
char **splitString(char *my_str_literal, const char *a_delim, size_t *out)
{ // More general pattern:
    char *token, *str, *tofree;
    char **res = NULL;
    int words = 0;

    tofree = str = strdup(my_str_literal); // We own str's memory now.
    while ((token = strsep(&str, a_delim)))
    {
        if (token && strlen(token) > 0)
        {
            res = (char **)realloc(res, sizeof(char *) * ++words);
            assert(res != NULL);
            char *word = malloc(strlen(token) + 1);
            strcpy(word, token);
            res[words - 1] = word;
        }
    }
    /* realloc one extra element for the last NULL */
    res = (char **)realloc(res, sizeof(char *) * (words + 1));
    res[words] = 0;
    *out = words;
    free(tofree);
    return res;
}

// custom getline to ingore \n at the end
// https://stackoverflow.com/questions/18278240/how-does-getline-function-work-here
int fgetline(FILE *fp, char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getc(fp)) != EOF && c != '\n'; ++i)
        s[i] = c;
    s[i] = '\0';
    return i;
}
