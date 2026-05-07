#include "exportservice.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QFileInfo>

bool ExportService::exportCSV(const QList<Task>& tasks, const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out << "标题,课程,截止时间,完成状态,完成时间,优先级\n";

    for (const Task& task : tasks) {
        QString title = task.title;
        title.replace("\"", "\"\"");
        QString course = task.course;
        course.replace("\"", "\"\"");

        out << "\"" << title << "\",";
        out << "\"" << course << "\",";
        out << "\"" << task.deadline.toString("yyyy-MM-dd") << "\",";
        out << (task.completed ? "已完成" : "进行中") << ",";
        out << "\"" << (task.completedAt.isValid() ? task.completedAt.toString("yyyy-MM-dd") : "") << "\",";
        QString p = task.priority == 2 ? "高" : (task.priority == 1 ? "中" : "低");
        out << p << "\n";
    }

    file.close();
    return true;
}

bool ExportService::exportTXTReport(const QList<Task>& tasks, const QList<Course>& courses, const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    QDateTime now = QDateTime::currentDateTime();
    out << "=====================================\n";
    out << "       PKU Planner 学习报告\n";
    out << "=====================================\n";
    out << "生成时间: " << now.toString("yyyy-MM-dd HH:mm") << "\n\n";

    int total = tasks.size();
    int completed = 0;
    int overdue = 0;
    int onTime = 0;
    qint64 totalEarlyMinutes = 0;
    int earlyCount = 0;

    QDateTime currentDate = QDateTime::currentDateTime();

    for (const Task& task : tasks) {
        if (task.completed) {
            completed++;
            if (task.completedAt.isValid()) {
                if (task.completedAt <= task.deadline) {
                    onTime++;
                    qint64 earlyMinutes = task.deadline.msecsTo(task.completedAt) / 60000;
                    totalEarlyMinutes += earlyMinutes;
                    earlyCount++;
                }
            }
        } else {
            if (task.deadline < currentDate) {
                overdue++;
            }
        }
    }

    double completionRate = total > 0 ? (completed * 100.0 / total) : 0;
    double onTimeRate = completed > 0 ? (onTime * 100.0 / completed) : 0;
    int avgEarlyMinutes = earlyCount > 0 ? (totalEarlyMinutes / earlyCount) : 0;
    int avgEarlyDays = avgEarlyMinutes / 1440;
    int avgEarlyHours = (avgEarlyMinutes % 1440) / 60;

    out << "----- 任务概览 -----\n";
    out << "任务总数: " << total << "\n";
    out << "已完成: " << completed << "\n";
    out << "进行中: " << (total - completed) << "\n";
    out << "已逾期: " << overdue << "\n";
    out << "\n";

    out << "----- 完成率 -----\n";
    out << QString("完成率: %1%2\n").arg(completionRate, 0, 'f', 1).arg("%");
    out << QString("按时率: %1%2\n").arg(onTimeRate, 0, 'f', 1).arg("%");
    if (avgEarlyDays > 0) {
        out << QString("平均提前完成: %1 天 %2 小时\n").arg(avgEarlyDays).arg(avgEarlyHours);
    } else if (avgEarlyHours > 0) {
        out << QString("平均提前完成: %1 小时\n").arg(avgEarlyHours);
    } else {
        out << "平均提前完成: N/A\n";
    }
    out << "\n";

    out << "----- 课程分布 -----\n";
    QMap<QString, int> courseCount;
    for (const Task& task : tasks) {
        courseCount[task.course]++;
    }
    QStringList sortedCourses = courseCount.keys();
    sortedCourses.sort();
    for (const QString& course : sortedCourses) {
        out << course << ": " << courseCount[course] << " 个任务\n";
    }
    out << "\n";

    if (overdue > 0) {
        out << "----- 逾期任务 -----\n";
        for (const Task& task : tasks) {
            if (!task.completed && task.deadline < currentDate) {
                out << "- " << task.title << " (" << task.course << ")\n";
                out << "  截止时间: " << task.deadline.toString("yyyy-MM-dd") << "\n";
            }
        }
    }

    out << "\n=====================================\n";
    out << "报告结束\n";
    out << "=====================================\n";

    file.close();
    return true;
}