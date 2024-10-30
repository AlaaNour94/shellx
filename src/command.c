#include "command.h"
#include "builtins.h"
#include "job_control.h"

void parseline(char *buf, char *cmds[MAX_CMDS][MAX_ARGS], int *cmd_nums)
{
    int argc = 0;
    int cmds_nums = 0;
    bool status = OUT;

    // skip leading spaces
    while (*buf == ' ' || *buf == '\n' || *buf == '\t')
    {
        buf++;
    }

    char *p = buf;
    while (*buf)
    {
        if (*buf == '|')
        {
            *buf = '\0';
            p = buf + 1;
            status = OUT;

            cmds[cmds_nums++][argc] = NULL;
            argc = 0;
        }
        else if (*buf == ' ' || *buf == '\n' || *buf == '\t')
        {
            *buf = '\0';
            p = buf + 1;
            status = OUT;
        }
        else if (*buf != ' ' && status == OUT)
        {
            cmds[cmds_nums][argc++] = p;
            status = IN;
        }

        buf++;
    }
    cmds[cmds_nums][argc] = NULL;

    if (argc)
    {
        *cmd_nums = cmds_nums + 1;
    }
    else
    {
        *cmd_nums = 0;
    }
}

void exec_pipe(char *cmds[MAX_CMDS][MAX_ARGS], int current, int argc, int rfd)
{

    int fd[2];
    if (pipe(fd) < 0)
    {
        perror(COLOR_RED "pipe error");
        exit(1);
    }
    pid_t ppid = getpid();
    pid_t pid = fork();

    if (pid < 0)
    {
        perror(COLOR_RED "fork error");
        exit(1);
    }

    if (pid == 0)
    {
        dup2(rfd, STDIN_FILENO);

        if (rfd)
            close(rfd);

        if (current < argc - 1)
            dup2(fd[1], STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);

        if (0 != setpgid(getpid(), ppid))
            perror(COLOR_RED "setpgid");

        execvp(cmds[current][0], cmds[current]);
        perror(COLOR_RED "exec error");
        exit(1);
    }

    close(fd[1]);
    if (current < argc - 1)
        exec_pipe(cmds, current + 1, argc, fd[0]);

    if (rfd)
        close(rfd);

    close(fd[0]);
    waitpid(pid, NULL, 0);
}

void eval(char *cmdline)
{

    char buf[MAX_LINE];
    int cmd_nums;
    char *cmds[MAX_CMDS][MAX_ARGS];
    strcpy(buf, cmdline);

    parseline(buf, cmds, &cmd_nums);

    if (cmd_nums == 0)
    {
        return;
    }

    if (handle_builtin_command(cmds, cmd_nums))
        return;

    pid_t pid;
    if ((pid = fork()) < 0)
    {
        perror(COLOR_RED "Fork error");
        exit(1);
    }

    if (pid == 0)
    {
        pid_t pgid = getpid();
        setpgid(pgid, pgid);
        exec_pipe(cmds, 0, cmd_nums, STDIN_FILENO);
        exit(0);
    }

    int i = add_job(pid, RUNNING_FG, cmdline);
    while (jobs[i].status == RUNNING_FG)
    {
        sleep(1);
    }
}
