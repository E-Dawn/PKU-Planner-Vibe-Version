#include "datastore.h"

DataStore::DataStore(QObject *parent) : QObject(parent) {}

// IDataStore ---------------------------------------------------------------
QList<Course> DataStore::courses() const { return m_courses; }
void DataStore::addCourse(const Course& c) { m_courses.append(c); emit coursesChanged(); }
void DataStore::updateCourse(int index, const Course& c) {
    if (index >= 0 && index < m_courses.size()) {
        m_courses[index] = c; emit coursesChanged();
    }
}
void DataStore::deleteCourse(int index) {
    if (index >= 0 && index < m_courses.size()) {
        m_courses.removeAt(index); emit coursesChanged();
    }
}

QList<Task> DataStore::tasks() const { return m_tasks; }
void DataStore::addTask(const Task& t) { m_tasks.append(t); emit tasksChanged(); }
void DataStore::updateTask(int index, const Task& t) {
    if (index >= 0 && index < m_tasks.size()) { m_tasks[index] = t; emit tasksChanged(); }
}
void DataStore::deleteTask(int index) {
    if (index >= 0 && index < m_tasks.size()) { m_tasks.removeAt(index); emit tasksChanged(); }
}
void DataStore::markTaskCompleted(int index, bool completed) {
    if (index >= 0 && index < m_tasks.size()) { m_tasks[index].completed = completed; emit tasksChanged(); }
}
