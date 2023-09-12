#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "commands.h"
#include "splitString.h"
#include "Tree.h"

/*
 * Function to validate a path
 * Returns 0 if path is valid
 * Returns 1 if path is invalid
 */
int validatePath(char *path)
{
    if (path == NULL || strlen(path) == 0)
    {
        printf("Path is null or empty\n");
        return 1;
    }
    return 0;
}

/**
 * Function to change directory
 */
int cd(char *path)
{
    if (validatePath(path))
    {
    };
    return 0;
}

/*
 * Prints current working directory
 */
int pwd(char *unused)
{
    return 0;
}

/**
 * Function to make a directory
 */
int mkdir(char *path)
{
    if (validatePath(path))
    {
    };
    return 0;
}

/**
 * Function to remove a directory
 */
int remdir(char *path)
{
    if (validatePath(path))
    {
    };
    return 0;
}

/**
 * Function to list directory
 */
int ls(char *unused)
{
    return 0;
}

/**
 * Function to quit
 */
int quit(char *unused)
{
    printf("\nGoodbye\n");
    exit(0);
    return 0; // may not be needed this line
}
