#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Miernik Wiedzy");
    this->setStyleSheet("background-color: #1A1529;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

