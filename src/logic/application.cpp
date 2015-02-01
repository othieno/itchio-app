#include "application.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>
#include <QFontDatabase>

using itchio::Application;
using itchio::Settings;
using itchio::Window;
using itchio::DatabaseManager;
using itchio::NetworkManager;
using itchio::Authenticator;
using itchio::ContentManager;

/*!
 * \brief Instantiates an Application.
 */
Application::Application(int& argc, char** argv) :
QApplication(argc, argv),
settings_(QString("%1/%2.ini").arg(dataLocation(), applicationName()), QSettings::IniFormat),
window_(*this),
databaseManager_(*this),
networkManager_(*this),
authenticator_(*this),
contentManager_(*this)
{
    connect(this, &Application::aboutToQuit, this, &Application::onAboutToQuit);
    connect(&authenticator_, &Authenticator::authenticated, this, &Application::onUserSessionCreated);

    setApplicationStyle();
    networkManager_.initialize();
}
/*!
 * \brief Returns the application's settings.
 */
Settings& Application::settings()
{
    return settings_;
}
/*!
 * \brief Returns a const-reference to the application's settings.
 */
const Settings& Application::settings() const
{
    return settings_;
}
/*!
 * \brief Displays the application's main window.
 */
void Application::showWindow()
{
    //TODO Load window settings before displaying it.
    window_.showMaximized();
}
/*!
 * \brief Returns the application's database manager.
 */
DatabaseManager& Application::databaseManager()
{
    return databaseManager_;
}
/*!
 * \brief Returns a const-reference to the application's database manager.
 */
const DatabaseManager& Application::databaseManager() const
{
    return databaseManager_;
}
/*!
 * \brief Returns the application's network manager.
 */
NetworkManager& Application::networkManager()
{
    return networkManager_;
}
/*!
 * \brief Returns a const-reference to the application's network manager.
 */
const NetworkManager& Application::networkManager() const
{
    return networkManager_;
}
/*!
 * \brief Returns the application's authentication service.
 */
Authenticator& Application::authenticator()
{
    return authenticator_;
}
/*!
 * \brief Returns a const-reference to the application's authentication service.
 */
const Authenticator& Application::authenticator() const
{
    return authenticator_;
}
/*!
 * \brief Returns the application's content manager.
 */
ContentManager& Application::contentManager()
{
    return contentManager_;
}
/*!
 * \brief Returns a const-reference to the application's content manager.
 */
const ContentManager& Application::contentManager() const
{
    return contentManager_;
}
/*!
 * \brief Returns the path to the directory where the application stores persistent data.
 */
QString Application::dataLocation()
{
    //TODO Replace this statement with the commented block below when done debugging.
    return QString("itch.user");

/*
//TODO This is a temporary fix to support systems that don't have Qt 5.4 yet (e.g. Debian GNU/Linux as of Jan 5, 2015).
//TODO It should be removed when Qt 5.4 is readily available (e.g. via a package manager).
#if QT_VERSION >= 0x050400
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#else
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif
*/
}
/*!
 * \brief Creates the data directories used by the application and returns true if successful, false otherwise.
 * If all directories already exist, then true is returned.
 */
bool Application::createDataDirectories()
{
    const auto& locations =
    {
        dataLocation(),
        DatabaseManager::databaseCacheLocation(),
        ContentManager::fileCacheLocation(),
    };
    for (const auto& location : locations)
    {
        const QDir directory(location);
        if (!directory.exists() && !directory.mkpath("."))
        {
            qWarning() << "[Application] WARN: Could not create the data directory" << location;
            return false;
        }
    }
    return true;
}
/*!
 * \brief Restarts the application.
 */
void Application::restart()
{
    exit(Application::RESTART_ON_EXIT_CODE);
}
/*!
 * \brief Sets the application's style which includes fonts and stylesheets.
 */
void Application::setApplicationStyle()
{
    for (const auto& path :
    {
        ":/font/Lato",
        ":/font/Raleway",
        ":/font/OpenSans",
        ":/font/Montserrat"
    }) QFontDatabase::addApplicationFont(path);

    // Set the default stylesheet if none was already specified in the command line arguments.
    if (styleSheet().isEmpty())
    {
        QFile file(":/qss/default");
        if (file.open(QIODevice::ReadOnly))
        {
            setStyleSheet(QTextStream(&file).readAll());
            file.close();
        }
        else
            qWarning() << "[Application] WARN: Could not load the default stylesheet!";
    }
}
/*!
 * \brief Initializes the content manager with the specified \a user.
 */
void Application::onUserSessionCreated(const User& user)
{
    if (settings_.autoLogin() && (settings_.apiKey() != user.key || settings_.username() != user.username))
    {
        settings_.setApiKey(user.key);
        settings_.setUsername(user.username);
    }

    contentManager_.setUser(user);
}
/*!
 * \brief Performs last-second operations before the application quits.
 */
void Application::onAboutToQuit()
{
    //TODO Implement me.
}
