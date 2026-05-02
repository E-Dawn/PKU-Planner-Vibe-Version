#ifndef COURSEACTIONDIALOG_H
#define COURSEACTIONDIALOG_H

#include <QDialog>

class CourseActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseActionDialog(QWidget *parent=nullptr);

    bool editSelected() const;
    bool deleteSelected() const;
    bool ddlSelected() const;

private:
    bool editChoice=false;
    bool deleteChoice=false;
    bool ddlChoice=false;
};

#endif