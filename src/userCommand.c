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
    root = createNewNode("", 'D');
    root->parent = root;
    root->sibling = root;
    cwd = root;
}

int find_command(char *user_command)
{
    int i = 0;
    while (cmd[i])
    {
        if (strcmp(user_command, cmd[i]) == 0)
            return i;
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
    return 0;
}
USER_COMMAND_FN_NOARGS(f_pwd)
{
    return 0;
}
USER_COMMAND_FN(f_creat)
{
    if (pathname == NULL || strlen(pathname) == 0)
    {
        logError("Path is null or empty\n", NULL);
        return 0;
    }
    FSNODE *newFile = createNewNode(pathname, 'F');
    addChildren(cwd, newFile);
    return 0;
}
USER_COMMAND_FN(f_rm)
{
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