#include "mainwindow.h"

#include <QApplication>
#include <mysql/mysql.h>
#include <iostream>
#include <string>

#include "DatabaseHandler.hpp"
#include "Question.hpp"

int main(int argc, char *argv[]) {
    const char *server = "127.0.0.1";
    const char *user = "root";
    const char *password = "password";
    const char *database = "fizyka";
    int port = 3307;

    DatabaseHandler connection(server, user, password, database, port);

    std::vector<std::string> questionContents = connection.getAllQuestionContents();

    QApplication app(argc, argv);

    MainWindow window;
    QLabel *label = new QLabel(&window);

    label->resize(300, 100);
    label->setWordWrap(true);
    label->setStyleSheet("font-size: 18px; color: white");
    label->setText(QString::fromStdString(questionContents[0]));
    label->move(100,125);
    window.show();

    return app.exec();
}
