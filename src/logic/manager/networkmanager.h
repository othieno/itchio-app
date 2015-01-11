#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "manager.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace itchio {

class NetworkManager Q_DECL_FINAL : public Manager
{
    Q_OBJECT
    friend class Application;
public:
    enum class ApiServerStatus
    {
        Up,
        Down
    };
    enum class OperationMode
    {
        Online,
        Offline
    };

    void initialize();

    const ApiServerStatus& apiServerStatus() const;
    const OperationMode& operationMode() const;

    void requestUserAuthentication(const QString& username, const QString& password);
    void requestUserProfile(const QString& key);
    void requestUserGames(const QString& key);

    void requestGamePurchases(const QString& key, const unsigned int gameIdentifier);
    void requestGameDownloadKeys(const QString& key, const unsigned int gameIdentifier);

    void requestApiServerStatus();
    void requestApiEncryptionKey();

    constexpr static const char* const API_URL = "https://itch.io/api/1";
private:
    explicit NetworkManager(Application& application);

    void setApiServerStatus(const ApiServerStatus& status);
    void setOperationMode(const OperationMode& mode);

    static QNetworkRequest createApiRequest(const QString& path);

    QNetworkAccessManager networkAccessManager_;
    ApiServerStatus apiServerStatus_;
    OperationMode operationMode_;
private slots:
    void onNetworkAccessibleChanged();
signals:
    void initialized();

    void apiServerStatusChanged(const ApiServerStatus& status);
    void operationModeChanged(const OperationMode& mode);

    void receivedUserAuthentication(const QNetworkReply::NetworkError& error, const QByteArray& response);
    void receivedUserProfile(const QNetworkReply::NetworkError& error, const QByteArray& response);
    void receivedUserGames(const QNetworkReply::NetworkError& error, const QByteArray& response);

    void receivedGamePurchases(const QNetworkReply::NetworkError& error, const QByteArray& response);
    void receivedGameDownloadKeys(const QNetworkReply::NetworkError& error, const QByteArray& response);

    void receivedApiServerStatus(const QNetworkReply::NetworkError& error, const QByteArray& response);
    void receivedApiEncryptionKey(const QNetworkReply::NetworkError& error, const QByteArray& response);
};

} // namespace itchio

#endif // NETWORKMANAGER_H
