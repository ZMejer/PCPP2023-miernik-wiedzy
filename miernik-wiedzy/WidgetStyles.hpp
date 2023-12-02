#ifndef WIDGETSTYLES_HPP
#define WIDGETSTYLES_HPP

#include <QPushButton>
#include <QProgressBar>

class WidgetStyles
{
public:
    static void applyButtonStyle(QPushButton* button);
    static void applyProgressBarStyle(QProgressBar* progressBar);
};

#endif // WIDGETSTYLES_HPP
