#include "coursecellwidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QToolTip>
#include <QTimer>
#include <QEnterEvent>
#include <QMouseEvent>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>

CourseCellWidget::CourseCellWidget(int row, int col, QWidget *parent)
    : QFrame(parent), m_row(row), m_col(col), m_index(-1)
{
    setMinimumSize(80, 60);

    setStyleSheet(R"(
        QFrame {
            background:#FAFAFA;
            border-radius:10px;
        }
        QFrame:hover {
            background:#FFEAEA;
        }
    )");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(6,6,6,6);

    title = new QLabel("");
    title->setStyleSheet("font-weight:bold; font-size:12px;");
    title->setWordWrap(true);

    info = new QLabel("");
    info->setStyleSheet("font-size:11px; color:#666;");
    info->setWordWrap(true);

    layout->addWidget(title);
    layout->addWidget(info);
}

void CourseCellWidget::setCourse(QString name, QString location, QString teacher, int index)
{
    m_index = index;
    title->setText(name);

    info->setText(
        location + "\n" + teacher
    );

    setStyleSheet(R"(
        QFrame {
            background: #E8F0FF;
            border-radius: 10px;
        }
        QFrame:hover {
            background: #D6E4FF;
        }
    )");
}

void CourseCellWidget::enterEvent(QEnterEvent *)
{
    QTimer::singleShot(300, this, [this]() {
        if(!title->text().isEmpty())
        {
            QToolTip::showText(cursor().pos(),
                title->text() + "\n信息: " + info->text());
        }
    });
}

void CourseCellWidget::leaveEvent(QEvent *)
{
    QToolTip::hideText();
}

void CourseCellWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    if(title->text().isEmpty())
    {
        emit createCourseRequested(m_row, m_col);
    }
    else
    {
        if(m_index != -1)
        {
            emit editCourseRequested(m_index);
        }
    }
}
