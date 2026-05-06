#ifndef EMPTYSTATEWIDGET_H
#define EMPTYSTATEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class EmptyStateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmptyStateWidget(QWidget *parent = nullptr);

    void setContent(const QString &icon, const QString &title, const QString &description, const QString &buttonText = QString());

signals:
    void buttonClicked();

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
    QLabel *m_descLabel;
    QPushButton *m_button;
};

#endif