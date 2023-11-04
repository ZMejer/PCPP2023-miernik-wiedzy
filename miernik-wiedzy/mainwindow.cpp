#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include "DatabaseHandler.hpp"
#include <algorithm>
#include <random>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Miernik Wiedzy");
    this->setStyleSheet("background-color: #1A1529;");


    const char *server = "127.0.0.1";
    const char *user = "root";
    const char *password = "password";
    const char *database = "fizyka";
    int port = 3307;
    DatabaseHandler connection(server, user, password, database, port);
    std::vector<std::string> questionContents = connection.executeAndFetch("select pytanie from pytania order by id");
    std::vector<std::string> correctAnswers = connection.executeAndFetch("select poprawna from odpowiedzi order by pytanie_id");
    std::vector<std::string> wrongAnswers_1 = connection.executeAndFetch("select bledna_1 from odpowiedzi order by pytanie_id");
    std::vector<std::string> wrongAnswers_2 = connection.executeAndFetch("select bledna_2 from odpowiedzi order by pytanie_id");
    std::vector<std::string> wrongAnswers_3 = connection.executeAndFetch("select bledna_3 from odpowiedzi order by pytanie_id");


    auto shuffleAnswers = [](std::vector<std::string>& answers) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(answers.begin(), answers.end(), g);
    };

    std::vector<std::vector<std::string>> allAnswers;
    for (size_t i = 0; i < questionContents.size(); ++i) {
        std::vector<std::string> answersForRow;
        answersForRow.push_back(correctAnswers[i]);
        answersForRow.push_back(wrongAnswers_1[i]);
        answersForRow.push_back(wrongAnswers_2[i]);
        answersForRow.push_back(wrongAnswers_3[i]);
        shuffleAnswers(answersForRow);
        allAnswers.push_back(answersForRow);
    }

    QLabel *QuestionLabel = new QLabel(this);
    QuestionLabel->resize(300, 200);
    QuestionLabel->setWordWrap(true);
    QuestionLabel->setStyleSheet("font-size: 24px; color: white; font-weight:bold;");
    QuestionLabel->setText(QString::fromStdString(questionContents[0]));
    QuestionLabel->move(100,125);

    for (size_t i = 0; i < allAnswers[0].size(); ++i) {
        QPushButton *answerButton = new QPushButton(QString::fromStdString(allAnswers[0][i]), this);
        answerButton->setGeometry(100, 350 + i * 75, 500, 60);
        answerButton->setCursor(Qt::PointingHandCursor);
        answerButton->setStyleSheet("QPushButton {"
                                    "   border:none;"
                                    "   background-color:#4b455e;"
                                    "   color:white; "
                                    "   font-weight:bold;"
                                    "   font-size:28px;"
                                    "   border-radius:5px;"
                                    "}"
                                    "QPushButton:hover {"
                                    "   background-color:#565266;"
                                    "}");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    QLabel *QuestionLabel = findChild<QLabel *>();
    if (QuestionLabel) {
        QuestionLabel->setFixedWidth(0.5 * event->size().width());
    }

    QList<QPushButton *> answerButtons = findChildren<QPushButton *>();
    for (QPushButton *answerButton : answerButtons) {
        answerButton->setFixedWidth(0.45 * event->size().width());
    }
}
