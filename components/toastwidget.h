#ifndef TOASTWIDGET_H
#define TOASTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QPropertyAnimation>

class ToastWidget : public QWidget
{
    Q_OBJECT
public:
    static void showToast(QWidget *parent, const QString &message, int duration = 3000);

private:
    explicit ToastWidget(QWidget *parent, const QString &message);
    ~ToastWidget();

    void fadeIn();
    void fadeOut();

    QLabel *m_messageLabel;
    QTimer *m_timer;
    QPropertyAnimation *m_animation;
};

#endif