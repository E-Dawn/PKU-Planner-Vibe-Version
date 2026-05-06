#include "emptystatewidget.h"
#include "../ui/theme.h"

EmptyStateWidget::EmptyStateWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background:transparent;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(16);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet("font-size:48px;");
    layout->addWidget(m_iconLabel);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet(QString("color:%1;font-size:16px;font-weight:600;").arg(Theme::TEXT_PRIMARY));
    layout->addWidget(m_titleLabel);

    m_descLabel = new QLabel(this);
    m_descLabel->setAlignment(Qt::AlignCenter);
    m_descLabel->setStyleSheet(QString("color:%1;font-size:13px;").arg(Theme::TEXT_TERTIARY));
    m_descLabel->setWordWrap(true);
    layout->addWidget(m_descLabel);

    m_button = new QPushButton(this);
    m_button->setStyleSheet(Theme::primaryButtonStyle());
    m_button->hide();
    layout->addWidget(m_button);
    layout->setContentsMargins(0, 0, 0, 0);

    connect(m_button, &QPushButton::clicked, this, &EmptyStateWidget::buttonClicked);
}

void EmptyStateWidget::setContent(const QString &icon, const QString &title, const QString &description, const QString &buttonText)
{
    m_iconLabel->setText(icon);
    m_titleLabel->setText(title);
    m_descLabel->setText(description);

    if (buttonText.isEmpty()) {
        m_button->hide();
    } else {
        m_button->setText(buttonText);
        m_button->show();
    }
}