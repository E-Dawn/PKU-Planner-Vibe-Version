#ifndef ONBOARDINGDIALOG_H
#define ONBOARDINGDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class OnboardingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnboardingDialog(QWidget *parent = nullptr);

signals:
    void createFirstCourseRequested();

private:
    void setupUI();
};

#endif