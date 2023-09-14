#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <getopt.h>
#include "userCommand.h"
#include "stringUtils.h"
#include "logger.h"

#define MAXCOM 1000 // max number of letters to be supported

// Function to take input
int takeInput(char *str)
{
    printf(">>> ");
    if (fgets(str, MAXCOM, stdin) == NULL)
    {
        f_quit();
    }
    str[strcspn(str, "\r\n")] = 0;
    if (strlen(str) == 0)
    {
        return 1;
    }
    // remove the \n from the end of the string
    return 0;
}

void executeCommand(int count, char *parsed[])
{
    int cmd = find_command(parsed[0]);
    if (cmd < 0)
    {
        logError("Invalid command: %s\n", parsed[0]);
    }
    switch (cmd)
    {
    case 0:
        f_mkdir(parsed[1]);
        break;
    case 1:
        f_rmdir(parsed[1]);
        break;
    case 2:
        f_ls(parsed[1]);
        break;
    case 3:
        f_cd(parsed[1]);
        break;
    case 4:
        f_pwd();
        break;
    case 5:
        f_creat(parsed[1]);
        break;
    case 6:
        f_rm(parsed[1]);
        break;
    case 7:
        f_reload(parsed[1]);
        break;
    case 8:
        f_save(parsed[1]);
        break;
    case 9:
        f_quit();
        break;
    case 10:
        f_help();
        break;
    default:
        logError("Invalid command: %s\n", parsed[0]);
        break;
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
    initUserCommands();
    while (1)
    {
        // take input
        if (takeInput(inputString))
            continue;
        int count;
        char **parsedArgs = splitString(inputString, " ", &count);

        // process
        executeCommand(count, parsedArgs);
        free(parsedArgs);
    }
    return 0;
}
