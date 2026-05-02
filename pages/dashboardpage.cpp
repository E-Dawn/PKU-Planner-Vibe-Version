#include "dashboardpage.h"
#include "../components/coursecellwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QProgressBar>
#include <QPushButton>
#include <QTimer>
#include <QDateTime>

DashboardPage::DashboardPage(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background:#F7F3EF;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(16,16,16,16);
    mainLayout->setSpacing(12);

    // ===== 1. 顶部学期控制栏 =====
    mainLayout->addWidget(createTopBar());

    // ===== 2. 主体区域 =====
    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->setSpacing(12);

    // 左：课程表
    QFrame *courseCard = new QFrame;
    courseCard->setStyleSheet("background:white; border-radius:16px;");
    QVBoxLayout *courseLayout = new QVBoxLayout(courseCard);

    QLabel *courseTitle = new QLabel("课程表");
    courseTitle->setStyleSheet("font-weight:bold; font-size:16px;");
    courseLayout->addWidget(courseTitle);

    QWidget *gridContainer = new QWidget;
    grid = new QGridLayout(gridContainer);
    grid->setSpacing(6);

    courseLayout->addWidget(gridContainer);

    contentLayout->addWidget(courseCard, 7); // 70%

    // 右：侧栏
    contentLayout->addWidget(createRightPanel(), 3); // 30%

    mainLayout->addLayout(contentLayout);

    // ===== 3. 底部统计卡片 =====
    mainLayout->addWidget(createBottomStats());

    initGrid();
    loadCourses();
    renderCourses();
}

QWidget* DashboardPage::createTopBar()
{
    QWidget *bar = new QWidget;
    bar->setStyleSheet("background:white; border-radius:16px; padding:8px;");

    QHBoxLayout *layout = new QHBoxLayout(bar);
    layout->setContentsMargins(8,8,8,8);

    // 学期进度
    semesterProgress = new QProgressBar;
    semesterProgress->setRange(0,18);
    semesterProgress->setValue(currentWeek);
    semesterProgress->setTextVisible(false);

    semesterProgress->setStyleSheet(R"(
        QProgressBar {
            border:none;
            background:#F5F5F5;
            height:16px;
            border-radius:8px;
        }

        QProgressBar::chunk {
            background:#8B1E2D;
            border-radius:8px;
        }
    )");

    weekLabel = new QLabel;
    weekLabel->setStyleSheet("font-weight:bold; font-size:14px;");

    QPushButton *prevBtn = new QPushButton("上周");
    QPushButton *nextBtn = new QPushButton("下周");
    QPushButton *todayBtn = new QPushButton("返回本周");

    layout->addWidget(new QLabel("学期进度"), 0);
    layout->addWidget(semesterProgress, 2);
    layout->addWidget(weekLabel, 0);
    layout->addWidget(prevBtn, 0);
    layout->addWidget(nextBtn, 0);
    layout->addWidget(todayBtn, 0);

    connect(prevBtn,&QPushButton::clicked,this,[=](){
        currentWeek--;
        updateWeekInfo();
    });

    connect(nextBtn,&QPushButton::clicked,this,[=](){
        currentWeek++;
        updateWeekInfo();
    });

    connect(todayBtn,&QPushButton::clicked,this,[=](){
        currentWeek = realWeek;
        updateWeekInfo();
    });

    updateWeekInfo();

    return bar;
}

void DashboardPage::updateWeekInfo()
{
    if(currentWeek < 1) currentWeek = 1;
    if(currentWeek > 18) currentWeek = 18;

    semesterProgress->setValue(currentWeek);

    QString type = (currentWeek % 2 == 1) ? "单周" : "双周";

    weekLabel->setText(
        QString("第 %1 周 (%2)")
            .arg(currentWeek)
            .arg(type)
    );
}

QWidget* DashboardPage::createBottomStats()
{
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(0,0,0,0);

    QStringList titles = {
        "今日课程",
        "今日DDL",
        "本周DDL",
        "当前时间"
    };

    for(auto t : titles)
    {
        QFrame *card = new QFrame;
        card->setStyleSheet(
            "background:white;border-radius:12px;padding:8px;"
        );

        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(8,8,8,8);

        QLabel *num = new QLabel("0");
        num->setStyleSheet(
            "font-size:18px;font-weight:bold;color:#8B1E2D;"
        );

        QLabel *title = new QLabel(t);
        title->setStyleSheet("color:#666;font-size:12px;");

        cl->addWidget(num);
        cl->addWidget(title);

        if(t == "当前时间")
        {
            timeLabel = num;
            timeLabel->setStyleSheet("font-size:14px;font-weight:bold;color:#8B1E2D;");

            QTimer *timer = new QTimer(this);
            connect(timer,&QTimer::timeout,this,[=](){
                timeLabel->setText(
                    QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
                );
            });
            timer->start(1000);
            timeLabel->setText(
                QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
            );
        }

        layout->addWidget(card);
    }

    return widget;
}

