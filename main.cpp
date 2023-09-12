#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <map>
#include <iostream>
#include "commands.h"

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

typedef int (*command_method_t)(char *path);
std::map<std::string, command_method_t> commands;

void initCommands()
{
    commands["cd"] = cd;
    commands["pwd"] = pwd;
    commands["mkdir"] = mkdir;
    commands["rmdir"] = rmdir;
    commands["ls"] = ls;
    commands["quit"] = quit;
    commands["help"] = help;
}

// Function to take input
int takeInput(char *str)
{
    char *buf;

    buf = readline("\n>>> ");
    if (strlen(buf) != 0)
    {
        strncpy(str, buf, MAXCOM);
        return 0;
    }
    return 1;
}

// Function to print Current Directory.
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
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
    if (commands.find(parsed[0]) == commands.end())
    {
        printf("Command not found [%s]\n", parsed[0]);
    }
    else
    {
        if (parsed[1] == NULL)
        {
            printf("Command: %s ()\n", parsed[0]);
            commands[parsed[0]]("");
        }
        else
        {
            printf("Command: %s (%s)\n", parsed[0], parsed[1]);
            commands[parsed[0]](parsed[1]);
        }
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
    initCommands();

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