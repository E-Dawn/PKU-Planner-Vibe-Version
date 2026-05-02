#include "taskmodel.h"
#include <QColor>
#include <QBrush> // 如果你要返回复杂的背景刷

TaskModel::TaskModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    // 测试数据
    tasks.push_back({"数据结构", "实验报告", QDateTime::currentDateTime().addDays(2), 2});
    tasks.push_back({"操作系统", "Lab1", QDateTime::currentDateTime().addDays(-1), 1});
}

int TaskModel::rowCount(const QModelIndex &) const
{
    return tasks.size();
}

int TaskModel::columnCount(const QModelIndex &) const
{
    return 5;
}

QVariant TaskModel::headerData(int section, Qt::Orientation o, int role) const
{
    if(role != Qt::DisplayRole || o != Qt::Horizontal) return {};

    switch(section)
    {
    case 0: return "课程";
    case 1: return "任务";
    case 2: return "DDL";
    case 3: return "剩余时间";
    case 4: return "优先级";
    }
    return {};
}

QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    const Task &t = tasks[index.row()];

    // 显示内容
    if(role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0: return t.course;
        case 1: return t.title;
        case 2: return t.deadline.toString("MM-dd hh:mm");
        case 3:
            if(t.isOverdue()) return "已逾期";
            return QString("%1 天").arg(t.daysLeft());
        case 4:
            return t.priority == 2 ? "高" : (t.priority == 1 ? "中" : "低");
        }
    }

    // 行背景（核心视觉）
    if(role == Qt::BackgroundRole)
    {
        if(t.isOverdue()) return QColor("#FFEAEA");
        if(t.daysLeft() <= 1) return QColor("#FFF3E0");
    }

    return {};
}

void TaskModel::addTask(const Task &task)
{
    beginInsertRows(QModelIndex(), tasks.size(), tasks.size());
    tasks.push_back(task);
    endInsertRows();
}