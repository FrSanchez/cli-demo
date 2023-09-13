#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <getopt.h>
#include "commands.h"
#include "splitString.h"
#include "logger.h"

#define MAXCOM 1000 // max number of letters to be supported

typedef int (*command_method_t)(char *path);
typedef struct
{
    char *name;
    command_method_t method;
    char *description;
} command_t;

command_t commands[] = {
    {"cd", &cd, "Change directory"},
    {"pwd", &pwd, "Print working directory"},
    {"mkdir", &makedir, "Make directory"},
    {"rmdir", &remdir, "Remove directory"},
    {"ls", &ls, "List directory"},
    {"quit", &quit, "Quit shell"},
    {"help", &help, "Show help"},
    {"save", &save, "Save folder structure"},
    {"load", &load, "Load folder structure"},
    {0, 0, 0}};

command_t *findCommand(char *input);

int help(char *arg)
{
    if (arg != NULL && strlen(arg) > 0)
    {
        command_t *cmd = findCommand(arg);
        if (cmd != NULL)
        {
            printf("%s: %s\n", cmd->name, cmd->description);
            return 0;
        }
        else
        {
            printf("Command not found: %s\n", arg);
            return 1;
        }
    }
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

command_t *findCommand(char *input)
{
    for (int i = 0; commands[i].name; i++)
    {
        if (strcmp(commands[i].name, input) == 0)
        {
            return &commands[i];
        }
    }
    return NULL;
}

void executeCommand(char *parsed[])
{
    command_t *command = findCommand(parsed[0]);
    if (command != NULL)
    {
        if (parsed[1] == NULL)
        {
            command->method("");
        }
        else
        {
            command->method(parsed[1]);
        }
    }
    else
    {
        printf("Command not found: %s\n", parsed[0]);
    }
}

void doHelp()
{
    puts("Usage: ./cli [OPTION]...");
    puts("A simple shell to manage a file system");
    puts("Options:");
    puts("  -h, --help\t\tShow this help message");
    puts("  -v, --version\t\tShow version number");
    puts("  -l, --loglevel\tSet log level (DEBUG, INFO, WARN, ERROR)");
    puts("  -f, --file\t\tLoad file");
}

void inputLogLevel(char *level)
{
    level = toUpper(level);
    if (strcmp(level, "DEBUG") == 0)
    {
        setLogLevel(LOG_DEBUG);
    }
    else if (strcmp(level, "INFO") == 0)
    {
        setLogLevel(LOG_INFO);
    }
    else if (strcmp(level, "WARN") == 0)
    {
        setLogLevel(LOG_WARN);
    }
    else if (strcmp(level, "ERROR") == 0)
    {
        setLogLevel(LOG_ERROR);
    }
    else
    {
        free(level);
        fprintf(stderr, "Invalid log level: %s\n", level);
        exit(-1);
    }
    free(level);
}

int main(int argc, char *argv[])
{
    char inputString[MAXCOM];
    int opt;
    int debug = 0;
    char *saveFile = NULL;
    char *logLevel = "ERROR";

    static struct option long_options[] =
        {
            // /* These options set a flag. */
            // {"verbose", no_argument, &verbose_flag, 1},
            // {"brief", no_argument, &verbose_flag, 0},
            /* These options don’t set a flag.
               We distinguish them by their indices. */
            {"version", no_argument, 0, 'v'},
            {"help", no_argument, 0, 'h'},
            {"loglevel", required_argument, 0, 'l'},
            {"file", required_argument, 0, 'f'},
            {0, 0, 0, 0}};
    int c;
    while (1)
    {
        int option_index = 0;
        c = getopt_long(argc, argv, "hv:l:f:", long_options, &option_index);
        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
        case 'h':
            doHelp();
            exit(0);
        case 'v':
            puts("Version 1.0");
            exit(0);
        case 'l':
            logLevel = optarg;
            break;
        case 'f':
            saveFile = optarg;
            break;
        case '?':
            /* getopt_long already printed an error message. */
            break;

        default:
            abort();
        }
    }

    inputLogLevel(logLevel);
    initCommands(saveFile);
    while (1)
    {
        // take input
        if (takeInput(inputString))
            continue;
        char **parsedArgs = splitString(inputString, " ");

        // process
        executeCommand(parsedArgs);
        free(parsedArgs);
    }
    return 0;
}
