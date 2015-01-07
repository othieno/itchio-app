#include "settings.h"
#include "networkmanager.h"

using itchio::Settings;

Settings::Settings(const QString& filename, const Format format, QObject* const parent) :
    QSettings(filename, format, parent)
{}

QString Settings::apiKey() const
{
    return value(Key::API_KEY).toString();
}

void Settings::setApiKey(const QString& key)
{
    setValue(Key::API_KEY, key);
}

bool Settings::hasValidApiKey() const
{
    //TODO Perform a more thorough check.
    return apiKey() != "";
}

QString Settings::apiUrl() const
{
    return value(Key::API_URL, NetworkManager::API_URL).toString();
}

void Settings::setApiUrl(const QString& url)
{
    setValue(Key::API_URL, url);
}

QString Settings::username() const
{
    return value(Key::USERNAME).toString();
}

void Settings::setUsername(const QString& username)
{
    setValue(Key::USERNAME, username);
}

bool Settings::autoLogin() const
{
    return value(Key::AUTO_LOGIN, Settings::DEFAULT_AUTO_LOGIN).toBool();
}

void Settings::enableAutoLogin(const bool enable)
{
    setValue(Key::AUTO_LOGIN, enable);
}

bool Settings::autoUpdateChecks() const
{
    return value(Key::AUTO_UPDATE_CHECKS, Settings::DEFAULT_AUTO_UPDATE_CHECKS).toBool();
}

void Settings::enableAutoUpdateChecks(const bool enable)
{
    setValue(Key::AUTO_UPDATE_CHECKS, enable);
}

bool Settings::showTrayNotifications() const
{
    return value(Key::SHOW_TRAY_NOTIFICATIONS, Settings::DEFAULT_SHOW_TRAY_NOTIFICATIONS).toBool();
}

void Settings::enableTrayNotifications(const bool enable)
{
    setValue(Key::SHOW_TRAY_NOTIFICATIONS, enable);
}

QString Settings::toString(const Key& key)
{
    switch (key) {
    case Key::API_KEY:
        return "api_key";
    case Key::API_URL:
        return "api_url";
    case Key::USERNAME:
        return "username";
    case Key::AUTO_LOGIN:
        return "auto_login";
    case Key::AUTO_UPDATE_CHECKS:
        return "auto_update_checks";
    case Key::SHOW_TRAY_NOTIFICATIONS:
        return "show_tray_notifications";
    default:
        // This is a guard to make sure any keys added later on are handled in this switch-case.
        qFatal("[Settings::toString] Undefined key!");
    }
}
