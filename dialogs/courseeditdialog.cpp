#include "courseeditdialog.h"
#include <QFormLayout>
#include <QVBoxLayout>

CourseEditDialog::CourseEditDialog(int defaultStart, int defaultEnd, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("课程编辑");
    setStyleSheet(R"(
        QDialog {
            background: white;
        }
        QLineEdit {
            border: 1px solid #ddd;
            border-radius: 8px;
            padding: 8px;
        }
        QPushButton {
            background: #8B1E2D;
            color: white;
            border-radius: 8px;
            padding: 8px 16px;
        }
        QPushButton:hover {
            background: #7A1C2C;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();

    nameEdit = new QLineEdit();
    teacherEdit = new QLineEdit();
    locationEdit = new QLineEdit();
    examEdit = new QLineEdit();
    
    startCombo = new QComboBox();
    endCombo = new QComboBox();
    
    for (int i = 1; i <= 12; ++i) {
        startCombo->addItem(QString("第 %1 节").arg(i));
        endCombo->addItem(QString("第 %1 节").arg(i));
    }
    
    startCombo->setCurrentIndex(defaultStart - 1);
    endCombo->setCurrentIndex(defaultEnd - 1);

    formLayout->addRow("课程名称:", nameEdit);
    formLayout->addRow("教师:", teacherEdit);
    formLayout->addRow("地点:", locationEdit);
    formLayout->addRow("考试时间:", examEdit);
    formLayout->addRow("开始节次:", startCombo);
    formLayout->addRow("结束节次:", endCombo);

    mainLayout->addLayout(formLayout);

    QDialogButtonBox *buttons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
    );
    
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    mainLayout->addWidget(buttons);
}

QString CourseEditDialog::getName() const {
    return nameEdit->text();
}

QString CourseEditDialog::getTeacher() const {
    return teacherEdit->text();
}

QString CourseEditDialog::getLocation() const {
    return locationEdit->text();
}

QString CourseEditDialog::getExamTime() const {
    return examEdit->text();
}

int CourseEditDialog::getStart() const {
    return startCombo->currentIndex() + 1;
}

int CourseEditDialog::getEnd() const {
    return endCombo->currentIndex() + 1;
}

void CourseEditDialog::setCourseData(const QString &name, const QString &teacher,
                                   const QString &location, const QString &examTime,
                                   int start, int end) {
    nameEdit->setText(name);
    teacherEdit->setText(teacher);
    locationEdit->setText(location);
    examEdit->setText(examTime);
    startCombo->setCurrentIndex(start - 1);
    endCombo->setCurrentIndex(end - 1);
}