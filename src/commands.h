#pragma once
#include "Tree.h"

#define DEFAULT_SAVE_FILE "filesystem.txt"
#define UNUSED(x) (void)(x)
#define isAbsolutePath(path) (path[0] == '/')

typedef int (*command_method_t)(int argc, char *args[]);
typedef struct
{
    char *name;
    command_method_t method;
    char *description;
} command_t;

void initCommands(char *saveFile);
int cd(int argc, char *args[]);
int makedir(int argc, char *args[]);
int remdir(int argc, char *args[]);
int ls(int argc, char *args[]);
int pwd(int argc, char *args[]);
int quit(int argc, char *args[]);
int help(int argc, char *args[]);
int save(int argc, char *args[]);
int load(int argc, char *args[]);
Node *getCwd();
Node *getRoot();
int validatePath(char *path);
