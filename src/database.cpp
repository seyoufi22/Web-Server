#include "database.h"
#include <iostream>
#include <sqlite3.h>
#include <vector>

using namespace std;
// Callback function for SQLite queries
static int callback(void* data, int argc, char** argv, char** azColName) {
    vector<string>* rows = static_cast<vector<string>*>(data);
    for (int i = 0; i < argc; i++) {
        rows->push_back(argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

void init_database() {
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    rc = sqlite3_open("/home/ahmed/WebServer/data/users.db", &db);

    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    } else {
        cout << "Opened database successfully" << std::endl;
    }

    // create users table if it doesn't exist
    const char* sql_create_table = "CREATE TABLE IF NOT EXISTS USERS(" \
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                                   "USERNAME TEXT NOT NULL UNIQUE," \
                                   "PASSWORD TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        cout << "Table created successfully" << std::endl;
    }

    // add a default user if doesn't exist
    const char* sql_insert_user = "INSERT OR IGNORE INTO USERS (USERNAME, PASSWORD) VALUES ('admin', 'password');";
    rc = sqlite3_exec(db, sql_insert_user, callback, 0, &zErrMsg);

     if (rc != SQLITE_OK) {
        cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        cout << "Default user checked/created successfully" << std::endl;
    }

    sqlite3_close(db);
}

bool authenticate_user(const std::string& username, const std::string& password) {
    sqlite3* db;
    int rc;

    rc = sqlite3_open("/home/ahmed/WebServer/data/users.db", &db);

    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    string sql = "SELECT COUNT(*) FROM USERS WHERE USERNAME = ? AND PASSWORD = ?;";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return count > 0;
}

