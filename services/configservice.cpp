#include "configservice.h"
#include "../models/datamanager.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

ConfigService& ConfigService::instance()
{
    static ConfigService instance;
    return instance;
}

ConfigService::ConfigService()
    : QObject(nullptr)
    , m_reminderEnabled(true)
    , m_reminderHours(24)
    , m_detailDrawerMode(true)
    , m_onboardingShown(false)
    , m_semesterStart(QDate(2026, 3, 1))
    , m_semesterEnd(QDate(2026, 6, 28))
{
    load();
}

void ConfigService::load()
{
    QString dataPath = DataManager::instance().storageDir();
    QFile file(dataPath + "/config.json");

    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(data, &error);

        if (error.error == QJsonParseError::NoError && doc.isObject()) {
            QJsonObject obj = doc.object();
            m_reminderEnabled = obj.value("reminderEnabled").toBool(true);
            m_reminderHours = obj.value("reminderHours").toInt(24);
            m_detailDrawerMode = obj.value("detailDrawerMode").toBool(true);
            m_exportPath = obj.value("exportPath").toString("");
            m_onboardingShown = obj.value("onboardingShown").toBool(false);

            QString startStr = obj.value("semesterStart").toString();
            QString endStr = obj.value("semesterEnd").toString();
            if (!startStr.isEmpty()) {
                m_semesterStart = QDate::fromString(startStr, "yyyy-MM-dd");
            }
            if (!endStr.isEmpty()) {
                m_semesterEnd = QDate::fromString(endStr, "yyyy-MM-dd");
            }

            qDebug() << "[ConfigService] Loaded config";
        }
    }
}

void ConfigService::save()
{
    QString dataPath = DataManager::instance().storageDir();
    QFile file(dataPath + "/config.json");

    QJsonObject obj;
    obj["reminderEnabled"] = m_reminderEnabled;
    obj["reminderHours"] = m_reminderHours;
    obj["detailDrawerMode"] = m_detailDrawerMode;
    obj["exportPath"] = m_exportPath;
    obj["onboardingShown"] = m_onboardingShown;
    obj["semesterStart"] = m_semesterStart.toString("yyyy-MM-dd");
    obj["semesterEnd"] = m_semesterEnd.toString("yyyy-MM-dd");

    QJsonDocument doc(obj);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "[ConfigService] Saved config";
    }
}

bool ConfigService::isReminderEnabled() const
{
    return m_reminderEnabled;
}

void ConfigService::setReminderEnabled(bool enabled)
{
    m_reminderEnabled = enabled;
    save();
    emit configChanged();
}

int ConfigService::getReminderHours() const
{
    return m_reminderHours;
}

void ConfigService::setReminderHours(int hours)
{
    m_reminderHours = hours;
    save();
    emit configChanged();
}

bool ConfigService::isDetailDrawerMode() const
{
    return m_detailDrawerMode;
}

void ConfigService::setDetailDrawerMode(bool drawerMode)
{
    m_detailDrawerMode = drawerMode;
    save();
    emit configChanged();
}

QString ConfigService::getExportPath() const
{
    if (m_exportPath.isEmpty()) {
        return DataManager::instance().storageDir();
    }
    return m_exportPath;
}

void ConfigService::setExportPath(const QString& path)
{
    m_exportPath = path;
    save();
    emit configChanged();
}

bool ConfigService::isOnboardingShown() const
{
    return m_onboardingShown;
}

void ConfigService::setOnboardingShown(bool shown)
{
    m_onboardingShown = shown;
    save();
    emit configChanged();
}

void ConfigService::resetOnboarding()
{
    setOnboardingShown(false);
}

void ConfigService::resetAllData()
{
    QString dataPath = DataManager::instance().storageDir();

    QFile coursesFile(dataPath + "/courses.json");
    if (coursesFile.exists()) {
        coursesFile.remove();
    }

    QFile tasksFile(dataPath + "/tasks.json");
    if (tasksFile.exists()) {
        tasksFile.remove();
    }

    QFile configFile(dataPath + "/config.json");
    if (configFile.exists()) {
        configFile.remove();
    }

    load();

    qDebug() << "[ConfigService] All data reset";
}

QString ConfigService::getDataPath() const
{
    return DataManager::instance().storageDir();
}

QDate ConfigService::getSemesterStart() const
{
    return m_semesterStart;
}

void ConfigService::setSemesterStart(const QDate& date)
{
    m_semesterStart = date;
    save();
    emit configChanged();
}

QDate ConfigService::getSemesterEnd() const
{
    return m_semesterEnd;
}

void ConfigService::setSemesterEnd(const QDate& date)
{
    m_semesterEnd = date;
    save();
    emit configChanged();
}

int ConfigService::getCurrentWeek() const
{
    if (!m_semesterStart.isValid()) return 1;
    int days = m_semesterStart.daysTo(QDate::currentDate());
    if (days < 0) return 1;
    return days / 7 + 1;
}

bool ConfigService::isSingleWeek() const
{
    return getCurrentWeek() % 2 == 1;
}