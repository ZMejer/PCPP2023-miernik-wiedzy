#include "mainwindow.h"

#include <QApplication>
#include <mysql/mysql.h>
#include <iostream>

#include "DatabaseHandler.hpp"

int main(int argc, char *argv[]) {
    const char *server = "127.0.0.1";
    const char *user = "root";
    const char *password = "password";
    const char *database = "fizyka";
    int port = 3307;

    DatabaseHandler dataHandler(server, user, password, database, port);

    if (!dataHandler.executeQuery("select * from dzialy")) {
        return EXIT_FAILURE;
    }

    MYSQL_RES *res = dataHandler.storeResult();
    if (res == NULL) {
        return EXIT_FAILURE;
    }

    int num_fields = mysql_num_fields(res);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(res);

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
