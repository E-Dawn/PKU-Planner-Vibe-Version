#ifndef TODOPAGE_H
#define TODOPAGE_H

#include <QWidget>
#include <QComboBox>

class QTableView;
class TaskModel;

class TodoPage : public QWidget
{
    Q_OBJECT

public:
    explicit TodoPage(QWidget *parent = nullptr);

private:
    TaskModel *model;
    QTableView *table;
    QComboBox *courseFilter;

    QWidget* createFilterBar();
};

#endif