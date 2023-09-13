#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "commands.h"
#include "stringUtils.h"
#include "Tree.h"
#include "list.h"
#include "logger.h"

Node *root;
Node *cwd;

Node *getCwd()
{
    return cwd;
}

Node *getRoot()
{
    return root;
}

void initCommands(char *saveFile)
{
    root = createEmptyNode("");
    cwd = root;
    char *args[] = {saveFile};
    load(1, args);
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
        logError("Path is null or empty\n", NULL);
        return 0;
    }
    return 1;
}

Node *navigateToFolder(char *path)
{
    logDebug("navigating to %s\n", path);
    Node *folder = cwd;
    if (isAbsolutePath(path))
    {
        folder = root;
    }
    char **tokens = splitString(path, "/", NULL);
    for (int i = 0; tokens[i]; i++)
    {
        if (strcmp(tokens[i], "..") == 0)
        {
            if (folder->parent)
            {
                folder = folder->parent;
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
                return NULL;
            }
        }
    }
    free(tokens);
    return folder;
}

/**
 * Function to change directory
 */
int cd(int argc, char *args[])
{
    if (args == NULL || args[0] == NULL)
    {
        return 0;
    }
    if (validatePath(args[0]))
    {
        Node *folder = navigateToFolder(args[0]);
        if (folder)
        {
            cwd = folder;
            return 0;
        }
        return 1;
    }
    return 0;
}

char *printFolder(Node *pwd)
{
    char *path = (char *)malloc(sizeof(char) * 1024);
    Node *folder = pwd->parent;
    logDebug("cwd: [%s]\n", pwd->name);
    strcpy(path, pwd->name);
    while (folder)
    {
        char temp[1024] = {'\0'};
        sprintf(temp, "%s/%s", folder->name, path);
        strcpy(path, temp);
        folder = folder->parent;
    }
    return path;
}

/*
 * Prints current working directory
 */
int pwd(int argc, char *__unused__[])
{
    UNUSED(argc);
    UNUSED(__unused__);
    if (!cwd->parent)
    {
        puts("/");
        return 0;
    }
    char *path = printFolder(cwd);
    puts(path);
    free(path);
    return 0;
}

/**
 * Function to remove a directory
 */
int remdir(int argc, char *args[])
{
    char *path = args[0];
    if (validatePath(path))
    {
        Node *folder = navigateToFolder(&path[0]);
        if (!folder)
        {
            return 1;
        }
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
int ls(int argc, char *args[])
{
    char *path = args[0];
    Node *folder = cwd;
    if (path != NULL && strlen(path) > 0)
    {
        folder = navigateToFolder(path);
    }
    if (folder)
    {
        for (int i = 0; i < folder->numChildren; i++)
        {
            printf("%s\n", folder->children[i]->name);
        }
        return 0;
    }
    return 1;
}

/**
 * Function to quit
 */
int quit(int argc, char *__unused__[])
{
    UNUSED(__unused__);
    save(0, NULL);
    printf("\nGoodbye\n");
    exit(0);
    return 0; // may not be needed this line
}

ListNode *listFolders(Node *folder, ListNode *head)
{
    head = insertIntoList(head, printFolder(folder));
    for (int i = 0; i < folder->numChildren; i++)
    {
        head = listFolders(folder->children[i], head);
    }
    return head;
}

int save(int argc, char *args[])
{
    char *arg = args ? args[0] : NULL;
    char *fileName = DEFAULT_SAVE_FILE;
    if (arg && strlen(arg) > 0)
    {
        fileName = arg;
    }
    logInfo("Saving to file: %s\n", fileName);
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        logError("Error opening file!\n", NULL);
    }
    ListNode *head = NULL;
    head = listFolders(root, head);
    if (head && head->next)
    {
        ListNode *current = head->next;
        while (current)
        {
            fprintf(fp, "%s\n", current->data);
            current = current->next;
        }
    }
    fclose(fp);
    return 0;
}

int load(int argc, char *args[])
{
    char *arg = args[0];
    char *fileName = DEFAULT_SAVE_FILE;
    if (arg && strlen(arg) > 0)
    {
        fileName = arg;
    }
    logInfo("Loading from file: %s\n", fileName);
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        logError("Error opening file!\n", NULL);
        return 0;
    }
    char line[1024];
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\r\n")] = 0;
        char *mkdirArgs[] = {line};
        makedir(1, mkdirArgs);
    }
    fclose(fp);
    return 0;
}
