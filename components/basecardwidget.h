#ifndef BASECARDWIDGET_H
#define BASECARDWIDGET_H

#include <QFrame>
#include <QMouseEvent>

class BaseCardWidget : public QFrame
{
    Q_OBJECT
public:
    explicit BaseCardWidget(QWidget *parent = nullptr, bool clickable = false);

    void setHoverEnabled(bool enabled);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

signals:
    void clicked();

private:
    bool m_clickable;
    bool m_hoverEnabled;
};

#endif