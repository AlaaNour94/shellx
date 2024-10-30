#include "shell.h"
#include "signals.h"
#include "command_history.h"
#include "command.h"

int main() {
    char cwd[PATH_MAX], prompt[PROMPT_SIZE];
    char *cmdline;

    setup_history_db();
    populate_history_from_db();
    setup_signal_handlers();

    while (1) {
        getcwd(cwd, PATH_MAX);
        snprintf(prompt, sizeof(prompt), COLOR_GREEN "[%s]" COLOR_RESET "%s ", cwd, SHELL_PROMPT);
        cmdline = readline(prompt);
        
        if (cmdline == NULL) break;
        
        if (*cmdline) {
            add_history(cmdline);
            insert_history_to_db(cmdline);
        }
        eval(cmdline);
        free(cmdline);
    }
    
    close_history_db();
    return 0;
}