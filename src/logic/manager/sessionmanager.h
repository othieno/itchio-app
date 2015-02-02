#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QObject>
#include "user.h"

namespace itchio {

class NetworkManager;

class SessionManager : public QObject
{
    Q_OBJECT
    friend class Application;
public:
    const User& user() const;
    const QString& userDatabaseLocation() const;

    void authenticateUser(const QString& username, const QString& password, const bool passwordIsApiKey = false);
public slots:
    void closeUserSession();
private:
    explicit SessionManager(NetworkManager& networkManager);

    NetworkManager& networkManager_;
    User user_;
    QString userDatabaseLocation_;
//TODO    Database userDatabase_;
private slots:
    void openUserSession();
signals:
    void userAuthenticated(const User& user);
    void userAuthenticationFailed(const QString& errorMessage);
    void userSessionOpened(const User& user);
    void userSessionClosed();
};

} // namespace itchio

#endif // SESSIONMANAGER_H
