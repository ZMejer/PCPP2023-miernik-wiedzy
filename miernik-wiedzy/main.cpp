#include "mainwindow.h"

#include <QApplication>
#include <mysql/mysql.h>
#include <iostream>

using namespace std;

int main() {
    cout << "Hello World!123" << endl;
    const char *server = "127.0.0.1";  // ustaw nazwę hosta na nazwę usługi bazy danych w docker-compose
    const char *user = "root";
    const char *password = "password";
    const char *database = "db";

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, server, user, password, database, 3307, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        fprintf(stderr, "Error: %s\n", mysql_error(conn));  // log the error
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    if (mysql_query(conn, "SHOW TABLES")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    int num_fields = mysql_num_fields(res);

    while ((row = mysql_fetch_row(res))) {
        for(int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
