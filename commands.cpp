#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int validatePath(char *path)
{
    if (path == NULL || strlen(path) == 0)
    {
        printf("Path is null or empty\n");
        return 1;
    }
    return 0;
}

int cd(char *path)
{
    if (validatePath(path))
    {
    };
    return 0;
}

int pwd(char *unused)
{
    return 0;
}

int mkdir(char *path)
{
    if (validatePath(path))
    {
    };
    return 0;
}

int rmdir(char *path)
{
    if (validatePath(path))
    {
    };
    return 0;
}

int ls(char *unused)
{
    return 0;
}

int quit(char *unused)
{
    printf("\nGoodbye\n");
    exit(0);
    return 0; // may not be needed this line
}

int help(char *unused)
{
    puts("This is the help portion of the program.");
    puts("The following commands are available:");
    puts("cd <path> - change directory");
    puts("pwd - print working directory");
    puts("mkdir <path> - make directory");
    puts("rmdir <path> - remove directory");
    puts("ls - list directory contents");
    puts("quit - exit the program");
    puts("help - display this help message");
    puts("");
    return 0;
}