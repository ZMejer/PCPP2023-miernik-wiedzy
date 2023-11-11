#include "mainwindow.h"

#include <QApplication>
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <QFile>


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    QFile file(":/qss/style.qss");
    if(file.open(QFile::ReadOnly)) {
        QString StyleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(StyleSheet);
    }

    MainWindow window;
    window.resize(1100,700);
    window.show();

    return app.exec();
}
