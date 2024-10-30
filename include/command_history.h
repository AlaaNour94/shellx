#include <readline/readline.h>
#include <readline/history.h>
#include <sqlite3.h>


int add_records_to_history(void *, int , char **, char **);
void setup_history_db();
void populate_history_from_db();
void insert_history_to_db(char *);
void close_history_db();