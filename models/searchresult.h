#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QString>

struct SearchResult {
    enum Type { Course, Task, File } type;
    QString title;
    QString subtitle;
    QString id;
    QString icon;
};

#endif // SEARCHRESULT_H