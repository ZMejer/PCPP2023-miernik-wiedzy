#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <mysql/mysql.h>

class DatabaseHandler {
private:
    MYSQL *conn;

public:
    DatabaseHandler(const char *server, const char *user, const char *password, const char *database, int port);
    ~DatabaseHandler();
    bool executeQuery(const char *query);
    MYSQL_RES *storeResult();
};

#endif
