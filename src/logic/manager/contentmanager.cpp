#include "contentmanager.h"
#include "databasemanager.h"
#include "networkmanager.h"
#include "application.h"
#include "window.h"
#include "gamedao.h"
#include <QDir>
#include <QSqlQuery>

using itchio::ContentManager;
using itchio::GameDAO;
using itchio::User;

/*!
 * \brief Instantiates a ContentManager that is attached to the specified \a application.
 */
ContentManager::ContentManager(Application& application) :
networkManager_(application.networkManager()),
gameDAO_(contentDatabase_)
{
    connect(&networkManager_, &NetworkManager::fileDownloaded, this, &ContentManager::onFileDownloaded);
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
    if (contentDatabase_.open())
        contentDatabase_.close();

    // Create the new user's database.
    contentDatabase_ = DatabaseManager::createDatabase(QString("%1.sqlite").arg(user_.identifier));
    if (!contentDatabase_.open())
    {
        contentDatabase_ = DatabaseManager::createDatabase();
        if (!contentDatabase_.open())
            qFatal("[ContentManager] FATAL: Could not open user database.");
    }

    // Create database tables (if they don't exist).
    gameDAO_.createTables();

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
    if (enable && networkManager_.operationMode() == NetworkManager::OperationMode::Online)
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
QSqlQuery ContentManager::executeDatabaseQuery(const QString& statement)
{
    return contentDatabase_.open() ? contentDatabase_.exec(statement) : QSqlQuery();
}
/*!
 * \brief Returns the Game data access object.
 */
GameDAO& ContentManager::gameDAO()
{
    return gameDAO_;
}
/*!
 * \brief Returns the path to the file cache.
 */
QString ContentManager::fileCacheLocation()
{
    return Application::dataLocation().append("/cache");
}
/*!
 * \brief Returns the prefix added to all cover image files.
 */
QString ContentManager::coverImageFilePrefix()
{
    return fileCacheLocation().append("/COVER_");
}
/*!
 * \brief Updates the current user's stored content.
 */
void ContentManager::updateUserContent()
{
    gameDAO_.insertMockRecords();
/*
    for (const auto& g : gameDAO_.getAll())
    {
        networkManager_.download(g.coverImageURL, g.coverImageCacheLocation());
    }
*/

    //TODO Implement me.

/*
    // If the timer is counting down, then the refresh was requested manually.
    if (autoUpdateTimer_.isActive())
        autoUpdateTimer_.stop();

//    if (autoUpdateTimer_.interval() > 0)
//        autoUpdateTimer_.start();
*/
}
/*!
 * \brief Empties the file cache.
 */
void ContentManager::emptyFileCache()
{
    QDir directory(fileCacheLocation());
    if (directory.exists() && directory.removeRecursively() && directory.mkpath("."))
        emit fileCacheEmptied();
}
/*!
 * \brief Handles the NetworkManager::fileDownloaded signal.
 */
void ContentManager::onFileDownloaded(const QString& fileName)
{
    // If the downloaded file was stored to the file cache, emit the 'fileCacheChanged' signal.
    if (!QString::compare(fileCacheLocation(), fileName.left(fileCacheLocation().length())))
        emit fileCacheChanged(fileName);
}
