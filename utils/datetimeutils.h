#ifndef DATETIMEUTILS_H
#define DATETIMEUTILS_H

#include <QString>
#include "../models/course.h"

namespace DateTimeUtils {

inline QString dayText(int day)
{
    switch (day) {
    case 1: return "周一";
    case 2: return "周二";
    case 3: return "周三";
    case 4: return "周四";
    case 5: return "周五";
    case 6: return "周六";
    case 7: return "周日";
    default: return "未设置";
    }
}

inline QString weekTypeText(int weekType)
{
    switch (weekType) {
    case 1: return "单周";
    case 2: return "双周";
    default: return "每周";
    }
}

inline QString scheduleLine(const Course& course)
{
    if (course.day < 1 || course.day > 7 || course.startPeriod <= 0 || course.endPeriod <= 0) {
        return QString();
    }

    QString line = QString("%1 %2-%3节").arg(dayText(course.day)).arg(course.startPeriod).arg(course.endPeriod);
    if (course.weekType == 1) {
        line += "（单周）";
    } else if (course.weekType == 2) {
        line += "（双周）";
    }
    return line;
}

inline QString scheduleSummaryForGroup(const QList<Course>& courses, const QList<int>& indices)
{
    QStringList lines;
    for (int index : indices) {
        const QString line = scheduleLine(courses[index]);
        if (!line.isEmpty() && !lines.contains(line)) {
            lines.append(line);
        }
    }
    return lines.join("\n");
}

inline QString safeText(const QString& text, const QString& fallback)
{
    return text.trimmed().isEmpty() ? fallback : text;
}

}

#endif // DATETIMEUTILS_H