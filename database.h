#ifndef DATABASE_H
#define DATABASE_H

#include <string>

// Initializes the database, creates table and default user if they don't exist.
void init_database();

// Authenticates a user against the database.
bool authenticate_user(const std::string& username, const std::string& password);

#endif // DATABASE_H

