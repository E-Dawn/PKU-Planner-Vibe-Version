#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QSettings>

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);

private:
    QCheckBox *reminderCheck;
    QComboBox *reminderInterval;
    QPushButton *exportBtn;
    QPushButton *importBtn;

    void loadSettings();
    void saveSettings();
    void exportToCSV();
};

#endif