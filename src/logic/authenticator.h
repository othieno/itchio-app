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
    void authenticate(const QString& key);
private:
    explicit Authenticator(Application& application);

    void showUserAuthentication();

    NetworkManager& networkManager_;
    QString currentUsername_;
private slots:
    void onReceivedUserAuthentication(const QNetworkReply::NetworkError& error, const QByteArray& response);
signals:
    void authenticated(const User& user);
    void authenticationFailed(const QString& errorMessage);
};

} // namespace itchio

#endif // AUTHENTICATOR_H
