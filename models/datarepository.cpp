#include "datarepository.h"

#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QCoreApplication>
#include <QSaveFile>
#include <QStandardPaths>
#include <QDebug>

QString DataRepository::dataDirectory()
{
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (dataPath.isEmpty()) {
        dataPath = QCoreApplication::applicationDirPath();
    }
    QDir dir(dataPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    return dataPath;
}

DataRepository::DataRepository(const QString& storageDir)
    : m_storageDir(storageDir.isEmpty() ? dataDirectory() : storageDir)
{
}

void DataRepository::setStorageDir(const QString& dir)
{
    m_storageDir = dir.isEmpty() ? dataDirectory() : dir;
}

QString DataRepository::storageDir() const
{
    return m_storageDir;
}

bool DataRepository::load()
{
    QList<Course> courses;
    QList<Task> tasks;
    bool coursesLoaded = loadCourses(courses);
    bool tasksLoaded = loadTasks(tasks);
    return coursesLoaded || tasksLoaded;
}

bool DataRepository::save() const
{
    return true;
}

void DataRepository::clearDisk() const
{
    QString dir = m_storageDir.isEmpty() ? dataDirectory() : m_storageDir;
    QDir(dir).remove("courses.json");
    QDir(dir).remove("courses.bak");
    QDir(dir).remove("tasks.json");
    QDir(dir).remove("tasks.bak");
}

bool DataRepository::loadCourses(QList<Course>& courses) const
{
    QJsonDocument doc;
    if (!loadFromFile("courses.json", doc)) {
        if (!loadFromFile("courses.bak", doc)) {
            courses.clear();
            return false;
        }
    }

    if (!doc.isArray()) {
        courses.clear();
        return false;
    }

    QJsonArray arr = doc.array();
    courses.clear();

    for (const auto& item : arr) {
        if (item.isObject()) {
            courses.append(Course::fromJson(item.toObject()));
        }
    }
    return true;
}

bool DataRepository::saveCourses(const QList<Course>& courses) const
{
    QJsonArray arr;
    for (const auto& course : courses) {
        arr.append(course.toJson());
    }

    QJsonDocument doc(arr);
    return saveToFile("courses.json", doc);
}

bool DataRepository::loadTasks(QList<Task>& tasks) const
{
    QJsonDocument doc;
    if (!loadFromFile("tasks.json", doc)) {
        if (!loadFromFile("tasks.bak", doc)) {
            tasks.clear();
            return false;
        }
    }

    if (!doc.isArray()) {
        tasks.clear();
        return false;
    }

    QJsonArray arr = doc.array();
    tasks.clear();

    for (const auto& item : arr) {
        if (item.isObject()) {
            tasks.append(Task::fromJson(item.toObject()));
        }
    }
    return true;
}

bool DataRepository::saveTasks(const QList<Task>& tasks) const
{
    QJsonArray arr;
    for (const auto& task : tasks) {
        QJsonObject obj;
        obj["course"] = task.course;
        obj["title"] = task.title;
        obj["deadline"] = task.deadline.toString(Qt::ISODate);
        obj["priority"] = task.priority;
        obj["completed"] = task.completed;
        if (task.completed) {
            if (task.completedAt.isValid()) {
                obj["completedAt"] = task.completedAt.toString(Qt::ISODate);
            } else {
                obj["completedAt"] = QDateTime::currentDateTime().toString(Qt::ISODate);
            }
        }
        arr.append(obj);
    }

    QJsonDocument doc(arr);
    return saveToFile("tasks.json", doc);
}

bool DataRepository::loadFromFile(const QString& filename, QJsonDocument& doc) const
{
    QString dataDir = m_storageDir.isEmpty() ? dataDirectory() : m_storageDir;
    QString fullPath = QDir(dataDir).absoluteFilePath(filename);

    QFile file(fullPath);

    if (!file.exists()) {
        return false;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError || doc.isNull()) {
        QString backupPath = fullPath + "." + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".corrupted";
        QFile::copy(fullPath, backupPath);
        return false;
    }

    return true;
}

bool DataRepository::saveToFile(const QString& filename, const QJsonDocument& doc) const
{
    QString dataDir = m_storageDir.isEmpty() ? dataDirectory() : m_storageDir;
    QString target = QDir(dataDir).absoluteFilePath(filename);

    QSaveFile file(target);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented));

    if (!file.commit()) {
        return false;
    }

    return true;
}