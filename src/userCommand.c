#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "fsNode.h"
#include "stringUtils.h"
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

FSNODE *navigateToPath(char *pathname, int offset)
{
    FSNODE *folder = cwd;
    if (pathname[0] == '/')
    {
        folder = root;
    }
    int count;
    char **parts = splitString(pathname, "/", &count);
    for (int i = 0; i < count - offset; i++)
    {
        if (strcmp(parts[i], "..") == 0)
        {
            folder = folder->parent;
        }
        else
        {
            FSNODE *child = hasChild(folder, parts[i]);
            if (child && child->type == 'D')
            {
                folder = child;
            }
            else
            {
                logError("Directory %s does not exist\n", parts[i]);
                return NULL;
            }
        }
    }
    return folder;
}

USER_COMMAND_FN(f_mkdir)
{
    if (pathname == NULL || strlen(pathname) == 0)
    {
        logError("Path is null or empty\n", NULL);
        return 1;
    }
    FSNODE *folder = cwd;
    if (pathname[0] == '/')
    {
        folder = root;
    }
    int count;
    char **parts = splitString(pathname, "/", &count);
    for (int i = 0; i < count - 1; i++)
    {
        if (strcmp(parts[i], "..") == 0)
        {
            folder = folder->parent;
        }
        else
        {
            FSNODE *child = hasChild(folder, parts[i]);
            if (child && child->type == 'D')
            {
                folder = child;
            }
            else
            {
                logError("Directory %s does not exist\n", parts[i]);
                return 1;
            }
        }
    }

    FSNODE *newNode = createNewNode(parts[count - 1], 'D');
    addChildren(folder, newNode);
    return 0;
}
USER_COMMAND_FN(f_rmdir)
{
    if (pathname == NULL || strlen(pathname) == 0)
    {
        logError("Path is null or empty\n", NULL);
        return 1;
    }

    FSNODE *folder = cwd;
    folder = navigateToPath(pathname, 0);

    if (folder)
    {
        if (folder->type == 'D')
        {
            if (folder->child)
            {
                logError("Directory %s is not empty\n", pathname);
                return 0;
            }
            removeChildren(folder->parent, folder);
        }
        else
        {
            logError("%s is not a directory\n", folder->name);
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
    FSNODE *folder = cwd;
    if (pathname != NULL && strlen(pathname) > 0)
    {
        folder = navigateToPath(pathname, 0);
    }

    FSNODE *node = folder->child;
    while (node)
    {
        printf("%s%c ", node->name, node->type == 'D' ? '/' : ' ');
        node = node->sibling;
    }
    return 0;
}

USER_COMMAND_FN(f_cd)
{
    FSNODE *folder = cwd;
    if (pathname == NULL || strlen(pathname) == 0)
    {
        cwd = root;
        return 0;
    }
    folder = navigateToPath(pathname, 0);
    if (folder)
    {
        cwd = folder;
        return 0;
    }
    logError("No such file or directory: %s\n", pathname);
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
    logDebug("Creating file %s\n", pathname);
    if (pathname == NULL || strlen(pathname) == 0)
    {
        logError("Path is null or empty\n", NULL);
        return 1;
    }
    FSNODE *folder = cwd;
    char *filename = getFilename(pathname);
    folder = navigateToPath(pathname, 1);
    FSNODE *child;
    if ((child = hasChild(folder, filename)))
    {
        logError("%s %s already exists\n", fileType(child), filename);
        return 0;
    }
    FSNODE *newFile = createNewNode(filename, 'F');
    addChildren(folder, newFile);
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
    FSNODE *folder = cwd;
    char *filename = getFilename(pathname);
    folder = navigateToPath(pathname, 1);
    if ((child = hasChild(folder, filename)))
    {
        if (child->type == 'F')
        {
            removeChildren(folder, child);
        }
        else
        {
            logError("%s %s is not a file\n", fileType(child), filename);
        }
    }
    else
    {
        logError("File %s does not exist\n", pathname);
    }
    return 0;
}

// custom getline to ingore \n at the end
// https://stackoverflow.com/questions/18278240/how-does-getline-function-work-here
int fgetline(FILE *fp, char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getc(fp)) != EOF && c != '\n'; ++i)
        s[i] = c;
    s[i] = '\0';
    return i;
}

USER_COMMAND_FN(f_reload)
{
    if (pathname == NULL || strlen(pathname) == 0)
    {
        logError("Path is null or empty\n", NULL);
        return 1;
    }
    FILE *fp = fopen(pathname, "r");

    if (!fp)
    {
        logError("Could not open file\n", NULL);
        return 1;
    }

    int len;            /* current line length */
    char line[MAXLINE]; /* current input line */
    while ((len = fgetline(fp, line, MAXLINE)) > 0)
    {
        logDebug("Retrieved line %s\n", line);
        int count;
        char **cmd = splitString(line, ":", &count);
        if (count != 2)
        {
            logError("Invalid line: %s\n", line);
        }
        else
        {
            switch (cmd[0][0])
            {
            case 'D':
                f_mkdir(cmd[1]);
                break;
            case 'F':
                f_creat(cmd[1]);
                break;
            default:
                logError("Invalid type: %c\n", cmd[0]);
            }
        }
    }

    fclose(fp);
    return 0;
}

void deepList(FILE *fp, FSNODE *node, char *route)
{
    while (node)
    {
        char temp[1024] = "";
        sprintf(temp, "%s/%s", route, node->name);
        fprintf(fp, "%c:%s\n", node->type, temp);
        if (node->type == 'D')
        {
            deepList(fp, node->child, temp);
        }
        node = node->sibling;
    }
}

USER_COMMAND_FN(f_save)
{
    if (pathname == NULL || strlen(pathname) == 0)
    {
        logError("Path is null or empty\n", NULL);
        return 1;
    }
    FILE *fp = fopen(pathname, "w");
    if (!fp)
    {
        logError("Could not open file\n", NULL);
        return 1;
    }
    deepList(fp, root->child, "");
    fclose(fp);
    return 0;
}
USER_COMMAND_FN_NOARGS(f_quit)
{
    f_save("fssim_sanchez.txt");
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
