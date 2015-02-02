#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace itchio {

class Application;

class NetworkManager final : public QNetworkAccessManager
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

    QNetworkReply* requestUserAuthentication(const QString& username, const QString& password);
    QNetworkReply* requestUserProfile(const QString& key);


    void requestUserGames(const QString& key);

    void requestGamePurchases(const QString& key, const unsigned int gameIdentifier);
    void requestGameDownloadKeys(const QString& key, const unsigned int gameIdentifier);

    void requestApiServerStatus();
    void requestApiEncryptionKey();

    void download(const QString& fileURL, const QString& fileName, const bool overwrite = false);

    static constexpr const char* API_URL = "https://itch.io/api/1";
private:
    explicit NetworkManager(const QString& userAgent);

    QNetworkRequest getApiRequest(const QString& path, const QString& key = QString()) const;

    void setApiServerStatus(const ApiServerStatus& status);
    void setOperationMode(const OperationMode& mode);

    const QString userAgent_;
    ApiServerStatus apiServerStatus_;
    OperationMode operationMode_;
private slots:
    void onNetworkAccessibleChanged();
signals:
    void initialized();

    void apiServerStatusChanged(const ApiServerStatus& status);
    void operationModeChanged(const OperationMode& mode);

    void receivedUserGames(const QNetworkReply::NetworkError& error, const QByteArray& response);

    void receivedGamePurchases(const QNetworkReply::NetworkError& error, const QByteArray& response);
    void receivedGameDownloadKeys(const QNetworkReply::NetworkError& error, const QByteArray& response);

    void receivedApiServerStatus(const QNetworkReply::NetworkError& error, const QByteArray& response);
    void receivedApiEncryptionKey(const QNetworkReply::NetworkError& error, const QByteArray& response);

    void fileDownloaded(const QString& fileName);
};

} // namespace itchio

#endif // NETWORKMANAGER_H
