#include "onboardingdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

OnboardingDialog::OnboardingDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() | Qt::Dialog);
    setModal(true);
    resize(380, 480);
    setStyleSheet(R"(
        QDialog {
            background: white;
        }
        QPushButton {
            border: none;
            border-radius: 12px;
            padding: 14px 24px;
            font-size: 16px;
            font-weight: 500;
        }
        QPushButton#primaryBtn {
            background: #8B1E2D;
            color: white;
        }
        QPushButton#primaryBtn:hover {
            background: #A02030;
        }
        QPushButton#primaryBtn:pressed {
            background: #701525;
        }
        QPushButton#secondaryBtn {
            background: #F5F5F5;
            color: #666666;
        }
        QPushButton#secondaryBtn:hover {
            background: #EAEAEA;
        }
    )");

    setupUI();
}

void OnboardingDialog::setupUI()
{
    QFrame *card = new QFrame(this);
    card->setStyleSheet(R"(
        QFrame {
            background: white;
            border-radius: 24px;
            border: 1px solid #EAEAEA;
        }
    )");
    card->setGraphicsEffect(nullptr);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(card, 1, Qt::AlignCenter);

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(32, 40, 32, 36);
    cardLayout->setSpacing(20);

    QLabel *logoLabel = new QLabel("🎓");
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setStyleSheet("font-size: 56px;");

    QLabel *titleLabel = new QLabel("欢迎使用 PKU Planner");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(R"(
        font-size: 24px;
        font-weight: 600;
        color: #8B1E2D;
    )");

    QLabel *subtitleLabel = new QLabel("管理课程 · 追踪DDL · 统计效率");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet(R"(
        font-size: 14px;
        color: #999999;
        margin-top: 4px;
    )");

    cardLayout->addWidget(logoLabel);
    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(subtitleLabel);
    cardLayout->addSpacing(16);

    QStringList features = {"课程管理", "任务追踪", "智能分析", "资料整理"};
    QStringList emojis = {"📚", "📝", "📊", "📁"};
    for (int i = 0; i < features.size(); ++i) {
        QFrame *featureItem = new QFrame;
        featureItem->setStyleSheet("background: #FDF9F9; border-radius: 12px; padding: 12px;");
        QHBoxLayout *fl = new QHBoxLayout(featureItem);
        fl->setContentsMargins(16, 12, 16, 12);
        fl->setSpacing(12);

        QLabel *icon = new QLabel(emojis[i]);
        icon->setStyleSheet("font-size: 24px;");

        QLabel *text = new QLabel(features[i]);
        text->setStyleSheet("font-size: 16px; color: #333333;");

        fl->addWidget(icon);
        fl->addWidget(text);
        fl->addStretch();

        cardLayout->addWidget(featureItem);
    }

    cardLayout->addSpacing(16);

    QPushButton *primaryBtn = new QPushButton("创建第一门课程");
    primaryBtn->setObjectName("primaryBtn");
    primaryBtn->setCursor(Qt::PointingHandCursor);
    connect(primaryBtn, &QPushButton::clicked, this, &QDialog::accept);

    QPushButton *secondaryBtn = new QPushButton("稍后体验");
    secondaryBtn->setObjectName("secondaryBtn");
    secondaryBtn->setCursor(Qt::PointingHandCursor);
    connect(secondaryBtn, &QPushButton::clicked, this, &QDialog::reject);

    cardLayout->addWidget(primaryBtn);
    cardLayout->addWidget(secondaryBtn);
}