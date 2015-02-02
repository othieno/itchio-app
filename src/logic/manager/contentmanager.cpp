#include "contentmanager.h"
#include "databasemanager.h"
#include "networkmanager.h"
#include "sessionmanager.h"
#include "application.h"
#include "window.h"
#include "gamedao.h"
#include <QDir>
#include <QSqlQuery>

using itchio::ContentManager;
using itchio::GameDAO;
using itchio::User;

/*!
 * \brief Instantiates a ContentManager with references to a \a networkManager and \a sessionManager.
 */
ContentManager::ContentManager(NetworkManager& networkManager, SessionManager& sessionManager) :
networkManager_(networkManager),
sessionManager_(sessionManager),
gameDAO_(contentDatabase_)
{
    connect(&sessionManager_, &SessionManager::userSessionOpened, this, &ContentManager::onUserSessionOpened);
    connect(&sessionManager_, &SessionManager::userSessionClosed, this, &ContentManager::onUserSessionClosed);
    connect(&networkManager_, &NetworkManager::fileDownloaded, this, &ContentManager::onFileDownloaded);
//FIXME    connect(&autoUpdateTimer_, &QTimer::timeout, this, &ContentManager::updateUserContent);

    autoUpdateTimer_.setInterval(DEFAULT_AUTO_UPDATE_INTERVAL);
    autoUpdateTimer_.setSingleShot(true);
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
 * \brief Returns the prefix added to all avatar image files.
 */
QString ContentManager::avatarImageFilePrefix()
{
    return fileCacheLocation().append("/AVATAR_");
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
 * \brief Downloads content specific to the \a user.
 */
void ContentManager::downloadUserContent(const User&)
{
    //TODO Download iff user.lastUpdated is more recent than image.lastUpdated.
//    if (!user.avatarImageURL.isEmpty())
//        networkManager_.download(user.avatarImageURL, user.avatarImageCacheLocation());


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
 * \brief Handles the 'userSessionOpened' signal emitted by the session manager.
 * More specifically, this will download the user's information and store it to their local database.
 */
void ContentManager::onUserSessionOpened(const User& user)
{
    // Close the previous user's database.
    if (contentDatabase_.open())
        contentDatabase_.close();

    // Create the new user's database.
    contentDatabase_ = DatabaseManager::createDatabase(sessionManager_.userDatabaseLocation());
    if (!contentDatabase_.open())
        qFatal("[ContentManager] FATAL: Could not open user database.");

    // Create database tables (if they don't exist) then download user content.
    gameDAO_.createTables();
    downloadUserContent(user);
}
/*!
 * \brief Handles the 'userSessionClosed' signal emitted by the session manager.
 */
void ContentManager::onUserSessionClosed()
{
    contentDatabase_.close();
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
