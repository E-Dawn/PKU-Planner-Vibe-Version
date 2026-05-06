#include "basecardwidget.h"
#include "../ui/theme.h"

BaseCardWidget::BaseCardWidget(QWidget *parent, bool clickable)
    : QFrame(parent)
    , m_clickable(clickable)
    , m_hoverEnabled(true)
{
    setStyleSheet(QString(
        "QFrame {"
        "   background: %1;"
        "   border-radius: %2px;"
        "   border: 1px solid %3;"
        "}"
    ).arg(Theme::CARD_BG).arg(Theme::CARD_RADIUS).arg(Theme::BORDER));

    if (m_clickable) {
        setCursor(Qt::PointingHandCursor);
    }
}

void BaseCardWidget::setHoverEnabled(bool enabled) {
    m_hoverEnabled = enabled;
    if (!enabled) {
        setStyleSheet(QString(
            "QFrame {"
            "   background: %1;"
            "   border-radius: %2px;"
            "   border: 1px solid %3;"
            "}"
        ).arg(Theme::CARD_BG).arg(Theme::CARD_RADIUS).arg(Theme::BORDER));
    }
}

void BaseCardWidget::enterEvent(QEnterEvent *event) {
    if (m_hoverEnabled && m_clickable) {
        setStyleSheet(QString(
            "QFrame {"
            "   background: %1;"
            "   border-radius: %2px;"
            "   border: 1px solid %3;"
            "}"
        ).arg(Theme::PRIMARY_LIGHT).arg(Theme::CARD_RADIUS).arg(Theme::PRIMARY));
    }
    QFrame::enterEvent(event);
}

void BaseCardWidget::leaveEvent(QEvent *event) {
    if (m_hoverEnabled) {
        setStyleSheet(QString(
            "QFrame {"
            "   background: %1;"
            "   border-radius: %2px;"
            "   border: 1px solid %3;"
            "}"
        ).arg(Theme::CARD_BG).arg(Theme::CARD_RADIUS).arg(Theme::BORDER));
    }
    QFrame::leaveEvent(event);
}