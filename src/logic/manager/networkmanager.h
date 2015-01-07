#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "abstractmanager.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace itchio {

class NetworkManager Q_DECL_FINAL : public AbstractManager
{
    Q_OBJECT
    friend class Application;
public:
    enum class ApiServerStatus
    {
        Up,
        Down
    };

    void initialize();
    bool offline() const;

    void requestUserAuthentication(const QString& username, const QString& password);
    void requestApiServerStatus();
    void requestApiEncryptionKey();


    constexpr static const char* const API_URL = "https://itch.io/api/1";
private:
    explicit NetworkManager(Application& application);

    static QNetworkRequest createApiRequest(const QString& path);

    constexpr static const char* const USER_AGENT = "itch.io app 0.0";
    constexpr static const char* const CONTENT_TYPE = "application/x-www-form-urlencoded";

    QNetworkAccessManager networkAccessManager_;
    ApiServerStatus apiServerStatus_;

    bool isUserAuthenticationRequestPending_;
private slots:
    void onNetworkAccessibleChanged();
signals:
    void initialized();

    void receivedUserAuthentication(const QNetworkReply::NetworkError& error, const QByteArray& response);

//    void receivedApiServerStatus(const QNetworkReply::NetworkError& error, const NetworkManager::ApiServerStatus& status);
//    void receivedApiEncryptionKey(const QNetworkReply::NetworkError& error, const QByteArray& key);
};

} // namespace itchio

#endif // NETWORKMANAGER_H


#ifdef DEPRECATED
#ifndef NET_H
#define NET_H

#include <QString>

class QNetworkReply;
class QNetworkAccessManager;

namespace itchio {
namespace net {

QNetworkReply* requestUserAuthentication(const QString& username, const QString& password);
QNetworkReply* requestUserProfile(const QString& key);

QNetworkReply* requestGameDownloadKeys(QNetworkAccessManager&, const QString& key, const QString& gameIdentifier);

} // namespace net
} // namespace itchio

#endif // NET_H
#endif
