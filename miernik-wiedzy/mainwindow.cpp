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
    , connection("127.0.0.1", "root", "password", "fizyka", 3307)
{
    currentQuestionIndex = 0;
    ui->setupUi(this);
    this->setWindowTitle("Miernik Wiedzy");
    this->setStyleSheet("background-color: #1A1529;");

    fetchDataFromDatabase();

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

    ui->QuestionLabel->resize(300, 200);
    ui->QuestionLabel->setWordWrap(true);
    ui->QuestionLabel->setStyleSheet("font-size: 24px; color: white; font-weight:bold;");
    ui->QuestionLabel->setText(QString::fromStdString(questionContents[0]));
    ui->QuestionLabel->move(100,125);

    QString buttonStyle =   "QPushButton {"
                            "   border:none;"
                            "   background-color:#4b455e;"
                            "   color:white; "
                            "   font-weight:bold;"
                            "   font-size:28px;"
                            "   border-radius:5px;"
                            "}"
                            "QPushButton:hover {"
                            "   background-color:#565266;"
                            "}";
    ui->answerButton_1->setText(QString::fromStdString(allAnswers[0][0]));
    ui->answerButton_2->setText(QString::fromStdString(allAnswers[0][1]));
    ui->answerButton_3->setText(QString::fromStdString(allAnswers[0][2]));
    ui->answerButton_4->setText(QString::fromStdString(allAnswers[0][3]));
    ui->answerButton_1->setStyleSheet(buttonStyle);
    ui->answerButton_2->setStyleSheet(buttonStyle);
    ui->answerButton_3->setStyleSheet(buttonStyle);
    ui->answerButton_4->setStyleSheet(buttonStyle);
    ui->answerButton_1->setGeometry(100, 350 + 0 * 75, 500, 60);
    ui->answerButton_2->setGeometry(100, 350 + 1 * 75, 500, 60);
    ui->answerButton_3->setGeometry(100, 350 + 2 * 75, 500, 60);
    ui->answerButton_4->setGeometry(100, 350 + 3 * 75, 500, 60);
    ui->answerButton_1->setCursor(Qt::PointingHandCursor);
    ui->answerButton_2->setCursor(Qt::PointingHandCursor);
    ui->answerButton_3->setCursor(Qt::PointingHandCursor);
    ui->answerButton_4->setCursor(Qt::PointingHandCursor);
    connect(ui->answerButton_1, SIGNAL(clicked()), this, SLOT(loadNextQuestion()));
    connect(ui->answerButton_2, SIGNAL(clicked()), this, SLOT(loadNextQuestion()));
    connect(ui->answerButton_3, SIGNAL(clicked()), this, SLOT(loadNextQuestion()));
    connect(ui->answerButton_4, SIGNAL(clicked()), this, SLOT(loadNextQuestion()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fetchDataFromDatabase() {
    questionContents = connection.executeAndFetch("select pytanie from pytania order by id");
    correctAnswers = connection.executeAndFetch("select poprawna from odpowiedzi order by pytanie_id");
    wrongAnswers_1 = connection.executeAndFetch("select bledna_1 from odpowiedzi order by pytanie_id");
    wrongAnswers_2 = connection.executeAndFetch("select bledna_2 from odpowiedzi order by pytanie_id");
    wrongAnswers_3 = connection.executeAndFetch("select bledna_3 from odpowiedzi order by pytanie_id");
}


void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    QLabel *QuestionLabel = ui->QuestionLabel;
    if (QuestionLabel) {
        QuestionLabel->setFixedWidth(0.5 * event->size().width());
    }

    QList<QPushButton *> answerButtons = findChildren<QPushButton *>();
    for (QPushButton *answerButton : answerButtons) {
        answerButton->setFixedWidth(0.45 * event->size().width());
    }
}

void MainWindow::loadNextQuestion() {

    fetchDataFromDatabase();

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

    if (currentQuestionIndex < questionContents.size() - 1) {
        currentQuestionIndex++;
    } else {
        // tu będzie koniec testu
        return;
    }

    ui->QuestionLabel->setText(QString::fromStdString(questionContents[currentQuestionIndex]));
    ui->answerButton_1->setText(QString::fromStdString(allAnswers[currentQuestionIndex][0]));
    ui->answerButton_2->setText(QString::fromStdString(allAnswers[currentQuestionIndex][1]));
    ui->answerButton_3->setText(QString::fromStdString(allAnswers[currentQuestionIndex][2]));
    ui->answerButton_4->setText(QString::fromStdString(allAnswers[currentQuestionIndex][3]));

}

