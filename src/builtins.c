#include "builtins.h"
#include "job_control.h"

void handle_cd_command(char *path)
{
    char *homedir;

    if ((homedir = getenv("HOME")) == NULL)
    {
        homedir = getpwuid(getuid())->pw_dir;
    }

    char p[PATH_MAX] = {0};

    if (path == NULL)
    {
        strcat(p, homedir);
    }
    else if (strncmp(path, "~", 1) == 0)
    {
        strcat(p, homedir);
        path++;
    }

    if (path)
        strcat(p, path);

    if (chdir(p) < 0)
        perror(COLOR_RED "cd");
}

int handle_builtin_command(char *cmds[MAX_CMDS][MAX_ARGS], int cmd_nums)
{
    if (strcmp("bg", cmds[0][0]) == 0)
    {
        int i;
        if (cmd_nums == 2)
            i = atoi(cmds[0][1]) - 1; // TODO check the bound of index
        else
            i = get_stopped_job();

        if (i == -1)
        {

            printf("No jobs available\n");
            return 1;
        }
        killpg(jobs[i].pid, SIGCONT);
        set_job_state(jobs[i].pid, RUNNING_BG);
        return 1;
    }

    if (strcmp("fg", cmds[0][0]) == 0)
    {
        int i;
        if (cmd_nums == 2)
            i = atoi(cmds[0][1]) - 1; // TODO check the bound of index
        else
            i = find_bg_stopped_job();

        if (i == -1)
        {
            printf("No jobs available\n");
            return 1;
        }
        set_job_state(jobs[i].pid, RUNNING_FG);
        while (jobs[i].status == RUNNING_FG)
        {
            sleep(1);
        }
        return 1;
    }

    if (strcmp("jobs", cmds[0][0]) == 0)
    {
        list_jobs();
        return 1;
    }

    if (strcmp("exit", cmds[0][0]) == 0)
    {
        exit(0);
    }

    if (strcmp("cd", cmds[0][0]) == 0)
    {
        handle_cd_command(cmds[0][1]);
        return 1;
    }
    return 0;
}