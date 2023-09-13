#pragma once

#define DEFAULT_SAVE_FILE "filesystem.txt"
#define UNUSED(x) (void)(x)

void initCommands(char *saveFile);
int cd(char *path);
int makedir(char *path);
int remdir(char *path);
int ls(char *path);
int pwd(char *);
int quit(char *);
int help(char *);
int save(char *);
int load(char *);
