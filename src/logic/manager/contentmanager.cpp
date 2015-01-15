#include "contentmanager.h"
#include "databasemanager.h"
#include "networkmanager.h"
#include "application.h"
#include "window.h"
#include "gamedao.h"
#include <QDir>

using itchio::ContentManager;
using itchio::GameDAO;
using itchio::User;

/*!
 * \brief Instantiates a ContentManager that is attached to the specified \a application.
 */
ContentManager::ContentManager(Application& application) :
Manager(application)
{
    connect(&autoUpdateTimer_, &QTimer::timeout, this, &ContentManager::updateUserContent);

    autoUpdateTimer_.setInterval(DEFAULT_AUTO_UPDATE_INTERVAL);
    autoUpdateTimer_.setSingleShot(true);
}
/*!
 * \brief Returns the current user.
 */
const User& ContentManager::user() const
{
    return user_;
}
/*!
 * Sets the current \a user.
 */
void ContentManager::setUser(const User& user)
{
    user_ = user;

    // Close the previous user's database.
    if (userDatabase_.open())
        userDatabase_.close();

    // Create the new user's database.
    userDatabase_ = DatabaseManager::createDatabase(QString("%1.sqlite").arg(user_.identifier));
    if (!userDatabase_.open())
    {
        userDatabase_ = DatabaseManager::createInMemoryDatabase();
        if (!userDatabase_.open())
            qFatal("[ContentManager] FATAL: Could not open user database.");
    }

    // Update the user's content.
    updateUserContent();
}
/*!
 * \brief Returns true if content auto-updates are enabled, false otherwise.
 */
bool ContentManager::isAutoUpdateEnabled() const
{
    return autoUpdateTimer_.isActive();
}
/*!
 * \brief Enables content auto-updates if \a enable is set to true, disables it otherwise.
 * If the network manager is in offline mode, then auto-refresh remains disabled.
 */
void ContentManager::enableAutoUpdate(const bool enable)
{
    if (enable && application_.networkManager().operationMode() == NetworkManager::OperationMode::Online)
        autoUpdateTimer_.start();
    else
        autoUpdateTimer_.stop();
}
/*!
 * \brief Returns the auto-update interval in milliseconds.
 */
int ContentManager::autoUpdateInterval() const
{
    return autoUpdateTimer_.interval();
}
/*!
 * \brief Sets the auto-update interval to the specified time in milliseconds.
 */
void ContentManager::setAutoUpdateInterval(const int milliseconds)
{
    autoUpdateTimer_.setInterval(milliseconds >= MINIMUM_AUTO_UPDATE_INTERVAL ? milliseconds : MINIMUM_AUTO_UPDATE_INTERVAL);
}
/*!
 * \brief Returns the Game data access object.
 */
GameDAO& ContentManager::gameDAO()
{
    static GameDAO GAMEDAO_INSTANCE(userDatabase_);
    return GAMEDAO_INSTANCE;
}
/*!
 * \brief Returns the path to the directory where all cache data is stored.
 */
QString ContentManager::cacheLocation()
{
    return Application::dataLocation().append("/cache");
}
/*!
 * \brief Updates the current user's stored content.
 */
void ContentManager::updateUserContent()
{
    //TODO Implement me.




/*
    // If the timer is counting down, then the refresh was requested manually.
    if (autoUpdateTimer_.isActive())
        autoUpdateTimer_.stop();



    qDebug() << "Refreshing..." << user_.username << user_.identifier << user_.key;



//    emit disconnected();

//    if (autoUpdateTimer_.interval() > 0)
//        autoUpdateTimer_.start();
*/





}
/*!
 * \brief Empties the cache directory.
 */
void ContentManager::emptyCache()
{
    QDir directory(cacheLocation());
    if (directory.exists() && directory.removeRecursively() && directory.mkpath("."))
        emit cacheEmptied();
}
