#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "database.h"
#include "gamedao.h"
#include <QTimer>

namespace itchio {

class User;
class Application;
class NetworkManager;
class SessionManager;

class ContentManager final : public QObject
{
    Q_OBJECT
    friend class Application;
public:
    bool isAutoUpdateEnabled() const;
    void enableAutoUpdate(const bool enable = true);

    int autoUpdateInterval() const;
    void setAutoUpdateInterval(const int milliseconds);

    QSqlQuery executeDatabaseQuery(const QString& statement);

    GameDAO& gameDAO();

    static QString fileCacheLocation();
    static QString coverImageFilePrefix();
    static QString avatarImageFilePrefix();

    constexpr static int MINIMUM_AUTO_UPDATE_INTERVAL = 3  * 1000; // 3 seconds.
    constexpr static int DEFAULT_AUTO_UPDATE_INTERVAL = 60 * 1000; // 1 minute
public slots:
    void emptyFileCache();

private:
    ContentManager(NetworkManager& networkManager, SessionManager& sessionManager);

    void downloadUserContent(const User& user);

    QTimer autoUpdateTimer_;

    NetworkManager& networkManager_;
    SessionManager& sessionManager_;

    Database contentDatabase_;
    GameDAO gameDAO_;
private slots:
    void onUserSessionOpened(const User& user);
    void onUserSessionClosed();
    void onFileDownloaded(const QString& fileName);
signals:
    /*!
     * \brief This signal is emitted when the cache is changed, more precisely when the
     * file with the specified \a fileName is modified.
     */
    void fileCacheChanged(const QString& fileName);
    /*!
     * \brief This signal is emitted when the file cache is emptied.
     */
    void fileCacheEmptied();


    void catalogUpdated();
    void libraryUpdated();

};

} // namespace itchio

#endif // CONTENTMANAGER_H
