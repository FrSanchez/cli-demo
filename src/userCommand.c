#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "fsNode.h"
#include "userCommand.h"

FSNODE *root;
FSNODE *cwd;

char *cmd[] = {"mkdir", "rmdir", "ls", "cd", "pwd", "creat", "rm",
               "reload", "save", "quit", "help", 0};

COMMAND_HELP commandData[] = {
    {.name = "mkdir", .description = "Make a new directory for a given pathname."},
    {.name = "rmdir", .description = "Remove the directory, provided it is empty."},
    {.name = "ls", .description = "List the directory contents."},
    {.name = "cd", .description = "Change the CWD to pathname, or to / if no pathname."},
    {.name = "pwd", .description = "Print the (absolute) pathname of the CWD."},
    {.name = "creat", .description = "Create a FILE node."},
    {.name = "rm", .description = "Remove the FILE node."},
    {.name = "reload", .description = "Construct a fresh file system."},
    {.name = "save", .description = "Save the current file system tree as a Linux file."},
    {.name = "quit", .description = "Save the file system tree, then terminate the program."},
    {.name = "help", .description = "Print the list of valid commands."},
};

void initUserCommands()
{
    logDebug("Initializing user commands\n");
    root = createNewNode("", 'D');
    root->parent = root;
    root->sibling = root;
    cwd = root;
}

char *fileType(FSNODE *node)
{
    return node->type == 'D' ? "Directory" : "File";
}

int find_command(char *user_command)
{
    int i = 0;
    logDebug("Finding command %s\n", user_command);
    while (cmd[i])
    {
        logDebug("Comparing %s to %s\n", user_command, cmd[i]);
        if (strcmp(user_command, cmd[i]) == 0)
        {
            logDebug("Found command %s at index %d\n", user_command, i);
            return i;
        }
        i++;
    }
    return -1;
}

USER_COMMAND_FN(f_mkdir)
{
    if (pathname == NULL || strlen(pathname) == 0)
    {
        logError("Path is null or empty\n", NULL);
        return 0;
    }
    if (hasChild(cwd, pathname))
    {
        logError("Directory %s already exists\n", pathname);
        return 0;
    }
    FSNODE *newNode = createNewNode(pathname, 'D');
    addChildren(cwd, newNode);
    return 0;
}
USER_COMMAND_FN(f_rmdir)
{
    FSNODE *child = NULL;
    if (child = hasChild(cwd, pathname))
    {
        if (child->type == 'D')
        {
            if (child->child)
            {
                logError("Directory %s is not empty\n", pathname);
                return 0;
            }
            removeChildren(cwd, child);
        }
        else
        {
            logError("%s %s is not a directory\n", fileType(child), pathname);
        }
    }
    else
    {
        logError("Directory %s does not exist\n", pathname);
    }
    return 0;
}

USER_COMMAND_FN(f_ls)
{
    FSNODE *node = cwd->child;
    while (node)
    {
        printf("%s%c ", node->name, node->type == 'D' ? '/' : ' ');
        node = node->sibling;
    }
    return 0;
}

USER_COMMAND_FN(f_cd)
{
    if (pathname == NULL || strlen(pathname) == 0)
    {
        cwd = root;
        return 0;
    }
    FSNODE *child = NULL;
    if ((child = hasChild(cwd, pathname)) && (child->type == 'D'))
    {
        cwd = child;
    }
    else
    {
        logError("Directory %s does not exist\n", pathname);
    }
    return 0;
}

USER_COMMAND_FN_NOARGS(f_pwd)
{
    FSNODE *node = cwd;
    char path[1024] = "";
    do
    {
        char temp[1024] = "";
        sprintf(temp, "/%s%s", node->name, path);
        strcpy(path, temp);
        node = node->parent;
    } while (node != root);
    printf("%s\n", path);
    return 0;
}

USER_COMMAND_FN(f_creat)
{
    if (pathname == NULL || strlen(pathname) == 0)
    {
        logError("Path is null or empty\n", NULL);
        return 1;
    }
    FSNODE *child;
    if ((child = hasChild(cwd, pathname)))
    {
        logError("%s %s already exists\n", fileType(child), pathname);
        return 0;
    }
    FSNODE *newFile = createNewNode(pathname, 'F');
    addChildren(cwd, newFile);
    return 0;
}

USER_COMMAND_FN(f_rm)
{
    if (pathname == NULL || strlen(pathname) == 0)
    {
        logError("Path is null or empty\n", NULL);
        return 1;
    }
    FSNODE *child;
    if ((child = hasChild(cwd, pathname)))
    {
        if (child->type == 'F')
        {
            removeChildren(cwd, child);
        }
        else
        {
            logError("%s %s is not a file\n", fileType(child), pathname);
        }
    }
    else
    {
        logError("File %s does not exist\n", pathname);
    }
    return 0;
}

USER_COMMAND_FN(f_reload)
{
    return 0;
}
USER_COMMAND_FN(f_save)
{
    return 0;
}
USER_COMMAND_FN_NOARGS(f_quit)
{
    printf("Goodbye!\n");
    exit(0);
}

USER_COMMAND_FN_NOARGS(f_help)
{
    puts("The following commands are available:");
    int i = 0;
    while (cmd[i])
    {
        printf("%s: %s\n", cmd[i], commandData[i].description);
        i++;
    }
    return 0;
}