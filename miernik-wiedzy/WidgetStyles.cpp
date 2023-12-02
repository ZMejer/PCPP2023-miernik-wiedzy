#include "WidgetStyles.hpp"

void WidgetStyles::applyButtonStyle(QPushButton* button) {
    QString style = "QPushButton {"
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
    button->setCursor(Qt::PointingHandCursor);
    button->setStyleSheet(style);
}

void WidgetStyles::applyProgressBarStyle(QProgressBar *progressBar) {
    QString progressBarStyle = "QProgressBar {"
                               "    border: 0;"
                               "    border-radius: 5px;"
                               "    background-color:#6C6482;"
                               "}"
                               "QProgressBar::chunk {"
                               "    border-radius:5px;"
                               "    background-color:#6EA474;"
                               "}";
    progressBar->setRange(0,100);
    progressBar->setValue(0);
    progressBar->setStyleSheet(progressBarStyle);
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(10);
}

void WidgetStyles::applyQuestionLabelStyle(QLabel *questionLabel) {
    questionLabel->resize(300, 200);
    questionLabel->setWordWrap(true);
    questionLabel->setStyleSheet("font-size: 22px; color: white; font-weight:bold;");
    questionLabel->move(100,125);
}
