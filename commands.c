#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "commands.h"
#include "splitString.h"
#include "tree.h"
#include "list.h"

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

Node *navigateToFolder(char *path)
{
    Node *folder = cwd;
    if (isAbsolutePath(path))
    {
        folder = root;
    }
    char **tokens = splitString(path, "/");
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
int cd(char *path)
{
    if (validatePath(path))
    {
        Node *folder = navigateToFolder(path);
        if (folder)
        {
            cwd = folder;
            return 0;
        }
        return 1;
    }
}

char *printFolder(Node *pwd)
{
    char *path = (char *)malloc(sizeof(char) * 1024);
    Node *folder = pwd->parent;
#ifdef DEBUG
    fprintf(stderr, "cwd: [%s]\n", pwd->name);
#endif
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
int pwd(char *unused)
{
    if (!cwd->parent)
    {
        puts("/");
        return 0;
    }
    char *path = printFolder(cwd);
    free(path);
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
        Node *folder = navigateToFolder(path);
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
int ls(char *path)
{
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
int quit(char *unused)
{
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

int save(char *)
{
    FILE *fp = fopen("save.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
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

int load(char *)
{
    FILE *fp = fopen("save.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
    }
    char line[1024];
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\r\n")] = 0;
        makedir(line);
    }
    fclose(fp);
    return 0;
}
