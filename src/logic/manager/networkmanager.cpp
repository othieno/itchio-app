#include "networkmanager.h"
#include <QUrlQuery>
#include <QFileInfo>

using itchio::NetworkManager;

/*!
 * \brief Instantiates an NetworkManager with the specified user agent \a userAgent.
 */
NetworkManager::NetworkManager(const QString& userAgent) :
userAgent_(userAgent),
apiServerStatus_(ApiServerStatus::Down),
operationMode_(OperationMode::Offline)
{
    connect(this, &NetworkManager::networkAccessibleChanged, this, &NetworkManager::onNetworkAccessibleChanged);
}
/*!
 * \brief Initializes the network manager.
 * The initialized signal is emitted when the network manager is ready.
 */
void NetworkManager::initialize()
{
    const bool accessible = networkAccessible() == QNetworkAccessManager::Accessible;
    if (accessible)
    {
        // TODO Block signals during the initialization phase?
//        setOperationMode(OperationMode::Online);

        //TODO Just network initialization things.
    }
    emit initialized();
}
/*!
 * \brief Returns the API server's status.
 */
const NetworkManager::ApiServerStatus& NetworkManager::apiServerStatus() const
{
    return apiServerStatus_;
}
/*!
 * \brief Returns the network manager's operation mode.
 * The network manager is considered to be in offline mode if the network is not accessible,
 * or the API server is down.
 */
const NetworkManager::OperationMode& NetworkManager::operationMode() const
{
    return operationMode_;
}
/*!
 * \brief Returns a correctly formed API request to the given \a path using the specified API \a key.
 */
QNetworkRequest NetworkManager::getApiRequest(const QString& path, const QString& key) const
{
    //TODO Sanitze the path even more, i.e. remove any leading slashes.
    QString sanitizedPath = path.trimmed();

    const auto& url = QUrl
    (
        key.isEmpty() ?
        QString("%1/%2").arg(NetworkManager::API_URL, sanitizedPath) :
        QString("%1/%2/%3").arg(NetworkManager::API_URL, key, sanitizedPath)
    );

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent_);

    return request;
}
/*!
 * \brief Makes a request to authorize the specified \a username and \a password.
 */
QNetworkReply* NetworkManager::requestUserAuthentication(const QString& username, const QString& password)
{
    // This variable makes sure requests are coalesced to prevent flooding the server.
    static bool isRequestPending = false;

    QNetworkReply* reply = nullptr;

    if (!isRequestPending)
    {
        auto request = getApiRequest("login");

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        QUrlQuery query;
        query.setQueryItems
        ({
            {"username", username},
            {"password", password},
            {"source", "desktop"}
        });

        reply = post(request, query.toString(QUrl::FullyEncoded).toUtf8());
        if (reply != nullptr)
        {
            isRequestPending = true;
            connect(reply, &QNetworkReply::finished, [](){ isRequestPending = false; });
        }
    }
    return reply;
}
/*!
 * \brief Makes a request to acquire the profile of the user with the specified \a key.
 */
QNetworkReply* NetworkManager::requestUserProfile(const QString& key)
{
    return get(getApiRequest("me", key));
}





/*!
 * \brief Makes a request to acquire the set of games owned by the user with the specified \a key.
 */
void NetworkManager::requestUserGames(const QString&)
{
    //TODO Implement me.
}
/*!
 * TODO Document this.
 */
void NetworkManager::requestGamePurchases(const QString&, const unsigned int)
{
    //TODO Implement me.
}
/*!
 * TODO Document this.
 */
void NetworkManager::requestGameDownloadKeys(const QString&, const unsigned int)
{
    //TODO Implement me.
}
/*!
 * TODO Document this.
 */
void NetworkManager::requestApiServerStatus()
{
    //TODO Implement me.
}
/*!
 * TODO Document this.
 */
void NetworkManager::requestApiEncryptionKey()
{
    //TODO Implement me.
}
/*!
 * TODO Document this.
 */
void NetworkManager::setApiServerStatus(const ApiServerStatus&)
{
    //TODO Implement me.
}
/*!
 * TODO Document this.
 */
void NetworkManager::setOperationMode(const OperationMode&)
{
    //TODO Implement me.
}
/*!
 * \brief Downloads the file at the given \a fileURL and stores it with the specified \a fileName.
 */
void NetworkManager::download(const QString& fileURL, const QString& fileName, const bool overwrite)
{
    const QFileInfo fileInfo(fileName);
    if ((!overwrite && fileInfo.exists()) || (overwrite && fileInfo.exists() && !fileInfo.isWritable()) || (networkAccessible() != QNetworkAccessManager::Accessible))
        return;
    else
    {
        QFile* const destination = new QFile(fileName, this);
        if (destination != nullptr && destination->open(QIODevice::WriteOnly))
        {
            auto* reply = get(QNetworkRequest(QUrl(fileURL)));
            if (reply != nullptr)
            {
                connect(reply, &QNetworkReply::readyRead, [reply, destination]()
                {
                    destination->write(reply->readAll());
                });
    /*
                connect(reply, &QNetworkReply::downloadProgress, [reply, destination](qint64 received, qint64 total)
                {
                    Q_UNUSED(received);
                    Q_UNUSED(total);
                    qDebug() << QString("%1 MB").arg(received/1024);
                });
    */
                connect(reply, &QNetworkReply::finished, [this, reply, destination]()
                {
                    destination->close();
                    destination->deleteLater();

                    reply->close();
                    reply->deleteLater();

                    emit fileDownloaded(destination->fileName());
                });
            }
        }
    }
}
/*!
 * \brief Handles the 'QNetworkAccessManager::networkAccessibleChanged' signal.
 */
void NetworkManager::onNetworkAccessibleChanged()
{
    //TODO Complete me.
    const bool accessible = networkAccessible() == QNetworkAccessManager::Accessible;
    Q_UNUSED(accessible);
//    if (!accessible)
//        setOperationMode(OperationMode::Offline);




    //TODO Start a timer to attempt to reconnect after every few milliseconds.
}
