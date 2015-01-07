#include "networkmanager.h"
#include <QUrlQuery>

using itchio::NetworkManager;

/*!
 * \brief Instantiates an NetworkManager that is attached to a parent \a application.
 */
NetworkManager::NetworkManager(Application& application) :
AbstractManager(application),
apiServerStatus_(ApiServerStatus::Down),
isUserAuthenticationRequestPending_(false)
{
    connect
    (
        &networkAccessManager_, &QNetworkAccessManager::networkAccessibleChanged,
        this,                   &NetworkManager::onNetworkAccessibleChanged
    );
}
/*!
 * \brief Initializes the network manager.
 * The initialized signal is emitted when the network manager is ready.
 */
void NetworkManager::initialize()
{
    const bool accessible = networkAccessManager_.networkAccessible() == QNetworkAccessManager::Accessible;
    if (accessible)
    {
        //TODO Just network initialization things.
    }
    emit initialized();
}
/*!
 * \brief Returns true if the network manager is operating in offline mode, false otherwise.
 * The network manager is considered to be in offline mode if the network is not accessible,
 * or the API server is down.
 */
bool NetworkManager::offline() const
{
    return
    networkAccessManager_.networkAccessible() != QNetworkAccessManager::Accessible ||
    apiServerStatus_ == ApiServerStatus::Down;
}















void NetworkManager::requestUserAuthentication(const QString& username, const QString& password)
{
    if (!isUserAuthenticationRequestPending_ && !offline())
    {
        const auto& request = createApiRequest("/login");

        QUrlQuery query;
        query.setQueryItems({{"username", username}, {"password", password}, {"source", "desktop"}});

        auto* const reply = networkAccessManager_.post(request, query.toString(QUrl::FullyEncoded).toUtf8());
        if (reply != nullptr)
        {
            // Coalesce authentication requests to prevent flooding the server.
            isUserAuthenticationRequestPending_ = true;

            connect(reply, &QNetworkReply::finished, [this, reply]
            {
                const auto& error = reply->error();
                const auto& response =
                error == QNetworkReply::NoError ? reply->readAll() : reply->errorString().toUtf8();

                emit receivedUserAuthentication(error, response);
                reply->deleteLater();

                isUserAuthenticationRequestPending_ = false;
            });
        }
    }
}















/*!
 * \brief Handles the 'QNetworkAccessManager::networkAccessibleChanged' signal.
 */
void NetworkManager::onNetworkAccessibleChanged()
{
    //TODO Complete me.
    const bool offline = networkAccessManager_.networkAccessible() != QNetworkAccessManager::Accessible;
    Q_UNUSED(offline);



    //TODO Start a timer to attempt to reconnect after a specified interval.
}



/*!
 * \brief Returns a correctly formed API request with the given \a path.
 */
QNetworkRequest NetworkManager::createApiRequest(const QString& path)
{
    const QString& simplifiedPath = path.simplified();
    const QString& format = simplifiedPath.at(0) == '/' ? "%1%2" : "%1/%2";

    QNetworkRequest request(QUrl(QString(format).arg(NetworkManager::API_URL, simplifiedPath)));

    request.setHeader(QNetworkRequest::ContentTypeHeader, CONTENT_TYPE);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);

    return request;
}
