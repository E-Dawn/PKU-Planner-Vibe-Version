#include "sidebarwidget.h"
#include "theme.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

SidebarWidget::SidebarWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet(QString(R"(
        QWidget {
            background: %1;
            color: white;
            font-family: 'Microsoft YaHei', 'Segoe UI', Arial;
            font-weight: 500;
        }
    )").arg(Theme::PRIMARY));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 18, 16, 16);
    layout->setSpacing(10);

    QLabel *title = new QLabel("Course Helper");
    title->setStyleSheet("font-size:18px; font-weight:700; padding: 6px 4px; color:#FFF;");
    layout->addWidget(title);

    QLabel *subtitle = new QLabel("管理课程与 DDL");
    subtitle->setStyleSheet("color: rgba(255,255,255,0.85); font-size: 12px; padding-left: 4px;");
    layout->addWidget(subtitle);

    QPushButton *btnDashboard = new QPushButton("课程表");
    QPushButton *btnTodo = new QPushButton("待办");
    QPushButton *btnStats = new QPushButton("📊 统计");

        QString buttonStyle = QString(R"(
            QPushButton {
                background: %1;
                color: %2;
                border: 1px solid transparent;
                border-radius: 14px;
                padding: 14px 16px;
                min-height: 44px;
                text-align: left;
                font-size: 14px;
                font-weight: 600;
            }
            QPushButton:hover {
                background: %3;
                color: %2;
            }
            QPushButton:pressed {
                background: %4;
                color: %2;
            }
            QPushButton:checked {
                background: %2;
                color: white;
                border: 1px solid %2;
            }
        )").arg(Theme::PRIMARY_LIGHTER).arg(Theme::PRIMARY).arg("#FFD7DA").arg("#FFCDD2");
    btnDashboard->setStyleSheet(buttonStyle);
    btnTodo->setStyleSheet(buttonStyle);
    btnStats->setStyleSheet(buttonStyle);
    btnDashboard->setCheckable(true);
    btnTodo->setCheckable(true);
    btnStats->setCheckable(true);
    btnDashboard->setChecked(true);
    btnDashboard->setCursor(Qt::PointingHandCursor);
    btnTodo->setCursor(Qt::PointingHandCursor);
    btnStats->setCursor(Qt::PointingHandCursor);

    QPushButton *btnSettings = new QPushButton("⚙ 设置");
    btnSettings->setStyleSheet(buttonStyle);
    btnSettings->setCheckable(true);
    btnSettings->setCursor(Qt::PointingHandCursor);

    layout->addWidget(btnDashboard);
    layout->addWidget(btnTodo);
    layout->addWidget(btnStats);
    layout->addWidget(btnSettings);
    layout->addStretch();

    connect(btnDashboard, &QPushButton::clicked, [=](){
        btnDashboard->setChecked(true);
        btnTodo->setChecked(false);
        btnStats->setChecked(false);
        emit pageChanged(0);
    });

    connect(btnTodo, &QPushButton::clicked, [=](){
        btnTodo->setChecked(true);
        btnDashboard->setChecked(false);
        btnStats->setChecked(false);
        emit pageChanged(1);
    });

    connect(btnStats, &QPushButton::clicked, [=](){
        btnStats->setChecked(true);
        btnDashboard->setChecked(false);
        btnTodo->setChecked(false);
        btnSettings->setChecked(false);
        emit pageChanged(2);
    });

    connect(btnSettings, &QPushButton::clicked, [=](){
        btnSettings->setChecked(true);
        btnDashboard->setChecked(false);
        btnTodo->setChecked(false);
        btnStats->setChecked(false);
        emit pageChanged(3);
    });

    connect(this, &SidebarWidget::pageChanged, [=](int page){
        btnDashboard->setChecked(page == 0);
        btnTodo->setChecked(page == 1);
        btnStats->setChecked(page == 2);
        btnSettings->setChecked(page == 3);
    });
}