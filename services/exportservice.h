#ifndef EXPORTSERVICE_H
#define EXPORTSERVICE_H

#include <QString>
#include <QList>
#include "../models/task.h"
#include "../models/course.h"

class ExportService
{
public:
    static bool exportCSV(const QList<Task>& tasks, const QString& filePath);
    static bool exportTXTReport(const QList<Task>& tasks, const QList<Course>& courses, const QString& filePath);
};

#endif