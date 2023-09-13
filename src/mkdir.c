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
#include "commands.h"
#include "getopt.h"

Node *navigateToFolder(char *path);
int internalMake(int intermediate, char *path)
{
    if (validatePath(path))
    {
        Node *folder = getCwd();
        if (isAbsolutePath(path))
        {
            folder = getRoot();
        }
        logDebug("mkdir: %s\n", path);
        int count = 0;
        char **tokens = splitString(path, "/", &count);
        logDebug("tokens: %d\n", count);
        for (int i = 0; tokens[i]; i++)
        {
            logDebug("(%s) %d token: %s\n", folder->name, i, tokens[i]);

            Node *child;
            if ((child = hasChild(folder, tokens[i])))
            {
                logInfo("%s exists\n", tokens[i]);
                folder = child;
            }
            else
            {
                if (intermediate || i == count - 1)
                {
                    logDebug("creating %s\n", tokens[i]);
                    Node *newNode = createEmptyNode(tokens[i]);
                    addChild(folder, newNode);
                    folder = newNode;
                }
                else
                {
                    logError("%s does not exist\n", path);
                    return 1;
                }
            }
        }
        free(tokens);
    };
    return 0;
}
/**
 * Function to make a directory
 */
int makedir(int argc, char *args[])
{
    int opt = 0;
    int intermediate = 0;
    for (int i = 0; i < argc; i++)
    {
        if (args[i][0] == '-')
        {
            opt++;
            if (strcmp(args[i], "-p") == 0)
            {
                intermediate = 1;
            }
        }
    }
    for (int i = opt; i < argc; i++)
    {
        internalMake(intermediate, args[i]);
    }
}
