#include "settingspage.h"
#include "../ui/theme.h"
#include "../models/datamanager.h"
#include <QLabel>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDateTime>

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet(QString("background:%1;").arg(Theme::BACKGROUND));

    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(24, 24, 24, 24);
    root->setSpacing(16);

    QLabel *title = new QLabel("设置", this);
    title->setStyleSheet(QString("font-size:24px;font-weight:700;color:%1;").arg(Theme::TEXT_PRIMARY));
    root->addWidget(title);

    QGroupBox *reminderGroup = new QGroupBox("提醒设置", this);
    reminderGroup->setStyleSheet(QString("QGroupBox{font-weight:600;color:%1;margin-top:12px;} QGroupBox::title{subcontrol-origin:margin;}").arg(Theme::TEXT_PRIMARY));
    QVBoxLayout *reminderLayout = new QVBoxLayout(reminderGroup);

    reminderCheck = new QCheckBox("启用DDL提醒", this);
    reminderCheck->setStyleSheet(QString("font-size:14px;color:%1;").arg(Theme::TEXT_PRIMARY));
    reminderLayout->addWidget(reminderCheck);

    QHBoxLayout *intervalRow = new QHBoxLayout;
    QLabel *intervalLabel = new QLabel("提醒间隔:", this);
    intervalLabel->setStyleSheet(QString("color:%1;font-size:14px;").arg(Theme::TEXT_SECONDARY));
    reminderInterval = new QComboBox(this);
    reminderInterval->addItems({"15分钟", "30分钟", "1小时", "2小时"});
    reminderInterval->setStyleSheet(QString("QComboBox{border:1px solid %1;border-radius:8px;padding:8px;background:white;color:%2;}").arg(Theme::BORDER).arg(Theme::TEXT_PRIMARY));
    intervalRow->addWidget(intervalLabel);
    intervalRow->addWidget(reminderInterval);
    intervalRow->addStretch();
    reminderLayout->addLayout(intervalRow);

    root->addWidget(reminderGroup);

    QGroupBox *dataGroup = new QGroupBox("数据管理", this);
    dataGroup->setStyleSheet(QString("QGroupBox{font-weight:600;color:%1;margin-top:12px;} QGroupBox::title{subcontrol-origin:margin;}").arg(Theme::TEXT_PRIMARY));
    QVBoxLayout *dataLayout = new QVBoxLayout(dataGroup);

    QHBoxLayout *exportRow = new QHBoxLayout;
    exportBtn = new QPushButton("导出数据 (CSV)", this);
    exportBtn->setCursor(Qt::PointingHandCursor);
    exportBtn->setStyleSheet(QString("QPushButton{background:%1;color:white;border:none;border-radius:12px;padding:12px 20px;font-weight:600;font-size:14px;} QPushButton:hover{background:%2;}").arg(Theme::PRIMARY).arg(Theme::PRIMARY_DARK));
    connect(exportBtn, &QPushButton::clicked, this, &SettingsPage::exportToCSV);
    exportRow->addWidget(exportBtn);
    exportRow->addStretch();
    dataLayout->addLayout(exportRow);

    QLabel *exportTip = new QLabel("导出包含课程和任务数据，可在Excel中打开", this);
    exportTip->setStyleSheet(QString("color:%1;font-size:12px;").arg(Theme::TEXT_TERTIARY));
    dataLayout->addWidget(exportTip);

    root->addWidget(dataGroup);

    root->addStretch();

    loadSettings();

    connect(reminderCheck, &QCheckBox::toggled, this, &SettingsPage::saveSettings);
    connect(reminderInterval, &QComboBox::currentIndexChanged, this, &SettingsPage::saveSettings);
}

void SettingsPage::loadSettings()
{
    reminderCheck->setChecked(true);
    reminderInterval->setCurrentIndex(1);
}

void SettingsPage::saveSettings()
{
    QSettings settings("PKUPlanner", "CourseHelper");
    settings.setValue("reminderEnabled", reminderCheck->isChecked());
    settings.setValue("reminderInterval", reminderInterval->currentIndex());
}

void SettingsPage::exportToCSV()
{
    QString fileName = QFileDialog::getSaveFileName(this, "导出数据",
        QDateTime::currentDateTime().toString("yyyyMMdd") + "_course_helper.csv",
        "CSV Files (*.csv)");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "导出失败", "无法创建文件");
        return;
    }

    QTextStream out(&file);
    out << "类型,名称,详情,截止时间,状态,优先级,创建时间\n";

    const auto courses = DataManager::instance().courses();
    for (const Course& c : courses) {
        out << QString("课程,%1,%2,%3,%4,,,%5\n")
            .arg(c.name).arg(c.teacher).arg(c.location).arg(c.examTime).arg(c.day);
    }

    const auto tasks = DataManager::instance().tasks();
    for (const Task& t : tasks) {
        QString status = t.completed ? "已完成" : (t.isOverdue() ? "逾期" : "进行中");
        QString priority = t.priority == 2 ? "高" : (t.priority == 1 ? "中" : "低");
        out << QString("任务,%1,%2,%3,%4,%5,%6\n")
            .arg(t.title).arg(t.course).arg(t.deadline.toString("yyyy-MM-dd hh:mm"))
            .arg(status).arg(priority).arg(t.hasCompletionTime() ? t.completedAt.toString("yyyy-MM-dd") : "-");
    }

    file.close();

    QMessageBox::information(this, "导出成功", QString("数据已导出到:\n%1").arg(fileName));
}