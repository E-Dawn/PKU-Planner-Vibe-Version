#include "toastwidget.h"
#include "../ui/theme.h"
#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>

ToastWidget::ToastWidget(QWidget *parent, const QString &message)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);

    QFrame *container = new QFrame(this);
    container->setStyleSheet(QString(
        "QFrame {"
        "   background: %1;"
        "   border-radius: %2px;"
        "   border: 1px solid %3;"
        "   padding: 12px 20px;"
        "}"
    ).arg(Theme::TEXT_PRIMARY).arg(Theme::CARD_RADIUS).arg(Theme::PRIMARY));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(container);

    m_messageLabel = new QLabel(message, container);
    m_messageLabel->setStyleSheet(QString("color: white; font-size: 14px; font-weight: 500;"));
    m_messageLabel->setWordWrap(true);

    QHBoxLayout *containerLayout = new QHBoxLayout(container);
    containerLayout->setContentsMargins(12, 10, 12, 10);
    containerLayout->addWidget(m_messageLabel);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ToastWidget::fadeOut);
}

ToastWidget::~ToastWidget()
{
}

void ToastWidget::showToast(QWidget *parent, const QString &message, int duration)
{
    ToastWidget *toast = new ToastWidget(parent, message);

    QPoint pos = parent->mapToGlobal(QPoint(parent->width() - 300, 20));
    toast->move(pos);

    toast->show();
    toast->fadeIn();

    QTimer::singleShot(duration, toast, &ToastWidget::fadeOut);
}

void ToastWidget::fadeIn()
{
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(opacity);

    QPropertyAnimation *animation = new QPropertyAnimation(opacity, "opacity", this);
    animation->setDuration(300);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QPropertyAnimation::DeleteWhenStopped);

    m_timer->start(3000);
}

void ToastWidget::fadeOut()
{
    if (!m_timer->isActive()) return;
    m_timer->stop();

    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(opacity);

    QPropertyAnimation *animation = new QPropertyAnimation(opacity, "opacity", this);
    animation->setDuration(300);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    connect(animation, &QPropertyAnimation::finished, this, &QWidget::close);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}