#ifndef SHELL_H
#define SHELL_H


#include <sys/wait.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_LINE 4096
#define MAX_ARGS 300
#define MAX_CMDS 100
#define MAX_JOBS 300
#define PROMPT_SIZE (PATH_MAX + 512)
#define SHELL_PROMPT "\U0001F41A"
#define IN 1
#define OUT 0

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"

typedef enum {
    STOPPED,
    RUNNING_FG,
    RUNNING_BG,
    FINISHED
} JobStatus;

typedef struct {
    pid_t pid;
    JobStatus status;
    char prompt[MAX_LINE];
} Job;

#endif