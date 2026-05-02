#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractTableModel>
#include "task.h"
#include <vector>

class TaskModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TaskModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;

    QVariant data(const QModelIndex &, int role) const override;
    QVariant headerData(int, Qt::Orientation, int) const override;

    void addTask(const Task &task);

private:
    std::vector<Task> tasks;
};

#endif