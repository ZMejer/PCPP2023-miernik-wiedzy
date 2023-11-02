#include "mainwindow.h"

#include <QApplication>
#include <mysql/mysql.h>
#include <iostream>

#include "DatabaseHandler.hpp"
#include "Question.hpp"

int main(int argc, char *argv[]) {
    const char *server = "127.0.0.1";
    const char *user = "root";
    const char *password = "password";
    const char *database = "fizyka";
    int port = 3307;

    DatabaseHandler connection(server, user, password, database, port);

    if (!connection.executeQuery("select * from pytania")) {
        return EXIT_FAILURE;
    }

    MYSQL_RES *res = connection.storeResult();
    if (res == NULL) {
        return EXIT_FAILURE;
    }

    int num_fields = mysql_num_fields(res);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        int id = atoi(row[0]);
        int section_id = atoi(row[1]);
        int chapter_id = atoi(row[2]);
        std::string content = row[3] ? row[3] : "NULL";

        Question question(id, section_id, chapter_id, content);

        printf("Pytanie: %s\n", question.getContent().c_str());
    }
    mysql_free_result(res);

    QApplication app(argc, argv);

    MainWindow window;
    QLabel *label = new QLabel(&window);
    label->setText("Pytanie: ");
    label->setStyleSheet("color:white");
    label->move(100,125);
    window.show();

    return app.exec();
}
