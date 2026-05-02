#include "taskeditdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QJsonObject>

TaskEditDialog::TaskEditDialog(QWidget *parent, const QString &defaultCourse)
    : QDialog(parent)
{
    setWindowTitle("添加DDL任务");
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QFrame *container = new QFrame(this);
    container->setStyleSheet(R"(
        QFrame{
            background:white;
            border-radius:20px;
        }
    )");

    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(20, 20, 20, 20);
    root->addWidget(container);

    QVBoxLayout *mainLayout = new QVBoxLayout(container);
    QFormLayout *formLayout = new QFormLayout();

    titleEdit = new QLineEdit();
    deadlineEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    deadlineEdit->setCalendarPopup(true);
    priorityCombo = new QComboBox();
    priorityCombo->addItems({"低", "中", "高"});
    hoursSpin = new QSpinBox();
    hoursSpin->setRange(1, 100);
    hoursSpin->setValue(2);
    courseCombo = new QComboBox();
    courseCombo->addItem("请选择课程");

    // 从courses.json加载课程
    QFile courseFile("courses.json");
    if (courseFile.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(courseFile.readAll());
        if (doc.isArray()) {
            QJsonArray courseArray = doc.array();
            for (const auto &item : courseArray) {
                if (item.isObject()) {
                    QJsonObject courseObj = item.toObject();
                    QString courseName = courseObj["name"].toString();
                    if (!courseName.isEmpty()) {
                        courseCombo->addItem(courseName);
                    }
                }
            }
        }
        courseFile.close();
    }

    // 设置默认课程
    if (!defaultCourse.isEmpty()) {
        int index = courseCombo->findText(defaultCourse);
        if (index != -1) {
            courseCombo->setCurrentIndex(index);
        }
    }

    formLayout->addRow("任务标题:", titleEdit);
    formLayout->addRow("截止时间:", deadlineEdit);
    formLayout->addRow("优先级:", priorityCombo);
    formLayout->addRow("预计小时:", hoursSpin);
    formLayout->addRow("所属课程:", courseCombo);

    mainLayout->addLayout(formLayout);

    QDialogButtonBox *buttons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
    );
    
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    mainLayout->addWidget(buttons);

    setStyleSheet(R"(
        QLineEdit {
            border: 1px solid #ddd;
            border-radius: 8px;
            padding: 8px;
        }
        QDateTimeEdit {
            border: 1px solid #ddd;
            border-radius: 8px;
            padding: 8px;
        }
        QComboBox {
            border: 1px solid #ddd;
            border-radius: 8px;
            padding: 8px;
        }
        QSpinBox {
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
}

QString TaskEditDialog::getTitle() const {
    return titleEdit->text();
}

QDateTime TaskEditDialog::getDeadline() const {
    return deadlineEdit->dateTime();
}

int TaskEditDialog::getPriority() const {
    return priorityCombo->currentIndex();
}

int TaskEditDialog::getEstimatedHours() const {
    return hoursSpin->value();
}

QString TaskEditDialog::getCourseName() const {
    return courseCombo->currentText();
}