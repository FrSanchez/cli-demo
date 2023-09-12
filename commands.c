#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "commands.h"
#include "splitString.h"
#include "Tree.h"

Node *root;
Node *cwd;

#define isAbsolutePath(path) (path[0] == '/')

void initCommands()
{
    root = createEmptyNode("");
    cwd = root;
}

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
        return 0;
    }
    return 1;
}

/**
 * Function to change directory
 */
int cd(char *path)
{
    if (validatePath(path))
    {
        Node *folder = cwd;
        if (isAbsolutePath(path))
        {
            folder = root;
        }
        char **tokens = splitString(path, "/");
        for (int i = 0; tokens[i]; i++)
        {
            char *token = tokens[i];
#ifdef DEBUG
            fprintf(stderr, "(%s) %d token: %s\n", folder->name, i, token);
#endif
            if (strcmp(token, "..") == 0)
            {
                if (folder->parent)
                {
                    folder = folder->parent;
                }
            }
            else
            {
                Node *child = hasChild(folder, token);
                if (child)
                {
                    folder = child;
                }
                else
                {
                    printf("Directory does not exist\n");
                    free(tokens);
                    return 1;
                }
            }
        }
        free(tokens);
        cwd = folder;
        return 0;
    }
}

/*
 * Prints current working directory
 */
int pwd(char *unused)
{
    char path[1024] = {'\0'};
    if (cwd == root)
    {
        puts("/");
        return 0;
    }
    Node *folder = cwd->parent;
    strcpy(path, cwd->name);
    while (folder)
    {
        char temp[1024] = {'\0'};
        sprintf(temp, "%s/%s", folder->name, path);
        strcpy(path, temp);
        folder = folder->parent;
    }
    puts(path);
    return 0;
}

/**
 * Function to make a directory
 */
int makedir(char *path)
{
    if (validatePath(path))
    {
        Node *folder = cwd;
        if (isAbsolutePath(path))
        {
            folder = root;
        }
        char **tokens = splitString(path, "/");
#ifdef DEBUG
        fprintf(stderr, "tokens: %d\n", sizeof(tokens));
#endif
        for (int i = 0; tokens[i]; i++)
        {
#ifdef DEBUG
            fprintf(stderr, "(%s) %d token: %s\n", folder->name, i, tokens[i]);
#endif

            Node *child;
            if (child = hasChild(folder, tokens[i]))
            {
#ifdef DEBUG
                fprintf(stderr, "%s exists\n", tokens[i]);
#endif
                folder = child;
            }
            else
            {
#ifdef DEBUG
                fprintf(stderr, "creating %s\n", tokens[i]);
#endif
                Node *newNode = createEmptyNode(tokens[i]);
                addChild(folder, newNode);
                folder = newNode;
            }
        }
        free(tokens);
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
        char **tokens = splitString(path, "/");
        Node *folder = cwd;
        if (isAbsolutePath(path))
        {
            folder = root;
        }
        for (int i = 0; tokens[i]; i++)
        {
            if (strcmp(tokens[i], "..") == 0)
            {
                if (folder->parent)
                {
                    if (folder->parent)
                    {
                        folder = folder->parent;
                    }
                }
            }
            else
            {
                Node *next = hasChild(folder, tokens[i]);
                if (next)
                {
                    folder = next;
                }
                else
                {
                    printf("Directory does not exist\n");
                    free(tokens);
                    return 1;
                }
            }
        }
        free(tokens);
        if (folder == root)
        {
            printf("Cannot remove root directory\n");
            return 1;
        }
        if (folder->numChildren > 0)
        {
            printf("Directory is not empty\n");
            return 1;
        }
        if (folder == cwd)
        {
            printf("Can't remove current directory\n");
            return 1;
        }
        removeChild(folder->parent, folder);
    };
    return 0;
}

/**
 * Function to list directory
 */
int ls(char *path)
{
    for (int i = 0; i < cwd->numChildren; i++)
    {
        printf("%s\n", cwd->children[i]->name);
    }
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

int save(char *)
{
    return 0;
}

int load(char *)
{
    return 0;
}
