#ifndef USER_COMMAND_H
#define USER_COMMAND_H

#define USER_COMMAND_FN(name) int name(char *pathname)
#define USER_COMMAND_FN_NOARGS(name) int name(void)

typedef struct
{
    char *name;
    char *description;
} COMMAND_HELP;

USER_COMMAND_FN(f_mkdir);
USER_COMMAND_FN(f_rmdir);
USER_COMMAND_FN(f_ls);
USER_COMMAND_FN(f_cd);
USER_COMMAND_FN_NOARGS(f_pwd);
USER_COMMAND_FN(f_creat);
USER_COMMAND_FN(f_rm);
USER_COMMAND_FN(f_reload);
USER_COMMAND_FN(f_save);
USER_COMMAND_FN_NOARGS(f_quit);
USER_COMMAND_FN_NOARGS(f_help);
void initUserCommands();
int find_command(char *user_command);
char *fileType(FSNODE *node);

#endif