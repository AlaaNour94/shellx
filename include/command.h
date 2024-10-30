#ifndef COMMAND_H
#define COMMAND_H

#include "shell.h"

void parseline(char *buf, char *cmds[MAX_CMDS][MAX_ARGS], int *cmd_nums);
void eval(char *cmdline);
void exec_pipe(char *cmds[MAX_CMDS][MAX_ARGS], int current, int argc, int rfd);

#endif