#include "command_history.h"

sqlite3 *db;

int add_records_to_history(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        add_history(argv[i]);
    }
    return 0;
}

void setup_history_db()
{
    int rc;
    char *errMsg = 0;
    rc = sqlite3_open("history.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    // Create a table
    const char *sql = "CREATE TABLE IF NOT EXISTS history (id INTEGER PRIMARY KEY, text TEXT UNIQUE);";
    rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

void populate_history_from_db()
{
    int rc;
    char *errMsg = 0;
    const char *sql = "SELECT text FROM history;";
    rc = sqlite3_exec(db, sql, add_records_to_history, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}

void insert_history_to_db(char *cmdline)
{
    int rc;
    sqlite3_stmt *stmt;

    const char *sql = "INSERT OR IGNORE INTO history (text) VALUES (?);";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Bind the variable `cmdline` to the placeholder `?` in the SQL statement
    sqlite3_bind_text(stmt, 1, cmdline, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    }

    // Finalize the statement to avoid memory leaks
    sqlite3_finalize(stmt);
}

void close_history_db(){
    sqlite3_close(db);
}