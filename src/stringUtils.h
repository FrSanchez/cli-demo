#pragma once

#include <string.h>

char **splitString(char *str, char *seps, int *size);
char *toUpper(const char *input);
char *getFilename(char *str);
int fgetline(FILE *fp, char s[], int lim);
char freeWords(char **words);
