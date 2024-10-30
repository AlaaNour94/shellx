#include "signals.h"

void setup_signal_handlers(void) {
    signal(SIGINT, handle_sigint);
    signal(SIGCHLD, handle_sigchild);
    signal(SIGTSTP, handle_sigtstp);
}

void handle_sigint(int sig)
{
    int i = find_current_fg_job();
    if (jobs[i].pid)
    {
        killpg(jobs[i].pid, sig);
    }
    remove_job(jobs[i].pid);
}

void handle_sigchild(int sig)
{

    int status;
    pid_t child_pid;
    while ((child_pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0)
    {
        if (WIFEXITED(status) || WIFSIGNALED(status))
        {
            remove_job(child_pid);
        }
        else if (WIFSTOPPED(status))
        {
            set_job_state(child_pid, STOPPED);
        }
    }
}

void handle_sigtstp(int sig)
{
    int i = find_current_fg_job();
    if (i > -1 && jobs[i].pid)
    {
        if (0 != killpg(jobs[i].pid, sig))
            perror(COLOR_RED "signrts");

        jobs[i].status = STOPPED;
    }
}
