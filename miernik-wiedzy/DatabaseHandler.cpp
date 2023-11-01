#include "DatabaseHandler.hpp"
#include <iostream>

DatabaseHandler::DatabaseHandler(const char *server, const char *user, const char *password, const char *database, int port) {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    if (mysql_real_connect(conn, server, user, password, database, port, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
    }
}

DatabaseHandler::~DatabaseHandler() {
    mysql_close(conn);
}

bool DatabaseHandler::executeQuery(const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return false;
    }
    return true;
}

MYSQL_RES *DatabaseHandler::storeResult() {
    return mysql_store_result(conn);
}
