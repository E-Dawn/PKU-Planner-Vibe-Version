#ifndef PAGEANIMATOR_H
#define PAGEANIMATOR_H

#include <QWidget>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QEasingCurve>

class PageAnimator
{
public:
    static void slideToPage(QStackedWidget *stack, QWidget *targetPage);
    static void slideToIndex(QStackedWidget *stack, int targetIndex);

private:
    static bool isAnimating;
};

#endif