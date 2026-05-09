#ifndef TASKCARDWIDGET_H
#define TASKCARDWIDGET_H

#include <QFrame>
#include "../models/task.h"

class QLabel;
class QCheckBox;
class QPushButton;

class TaskCardWidget : public QFrame
{
    Q_OBJECT

signals:
    void completed(const Task &task);
    void edited(const Task &task);
    void deleted(const Task &task);
    void clicked();

public:
    explicit TaskCardWidget(const Task &task, QWidget *parent = nullptr);
    void setTask(const Task &task);
    Task task() const;
    void highlight();

private:
    QString priorityText() const;
    QString countdownText() const;
    QString priorityColor() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    void updateVisualState();

    Task m_task;
    QCheckBox *doneBox;
    QLabel *courseTag;
    QLabel *titleLabel;
    QLabel *priorityBadge;
    QLabel *statusBadge;
    QLabel *deadlineLabel;
    QPushButton *completeBtn;
    QWidget *detailPanel = nullptr;
    bool m_expanded = false;
};

#endif
