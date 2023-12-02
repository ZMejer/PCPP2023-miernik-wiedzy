#ifndef WIDGETSTYLES_HPP
#define WIDGETSTYLES_HPP

#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

class WidgetStyles
{
public:
    static void applyButtonStyle(QPushButton* button);
    static void applyProgressBarStyle(QProgressBar* progressBar);
    static void applyQuestionLabelStyle(QLabel* questionLabel);
};

#endif // WIDGETSTYLES_HPP
