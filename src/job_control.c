#include "job_control.h"

volatile Job jobs[MAX_JOBS];
volatile int job_count;

int add_job(pid_t pid, JobStatus status, const char *command)
{
    for (int i = 0; i < MAX_JOBS; i++)
    {
        if (!jobs[i].pid || jobs[i].status == FINISHED)
        {
            jobs[i] = (Job){.pid = pid, .status = status};
            strncpy((char *)jobs[i].prompt, command, MAX_LINE);
            job_count++;
            return i;
        }
    }
    return -1;
}

int find_current_fg_job()
{
    for (int i = 0; i < job_count; i++)
    {
        if (jobs[i].status == RUNNING_FG)
        {
            return i;
        }
    }
    return -1;
}

int find_bg_stopped_job()
{
    for (int i = 0; i < job_count; i++)
    {
        if (jobs[i].status == RUNNING_BG || jobs[i].status == STOPPED)
        {
            return i;
        }
    }
    return -1;
}

int get_stopped_job()
{
    for (int i = 0; i < job_count; i++)
    {
        if (jobs[i].status == STOPPED)
        {
            return i;
        }
    }
    return -1;
}

void list_jobs()
{
    for (int i = 0; i < job_count; i++)
    {
        if (jobs[i].status == RUNNING_BG || jobs[i].status == STOPPED)
        {
            printf("[%d] %d \t %s\n", i + 1, jobs[i].status, jobs[i].prompt);
        }
    }
}

void remove_job(pid_t pid)
{
    for (int i = 0; i < job_count; i++)
    {
        if (jobs[i].pid == pid)
        {
            jobs[i].pid = 0;
            jobs[i].status = FINISHED;
            job_count--;
            return;
        }
    }
}

void set_job_state(pid_t pid, JobStatus status)
{
    for (int i = 0; i < job_count; i++)
    {
        if (jobs[i].pid == pid)
        {
            jobs[i].status = status;
            return;
        }
    }
}
