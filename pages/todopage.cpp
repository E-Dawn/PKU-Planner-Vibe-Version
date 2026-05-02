#include "todopage.h"
#include "../models/taskmodel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QLineEdit>
#include <QComboBox>
#include <QHeaderView>
#include <QFrame>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

TodoPage::TodoPage(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background:#F7F3EF;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16,16,16,16);

    // ===== 筛选栏 =====
    mainLayout->addWidget(createFilterBar());

    // ===== 表格卡片 =====
    QFrame *card = new QFrame;
    card->setStyleSheet("background:white; border-radius:16px;");

    QVBoxLayout *cardLayout = new QVBoxLayout(card);

    table = new QTableView;
    model = new TaskModel(this);

    table->setModel(model);

    // UI美化
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setVisible(false);

    table->setStyleSheet(R"(
        QTableView {
            border:none;
            background:white;
        }
        QHeaderView::section {
            background:#F5F5F5;
            border:none;
            padding:6px;
        }
    )");

    cardLayout->addWidget(table);

    mainLayout->addWidget(card);
}

QWidget* TodoPage::createFilterBar()
{
    QWidget *bar = new QWidget;

    QHBoxLayout *layout = new QHBoxLayout(bar);
    layout->setContentsMargins(0,0,0,0);

    QLineEdit *search = new QLineEdit;
    search->setPlaceholderText("搜索任务...");

    courseFilter = new QComboBox;
    courseFilter->addItems({"全部课程"});
    
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
                        courseFilter->addItem(courseName);
                    }
                }
            }
        }
    }

    QComboBox *timeFilter = new QComboBox;
    timeFilter->addItems({"全部时间", "今天", "本周", "逾期"});

    QComboBox *statusFilter = new QComboBox;
    statusFilter->addItems({"全部状态", "未完成", "已完成"});

    layout->addWidget(search);
    layout->addWidget(courseFilter);
    layout->addWidget(timeFilter);
    layout->addWidget(statusFilter);

    return bar;
}