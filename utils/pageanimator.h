#ifndef PAGEANIMATOR_H
#define PAGEANIMATOR_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QEasingCurve>

class PageAnimator
{
public:
    static void slideTransition(QWidget *from, QWidget *to, bool forward = true) {
        if (!from || !to) return;

        from->setVisible(false);
        to->setVisible(true);
    }

    static void fadeTransition(QWidget *from, QWidget *to) {
        if (!from || !to) return;

        QPropertyAnimation *animation = new QPropertyAnimation(from, "windowOpacity");
        animation->setDuration(200);
        animation->setStartValue(1.0);
        animation->setEndValue(0.0);
        animation->setEasingCurve(QEasingCurve::InOutQuad);
        animation->start(QPropertyAnimation::DeleteWhenStopped);

        from->setVisible(false);
        to->setVisible(true);
        to->setWindowOpacity(0);
        to->show();

        QPropertyAnimation *fadeIn = new QPropertyAnimation(to, "windowOpacity");
        fadeIn->setDuration(200);
        fadeIn->setStartValue(0.0);
        fadeIn->setEndValue(1.0);
        fadeIn->setEasingCurve(QEasingCurve::InOutQuad);
        fadeIn->start(QPropertyAnimation::DeleteWhenStopped);
    }
};

#endif