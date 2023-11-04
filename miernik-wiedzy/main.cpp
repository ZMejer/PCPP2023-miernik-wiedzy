#include "mainwindow.h"

#include <QApplication>
#include <mysql/mysql.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    MainWindow window;
    window.resize(1100,700);
    window.show();

    return app.exec();
}
