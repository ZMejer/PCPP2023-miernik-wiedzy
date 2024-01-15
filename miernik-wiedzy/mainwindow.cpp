#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include "DatabaseHandler.hpp"
#include <algorithm>
#include <random>
#include <QPushButton>
#include <QProgressBar>
#include <QThread>
#include "WidgetStyles.hpp"
#include <string>
#include <QString>

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

    const int sectionButtonCount = 4;
    QPushButton* sectionButtons[sectionButtonCount] = {
        ui->sectionButton_1,
        ui->sectionButton_2,
        ui->sectionButton_3,
        ui->sectionButton_4
    };

    for (int i = 0; i < sectionButtonCount; i++) {
        WidgetStyles::applyButtonStyle(sectionButtons[i]);
        sectionButtons[i]->setGeometry(250, 150 + i * 75, 500, 60);
        connect(sectionButtons[i], &QPushButton::clicked, this, &MainWindow::selectSection);
    }

    WidgetStyles::applyButtonStyle(ui->returnButton);
    connect(ui->returnButton, &QPushButton::clicked, this, &MainWindow::returnToMainPage);
}

void MainWindow::returnToMainPage() {
    currentQuestionIndex = 0;
    correctlyAnsweredQuestions = 0;
    ui->AnsweredQuestionsNumbers->setText(QString::fromStdString(std::to_string(currentQuestionIndex+1)+"/"+std::to_string(questionContents.size())));
    ui->AnsweredQuestionsProgress->setValue(100*(currentQuestionIndex+1)/questionContents.size());
    ui->stackedWidget->setCurrentIndex(2);
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

    WidgetStyles::applyQuestionLabelStyle(ui->QuestionLabel);
    ui->QuestionLabel->setText(QString::fromStdString(questionContents[0]));

    const int answerButtonCount = 4;
    QPushButton* answerButtons[answerButtonCount] = {
        ui->answerButton_1,
        ui->answerButton_2,
        ui->answerButton_3,
        ui->answerButton_4
    };

    for (int i = 0; i < answerButtonCount; i++) {
        WidgetStyles::applyButtonStyle(answerButtons[i]);
        answerButtons[i]->setText(QString::fromStdString(allAnswers[0][i]));
        answerButtons[i]->setGeometry(100, 350 + i * 75, 500, 60);
        connect(answerButtons[i], SIGNAL(clicked()), this, SLOT(loadNextQuestion()));
    }

    WidgetStyles::applyProgressBarStyle(ui->AnsweredQuestionsProgress);
    WidgetStyles::applyProgressBarStyle(ui->MasteredQuestionsProgress);

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

    QList<QPushButton *> pushButtons = findChildren<QPushButton *>();
    for (QPushButton *pushButton : pushButtons) {
        int ButtonWidth = 0.45 * event->size().width();
        if (pushButton != ui->returnButton) {
            pushButton->setFixedWidth(ButtonWidth);
        }
        else {
            pushButton->move(event->size().width() - pushButton->width()*2, pushButton->y());
        }
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
        else {
            QLabel *QuestionLabel = ui->QuestionLabel;
            QString questionText = QuestionLabel->text();
            std::vector<std::string> subSectionId = connection.executeAndFetch("select rozdzial_id from pytania where pytanie='"+questionText.toStdString()+"' order by id");
            std::vector<std::string> subSection = connection.executeAndFetch("select nazwa from rozdzialy where id='"+subSectionId[0]+"' order by id");
            if (std::find(subSectionsToRevise.begin(), subSectionsToRevise.end(), subSection[0]) == subSectionsToRevise.end()) {
                subSectionsToRevise.push_back(subSection[0]);
            }
        }
    }

    ui->AnsweredQuestionsNumbers->setText(QString::fromStdString(std::to_string(currentQuestionIndex+1)+"/"+std::to_string(questionContents.size())));
    ui->AnsweredQuestionsProgress->setValue(100*(currentQuestionIndex+1)/questionContents.size());

    if (currentQuestionIndex < questionContents.size() - 1) {
        currentQuestionIndex++;
    } else {
        // tu koniec testu
        QString subSectionsText;
        for (size_t i = 1; i < subSectionsToRevise.size(); i++) {
            subSectionsText += "\n" + QString::fromStdString(subSectionsToRevise[i]);
        }
        ui->subSections->setText(subSectionsText);
        ui->stackedWidget->setCurrentIndex(1);
        ui->earnedPointsLabel->setText(QString::fromStdString(std::to_string(correctlyAnsweredQuestions)+"/"+std::to_string(questionContents.size())));
        ui->subSections->setStyleSheet("color: white;");
        ui->earnedPointsLabel->setStyleSheet("color:white; ");
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

