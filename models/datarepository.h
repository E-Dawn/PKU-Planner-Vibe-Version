#ifndef DATAREPOSITORY_H
#define DATAREPOSITORY_H

#include <QString>
#include <QJsonDocument>
#include "course.h"
#include "task.h"

class DataRepository
{
public:
    explicit DataRepository(const QString& storageDir);

    bool loadCourses(QList<Course>& courses) const;
    bool saveCourses(const QList<Course>& courses) const;
    bool loadTasks(QList<Task>& tasks) const;
    bool saveTasks(const QList<Task>& tasks) const;

    bool load();
    bool save() const;
    void clearDisk() const;

    void setStorageDir(const QString& dir);
    QString storageDir() const;

    static QString dataDirectory();

private:
    bool loadFromFile(const QString& filename, QJsonDocument& doc) const;
    bool saveToFile(const QString& filename, const QJsonDocument& doc) const;

    QString m_storageDir;
};

#endif // DATAREPOSITORY_H