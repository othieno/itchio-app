#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include "abstractcontroller.h"
#include "window.h"
#include <QNetworkReply>

namespace itchio {

class NetworkManager;
class User;

class Authenticator Q_DECL_FINAL : public AbstractController
{
    Q_OBJECT
    friend class Application;
public:
    void authenticate(const QString& username, const QString& password);
private:
    explicit Authenticator(Application& application);

    void showUserAuthentication();
    void authenticate(const QString& key);

    NetworkManager& networkManager_;
    Window& window_;
    QString currentUsername_;
public slots:
    void onUserDisconnected();
private slots:
    void onAuthenticated(const User& user);
    void onAuthenticationFailed(const QString& errorMessage);
    void onReceivedUserAuthentication(const QNetworkReply::NetworkError& error, const QByteArray& response);
signals:
    void authenticated(const User& user);
    void authenticationFailed(const QString& errorMessage);
};

} // namespace itchio

#endif // AUTHENTICATOR_H
