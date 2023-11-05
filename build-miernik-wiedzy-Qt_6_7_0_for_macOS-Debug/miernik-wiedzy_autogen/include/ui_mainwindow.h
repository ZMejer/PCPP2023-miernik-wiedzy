/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *QuestionLabel;
    QPushButton *answerButton_1;
    QPushButton *answerButton_2;
    QPushButton *answerButton_3;
    QPushButton *answerButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(875, 634);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 71, 61));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 40, 141, 21));
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        label_2->setFont(font);
        QuestionLabel = new QLabel(centralwidget);
        QuestionLabel->setObjectName("QuestionLabel");
        QuestionLabel->setGeometry(QRect(80, 130, 141, 21));
        QuestionLabel->setFont(font);
        answerButton_1 = new QPushButton(centralwidget);
        answerButton_1->setObjectName("answerButton_1");
        answerButton_1->setGeometry(QRect(70, 210, 321, 71));
        answerButton_2 = new QPushButton(centralwidget);
        answerButton_2->setObjectName("answerButton_2");
        answerButton_2->setGeometry(QRect(70, 300, 321, 71));
        answerButton_3 = new QPushButton(centralwidget);
        answerButton_3->setObjectName("answerButton_3");
        answerButton_3->setGeometry(QRect(70, 390, 321, 71));
        answerButton_4 = new QPushButton(centralwidget);
        answerButton_4->setObjectName("answerButton_4");
        answerButton_4->setGeometry(QRect(70, 480, 321, 71));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 875, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><body><img src=\":/assets/assets/logo.png\"></body</html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700; color:white;\">Miernik Wiedzy</span></p></body></html>", nullptr));
        QuestionLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700; color:white;\">Question</span></p></body></html>", nullptr));
        answerButton_1->setText(QCoreApplication::translate("MainWindow", "Answer", nullptr));
        answerButton_2->setText(QCoreApplication::translate("MainWindow", "Answer", nullptr));
        answerButton_3->setText(QCoreApplication::translate("MainWindow", "Answer", nullptr));
        answerButton_4->setText(QCoreApplication::translate("MainWindow", "Answer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
