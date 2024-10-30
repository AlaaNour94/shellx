#ifndef JOB_CONTROL_H
#define JOB_CONTROL_H

#include "shell.h"

extern volatile Job jobs[MAX_JOBS];
extern volatile int job_count;

int add_job(pid_t pid, JobStatus status, const char *command);
void set_job_state(pid_t pid, JobStatus status);
void remove_job(pid_t pid);
int find_current_fg_job(void);
int find_bg_stopped_job(void);
int get_stopped_job(void);
void list_jobs(void);

#endif