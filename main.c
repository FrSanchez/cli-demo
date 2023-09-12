#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include "commands.h"

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

typedef int (*command_method_t)(char *path);
typedef struct
{
    char *name;
    command_method_t method;
} command_t;

command_t commands[] = {
    {"cd", cd},
    {"pwd", pwd},
    {"mkdir", mkdir},
    {"rmdir", rmdir},
    {"ls", ls},
    {"quit", quit},
    {"help", help},
};

// Function to take input
int takeInput(char *str)
{
    printf(">>> ");
    if (fgets(str, MAXCOM, stdin) == NULL)
    {
        quit("");
    }
    if (strlen(str) == 0)
    {
        return 1;
    }
    return 0;
}

// Function to print Current Directory.
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}

command_method_t findCommand(char *input)
{
    for (int i = 0; i < sizeof(commands) / sizeof(command_t); i++)
    {
        if (strcmp(commands[i].name, input) == 0)
        {
            return commands[i].method;
        }
    }
    return NULL;
}

// function for parsing command words
void parseSpace(char *str, char **parsed)
{
    int i;

    for (i = 0; i < MAXLIST; i++)
    {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
    command_method_t method = findCommand(parsed[0]);
    if (method != NULL)
    {
        if (parsed[1] == NULL)
        {
            printf("Command: %s ()\n", parsed[0]);
            method("");
        }
        else
        {
            printf("Command: %s (%s)\n", parsed[0], parsed[1]);
            method(parsed[1]);
        }
    }
    else
    {
        printf("Command not found: %s\n", parsed[0]);
    }
}

void processString(char *str, char **parsed, char **parsedpipe)
{

    char *strpiped[2];
    int piped = 0;

    parseSpace(str, parsed);
}

int main()
{
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char *parsedArgsPiped[MAXLIST];
    int execFlag = 0;

    while (1)
    {
        // print shell line
        printDir();
        // take input
        if (takeInput(inputString))
            continue;
        // process
        processString(inputString, parsedArgs, parsedArgsPiped);
    }
    return 0;
}