QWidget* DashboardPage::createRightPanel()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(12);

    // 今日课程卡
    QFrame *todayCard = new QFrame;
    todayCard->setStyleSheet("background:white; border-radius:16px;");
    QVBoxLayout *todayLayout = new QVBoxLayout(todayCard);
    
    QLabel *todayTitle = new QLabel("今日课程");
    todayTitle->setStyleSheet("font-weight:bold;");
    todayLayout->addWidget(todayTitle);
    
    QLabel *todayContent = new QLabel("暂无课程");
    todayContent->setStyleSheet("color:#999;");
    todayLayout->addWidget(todayContent);

    // DDL摘要卡
    QFrame *ddlCard = new QFrame;
    ddlCard->setStyleSheet("background:white; border-radius:16px;");
    QVBoxLayout *ddlLayout = new QVBoxLayout(ddlCard);
    
    QLabel *ddlTitle = new QLabel("DDL提醒");
    ddlTitle->setStyleSheet("font-weight:bold;");
    ddlLayout->addWidget(ddlTitle);
    
    QLabel *ddlContent = new QLabel("暂无DDL");
    ddlContent->setStyleSheet("color:#999;");
    ddlLayout->addWidget(ddlContent);

    layout->addWidget(todayCard);
    layout->addWidget(ddlCard);
    layout->addStretch();

    return widget;
}

void DashboardPage::initGrid()
{
    QStringList days = {"一","二","三","四","五","六","日"};

    // 星期
    for(int col=0; col<7; col++)
    {
        QLabel *label = new QLabel("周" + days[col]);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-weight:bold; color:#666;");
        grid->addWidget(label, 0, col+1);
    }

// 时间（节数 + 时间段）
QStringList timeSlots = {
    "8:00-8:50",    // 第1节
    "9:00-9:50",    // 第2节
    "10:10-11:00",  // 第3节
    "11:10-12:00",  // 第4节
    "13:00-13:50",  // 第5节
    "14:00-14:50",  // 第6节
    "15:10-16:00",  // 第7节
    "16:10-17:00",  // 第8节
    "17:10-18:00",  // 第9节
    "18:40-19:30",  // 第10节
    "19:40-20:30",  // 第11节
    "20:40-21:30"   // 第12节
};

for(int row=0; row<12; row++)
{
    QLabel *timeLabel = new QLabel(QString("%1\n%2").arg(row+1).arg(timeSlots[row]));
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setStyleSheet("color:#aaa; font-size:10px; line-height:1.2;");
    grid->addWidget(timeLabel, row+1, 0);
}

    // Initialize all cells as empty first to provide a clickable background
    for(int row=0; row<12; row++)
    {
        for(int col=0; col<7; col++)
        {
            CourseCellWidget *cell = new CourseCellWidget(row+1, col+1);
            grid->addWidget(cell, row+1, col+1);
            connect(cell, &CourseCellWidget::createCourseRequested, this, &DashboardPage::createCourse);
        }
    }
}

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include "../dialogs/courseeditdialog.h"
#include <QMessageBox>

void DashboardPage::saveCourses()
{
    QJsonArray arr;

    for(auto &c : courses)
    {
        arr.append(c.toJson());
    }

    QJsonDocument doc(arr);

    QFile file("courses.json");
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
    }
}

void DashboardPage::loadCourses()
{
    QFile file("courses.json");

    if(!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc =
        QJsonDocument::fromJson(file.readAll());

    QJsonArray arr = doc.array();

    courses.clear();
    for(auto item : arr)
    {
        courses.push_back(
            Course::fromJson(item.toObject())
        );
    }
}

void DashboardPage::renderCourses()
{
    QLayoutItem *child;
    while ((child = grid->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    initGrid();

    int index = 0;
    for(auto &c : courses)
    {
        CourseCellWidget *cell = new CourseCellWidget(c.startPeriod, c.day);
        cell->setCourse(c.name, c.location, c.teacher, index);
        
        connect(cell, &CourseCellWidget::editCourseRequested,
                this, &DashboardPage::editCourse);

        grid->addWidget(
            cell,
            c.startPeriod,
            c.day,
            c.endPeriod - c.startPeriod + 1,
            1
        );
        index++;
    }
}

void DashboardPage::createCourse(int row, int col)
{
    CourseEditDialog dialog(row, row);
    dialog.setWindowTitle("添加课程");
    
    if (dialog.exec() == QDialog::Accepted) {
        Course c;
        c.name = dialog.getName();
        c.teacher = dialog.getTeacher();
        c.location = dialog.getLocation();
        c.examTime = dialog.getExamTime();
        
        c.startPeriod = dialog.getStart();
        c.endPeriod = dialog.getEnd();
        c.day = col;
        
        courses.push_back(c);
        
        saveCourses();
        renderCourses();
    }
}

void DashboardPage::editCourse(int index)
{
    if (index < 0 || index >= courses.size()) return;
    
    Course &c = courses[index];
    
    QMessageBox msgBox;
    msgBox.setWindowTitle("操作");
    msgBox.setText("请选择操作");
    
    QPushButton *editBtn = msgBox.addButton("编辑", QMessageBox::ActionRole);
    QPushButton *deleteBtn = msgBox.addButton("删除", QMessageBox::ActionRole);
    QPushButton *cancelBtn = msgBox.addButton("取消", QMessageBox::RejectRole);
    
    msgBox.exec();
    
    if (msgBox.clickedButton() == editBtn) {
        CourseEditDialog dialog(c.startPeriod, c.endPeriod);
        dialog.setWindowTitle("编辑课程");
        dialog.setCourseData(c.name, c.teacher, c.location, c.examTime, c.startPeriod, c.endPeriod);
        
        if (dialog.exec() == QDialog::Accepted) {
            c.name = dialog.getName();
            c.teacher = dialog.getTeacher();
            c.location = dialog.getLocation();
            c.examTime = dialog.getExamTime();
            c.startPeriod = dialog.getStart();
            c.endPeriod = dialog.getEnd();
            // c.day remains unchanged from edit interface (unless col added to dialog)
            
            saveCourses();
            renderCourses();
        }
    } else if (msgBox.clickedButton() == deleteBtn) {
        courses.erase(courses.begin() + index);
        saveCourses();
        renderCourses();
    }
}