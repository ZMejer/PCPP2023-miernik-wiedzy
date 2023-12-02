#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include "DatabaseHandler.hpp"
#include <algorithm>
#include <random>
#include <QPushButton>
#include <QProgressBar>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , connection("127.0.0.1", "root", "password", "fizyka", 3307)
{
    currentQuestionIndex = 0;
    correctlyAnsweredQuestions = 0;

    ui->setupUi(this);
    this->setWindowTitle("Miernik Wiedzy");
    this->setStyleSheet("background-color: #1A1529;");

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

    ui->sectionButton_1->setCursor(Qt::PointingHandCursor);
    ui->sectionButton_2->setCursor(Qt::PointingHandCursor);
    ui->sectionButton_3->setCursor(Qt::PointingHandCursor);
    ui->sectionButton_4->setCursor(Qt::PointingHandCursor);
    ui->sectionButton_1->setStyleSheet(buttonStyle);
    ui->sectionButton_2->setStyleSheet(buttonStyle);
    ui->sectionButton_3->setStyleSheet(buttonStyle);
    ui->sectionButton_4->setStyleSheet(buttonStyle);
    ui->sectionButton_1->setGeometry(250, 150 + 0 * 75, 500, 60);
    ui->sectionButton_2->setGeometry(250, 150 + 1 * 75, 500, 60);
    ui->sectionButton_3->setGeometry(250, 150 + 2 * 75, 500, 60);
    ui->sectionButton_4->setGeometry(250, 150 + 3 * 75, 500, 60);
    connect(ui->sectionButton_1, SIGNAL(clicked()), this, SLOT(selectSection()));
    connect(ui->sectionButton_2, SIGNAL(clicked()), this, SLOT(selectSection()));
    connect(ui->sectionButton_3, SIGNAL(clicked()), this, SLOT(selectSection()));
    connect(ui->sectionButton_4, SIGNAL(clicked()), this, SLOT(selectSection()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectSection(){
    QObject* senderObject = QObject::sender();
    if (QPushButton* clickedButton = qobject_cast<QPushButton*>(senderObject)) {
        QString buttonText = clickedButton->text();
        std::vector<std::string> result = connection.executeAndFetch("select id from dzialy where nazwa='"+buttonText.toStdString()+"'");
        sectionId = std::stoi(result[0]);
    }
    fetchDataFromDatabase(sectionId);
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
    ui->QuestionLabel->setStyleSheet("font-size: 22px; color: white; font-weight:bold;");
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


    QString progressBarStyle = "QProgressBar {"
                               "    border: 0;"
                               "    border-radius: 5px;"
                               "    background-color:#6C6482;"
                               "}"
                               "QProgressBar::chunk {"
                               "    border-radius:5px;"
                               "    background-color:#6EA474;"
                               "}";
    ui->AnsweredQuestionsProgress->setRange(0,100);
    ui->AnsweredQuestionsProgress->setValue(0);
    ui->AnsweredQuestionsProgress->setStyleSheet(progressBarStyle);
    ui->AnsweredQuestionsProgress->setTextVisible(false);
    ui->MasteredQuestionsProgress->setRange(0,100);
    ui->MasteredQuestionsProgress->setValue(0);
    ui->MasteredQuestionsProgress->setStyleSheet(progressBarStyle);
    ui->MasteredQuestionsProgress->setTextVisible(false);
    ui->AnsweredQuestionsProgress->setFixedHeight(10);
    ui->MasteredQuestionsProgress->setFixedHeight(10);

    ui->AnsweredQuestionsNumbers->setText(QString::fromStdString(std::to_string(currentQuestionIndex)+"/"+std::to_string(questionContents.size())));
    ui->AnsweredQuestionsNumbers->setStyleSheet("color:white; font-size:16px;");

    ui->MasteredQuestionsNumbers->setText(QString::fromStdString(std::to_string(correctlyAnsweredQuestions)+"/"+std::to_string(questionContents.size())));
    ui->MasteredQuestionsNumbers->setStyleSheet("color:white; font-size:16px;");
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::fetchDataFromDatabase(int sectionId) {
    questionContents = connection.executeAndFetch("select pytanie from pytania where dzial_id='"+std::to_string(sectionId)+"' order by id");
    correctAnswers = connection.executeAndFetch("select poprawna from odpowiedzi where pytanie_id in(select id from pytania where dzial_id='"+std::to_string(sectionId)+"') order by pytanie_id");
    wrongAnswers_1 = connection.executeAndFetch("select bledna_1 from odpowiedzi where pytanie_id in(select id from pytania where dzial_id='"+std::to_string(sectionId)+"') order by pytanie_id");
    wrongAnswers_2 = connection.executeAndFetch("select bledna_2 from odpowiedzi where pytanie_id in(select id from pytania where dzial_id='"+std::to_string(sectionId)+"') order by pytanie_id");
    wrongAnswers_3 = connection.executeAndFetch("select bledna_3 from odpowiedzi where pytanie_id in(select id from pytania where dzial_id='"+std::to_string(sectionId)+"') order by pytanie_id");

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

    QLabel *AnsweredQuestions = ui->AnsweredQuestionsLabel;
    QProgressBar *AnsweredProgress = ui->AnsweredQuestionsProgress;
    QLabel *AnsweredNumbers = ui->AnsweredQuestionsNumbers;
    if (AnsweredQuestions && AnsweredProgress && AnsweredNumbers) {
        AnsweredQuestions->setFixedWidth(0.4 * event->size().width());
        AnsweredQuestions->move(0.7*event->size().width(),175);
        AnsweredProgress->move(0.7*event->size().width(),210);
        AnsweredNumbers->move(0.7*event->size().width()+90,230);
    }
    QLabel *MasteredQuestions = ui->MasteredQuestionsLabel;
    QProgressBar *MasteredProgress = ui->MasteredQuestionsProgress;
    QLabel *MasteredNumbers = ui->MasteredQuestionsNumbers;
    if (MasteredQuestions && MasteredProgress && MasteredNumbers) {
        MasteredQuestions->setFixedWidth(0.4 * event->size().width());
        MasteredQuestions->move(0.7*event->size().width(),325);
        MasteredProgress->move(0.7*event->size().width(),360);
        MasteredNumbers->move(0.7*event->size().width()+90,380);
    }
}

void MainWindow::loadNextQuestion() {

    //QThread::sleep(1);

    fetchDataFromDatabase(sectionId);

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

    QObject* senderObject = QObject::sender();
    if (QPushButton* clickedButton = qobject_cast<QPushButton*>(senderObject)) {
        QString buttonText = clickedButton->text();
        if(buttonText == QString::fromStdString(correctAnswers[currentQuestionIndex])){
            correctlyAnsweredQuestions += 1;
        }
    }

    ui->AnsweredQuestionsNumbers->setText(QString::fromStdString(std::to_string(currentQuestionIndex+1)+"/"+std::to_string(questionContents.size())));
    ui->AnsweredQuestionsProgress->setValue(100*(currentQuestionIndex+1)/questionContents.size());

    if (currentQuestionIndex < questionContents.size() - 1) {
        currentQuestionIndex++;
    } else {
        // tu będzie koniec testu
        return;
    }

    ui->MasteredQuestionsNumbers->setText(QString::fromStdString(std::to_string(correctlyAnsweredQuestions)+"/"+std::to_string(questionContents.size())));
    ui->MasteredQuestionsProgress->setValue(100*(correctlyAnsweredQuestions)/questionContents.size());

    ui->QuestionLabel->setText(QString::fromStdString(questionContents[currentQuestionIndex]));
    ui->answerButton_1->setText(QString::fromStdString(allAnswers[currentQuestionIndex][0]));
    ui->answerButton_2->setText(QString::fromStdString(allAnswers[currentQuestionIndex][1]));
    ui->answerButton_3->setText(QString::fromStdString(allAnswers[currentQuestionIndex][2]));
    ui->answerButton_4->setText(QString::fromStdString(allAnswers[currentQuestionIndex][3]));
}

