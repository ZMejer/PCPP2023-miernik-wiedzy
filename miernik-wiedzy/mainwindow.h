#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "DatabaseHandler.hpp"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void fetchDataFromDatabase(int sectionId);
    void initializeAnswers();

private slots:
    void loadNextQuestion();
    void selectSection();
    void returnToMainPage();

private:
    Ui::MainWindow *ui;
    QLabel *QuestionLabel;
    std::vector<std::string> questionContents;
    DatabaseHandler connection;
    QPushButton *answerButton;
    std::vector<std::string> allAnswers;
    int currentQuestionIndex;
    std::vector<std::string> correctAnswers;
    std::vector<std::string> wrongAnswers_1;
    std::vector<std::string> wrongAnswers_2;
    std::vector<std::string> wrongAnswers_3;
    int correctlyAnsweredQuestions;
    int sectionId;
};
#endif // MAINWINDOW_H
