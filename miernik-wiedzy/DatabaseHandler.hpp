#ifndef DATABASEHANDLER_HPP
#define DATABASEHANDLER_HPP

#include <mysql/mysql.h>
#include <iostream>

class DatabaseHandler {
private:
    MYSQL *conn;

public:
    DatabaseHandler(const char *server, const char *user, const char *password, const char *database, int port);
    ~DatabaseHandler();
    bool executeQuery(const char *query);
    MYSQL_RES *storeResult();
    std::vector<std::string> executeAndFetch(const std::string &query);
};

#endif
