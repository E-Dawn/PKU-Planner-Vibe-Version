#ifndef TASKEDITDIALOG_H
#define TASKEDITDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QDateTimeEdit>

class TaskEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskEditDialog(QWidget *parent = nullptr, const QString &defaultCourse = "");

    QString getTitle() const;
    QDateTime getDeadline() const;
    int getPriority() const;
    int getEstimatedHours() const;
    QString getCourseName() const;

private:
    QComboBox *courseCombo;
    QLineEdit *titleEdit;
    QDateTimeEdit *deadlineEdit;
    QComboBox *priorityCombo;
    QSpinBox *hoursSpin;
};

#endif