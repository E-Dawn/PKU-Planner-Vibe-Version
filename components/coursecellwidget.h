#ifndef COURSECELLWIDGET_H
#define COURSECELLWIDGET_H

#include <QFrame>

class QLabel;
class QMouseEvent;

class CourseCellWidget : public QFrame
{
    Q_OBJECT

public:
    explicit CourseCellWidget(int row = 0, int col = 0, QWidget *parent = nullptr);

    void setCourse(QString name, QString location, QString teacher, int index = -1);

signals:
    void createCourseRequested(int row, int col);
    void editCourseRequested(int index);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QLabel *title;
    QLabel *info;
    int m_row;
    int m_col;
    int m_index = -1;
};

#endif
