#include "application.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>

using itchio::Application;
using itchio::Settings;
using itchio::Window;
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
networkManager_(*this),
authenticator_(*this),
contentManager_(*this)
{
    connect(&networkManager_, &NetworkManager::initialized, this, &Application::onNetworkManagerInitialized);
    connect(&authenticator_, &Authenticator::authenticated, this, &Application::onUserAuthenticated);
//TODO    connect(&contentManager_, &ContentManager::userSessionClosed, this, &Application::onUserSessionClosed);

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
 * \brief Returns the application's main window.
 */
Window& Application::window()
{
    return window_;
}
/*!
 * \brief Returns a const-reference to the application's main window.
 */
const Window& Application::window() const
{
    return window_;
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
    //TODO Replace this statement with the commented block below.
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
 * \brief Creates a data location directory and returns true if successful, false otherwise.
 * If the directory already exists, then true is returned.
 */
bool Application::createDataLocation()
{
    const QDir directory(dataLocation());
    return directory.exists() || directory.mkpath(".");
}
/*!
 * \brief Restarts the application.
 */
void Application::restart()
{
    exit(Application::RESTART_ON_EXIT_CODE);
}
/*!
 * \brief Sets the application's style which includes stylesheets and fonts.
 */
void Application::setApplicationStyle()
{
    QFile file(":/qss/itchio.qss");
    if (file.open(QIODevice::ReadOnly))
    {
        setStyleSheet(QTextStream(&file).readAll());
        file.close();
    }
    else
        qWarning("[%s] Could not load default stylesheet!", qPrintable(applicationName()));
}
/*!
 * \brief Initializes the authenticator when the network manager is ready.
 */
void Application::onNetworkManagerInitialized()
{
    authenticator_.showUserAuthentication();
}
/*!
 * \brief Initializes the content manager with the specified \a user.
 */
void Application::onUserAuthenticated(const User& user)
{
    if (settings_.autoLogin())
    {
        settings_.setApiKey(user.key);
        settings_.setUsername(user.username);
    }

    contentManager_.showUserContent(user);
}
/*!
 * \brief Shows the authentication screen when a user logs out of their session.
 */
void Application::onUserSessionClosed()
{
    authenticator_.showUserAuthentication();
}
