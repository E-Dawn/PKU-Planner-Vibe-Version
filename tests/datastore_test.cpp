// tests/datastore_test.cpp
#include <QtTest/QtTest>
#include "models/datastore.h"
#include "models/course.h"
#include "models/task.h"

class DataStoreTest : public QObject {
    Q_OBJECT
private slots:
    void testCourseLifecycle() {
        DataStore store;
        Course c; c.name = "Math 101"; c.teacher = "Prof. A";
        // add
        store.addCourse(c);
        QCOMPARE(store.courses().size(), 1);
        QCOMPARE(store.courses().first().name, QString("Math 101"));
        // update
        Course upd = c; upd.name = "Math 102";
        store.updateCourse(0, upd);
        QCOMPARE(store.courses().first().name, QString("Math 102"));
        // delete
        store.deleteCourse(0);
        QCOMPARE(store.courses().size(), 0);
    }

    void testTaskLifecycle() {
        DataStore store;
        Task t; t.title = "Homework 1"; t.completed = false;
        // add
        store.addTask(t);
        QCOMPARE(store.tasks().size(), 1);
        QCOMPARE(store.tasks().first().title, QString("Homework 1"));
        // mark completed
        store.markTaskCompleted(0, true);
        QCOMPARE(store.tasks().first().completed, true);
        QVERIFY(store.tasks().first().completedAt.isValid());
        // update title
        Task upd = t; upd.title = "Homework 1 – revised";
        store.updateTask(0, upd);
        QCOMPARE(store.tasks().first().title, QString("Homework 1 – revised"));
        // delete
        store.deleteTask(0);
        QCOMPARE(store.tasks().size(), 0);
    }
};

QTEST_MAIN(DataStoreTest)
#include "datastore_test.moc"
