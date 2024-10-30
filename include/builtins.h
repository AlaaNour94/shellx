#ifndef BUILTINS_H
#define BUILTINS_H

#include "shell.h"
#include <pwd.h>

void handle_cd_command(char *path);
int handle_builtin_command(char *cmds[MAX_CMDS][MAX_ARGS], int cmd_nums);

#endif