#ifndef SIGNALS_H
#define SIGNALS_H

#include "shell.h"
#include "job_control.h"

void setup_signal_handlers(void);
void handle_sigint(int sig);
void handle_sigchild(int sig);
void handle_sigtstp(int sig);

#endif