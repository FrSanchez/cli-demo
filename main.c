#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include "commands.h"
#include "splitString.h"

#define MAXCOM 1000 // max number of letters to be supported

typedef int (*command_method_t)(char *path);
typedef struct
{
    char *name;
    command_method_t method;
    char *description;
} command_t;

command_t commands[] = {
    {"cd", cd, "Change directory"},
    {"pwd", pwd, "Print working directory"},
    {"mkdir", mkdir, "Make directory"},
    {"rmdir", remdir, "Remove directory"},
    {"ls", ls, "List directory"},
    {"quit", quit, "Quit shell"},
    {"help", help, "Show help"},
};

int help(char *unused)
{
    puts("This is the help portion of the program.");
    puts("The following commands are available:");
    for (int i = 0; i < sizeof(commands) / sizeof(command_t); i++)
    {
        printf("%s: %s\n", commands[i].name, commands[i].description);
    }
    return 0;
}

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
    // remove the \n from the end of the string
    str[strcspn(str, "\r\n")] = 0;
    return 0;
}

command_method_t findCommand(char *input)
{
    fprintf(stderr, "input: [%s]\n", input);
    for (int i = 0; i < sizeof(commands) / sizeof(command_t); i++)
    {
        fprintf(stderr, "command %d: %s\n", i, commands[i].name);
        if (strcmp(commands[i].name, input) == 0)
        {
            return commands[i].method;
        }
    }
    return NULL;
}

void executeCommand(char *parsed[])
{
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

int main()
{
    char inputString[MAXCOM];

    while (1)
    {
        // take input
        if (takeInput(inputString))
            continue;
        char **parsedArgs = splitString(inputString, " ");

        // process
        executeCommand(parsedArgs);
    }
    return 0;
}