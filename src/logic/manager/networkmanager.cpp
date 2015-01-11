#include "networkmanager.h"
#include <QUrlQuery>

using itchio::NetworkManager;

/*!
 * \brief Instantiates an NetworkManager that is attached to a parent \a application.
 */
NetworkManager::NetworkManager(Application& application) :
Manager(application),
apiServerStatus_(ApiServerStatus::Down),
operationMode_(OperationMode::Offline)
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
 * \brief Makes a request to authorize the specified \a username and \a password.
 */
void NetworkManager::requestUserAuthentication(const QString& username, const QString& password)
{
    // This variable makes sure requests are coalesced to prevent flooding the server.
    static bool IS_REQUEST_PENDING = false;

    if (!IS_REQUEST_PENDING)//TODO && operationMode_ != OperationMode::Offline)
    {
        const auto& request = createApiRequest("/login");

        QUrlQuery query;
        query.setQueryItems({{"username", username}, {"password", password}, {"source", "desktop"}});

        auto* const reply = networkAccessManager_.post(request, query.toString(QUrl::FullyEncoded).toUtf8());
        if (reply != nullptr)
        {
            // Coalesce authentication requests to prevent flooding the server.
            IS_REQUEST_PENDING = true;

            connect(reply, &QNetworkReply::finished, [this, reply]
            {
                const auto& error = reply->error();
                const auto& response =
                error == QNetworkReply::NoError ? reply->readAll() : reply->errorString().toUtf8();

                emit receivedUserAuthentication(error, response);
                reply->deleteLater();

                IS_REQUEST_PENDING = false;
            });
        }
    }
}
/*!
 * \brief Makes a request to acquire the profile of the user with the specified \a key.
 */
void NetworkManager::requestUserProfile(const QString&)
{
    //TODO Implement me.
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
 * \brief Handles the 'QNetworkAccessManager::networkAccessibleChanged' signal.
 */
void NetworkManager::onNetworkAccessibleChanged()
{
    //TODO Complete me.
    const bool accessible = networkAccessManager_.networkAccessible() == QNetworkAccessManager::Accessible;
    Q_UNUSED(accessible);
//    if (!accessible)
//        setOperationMode(OperationMode::Offline);




    //TODO Start a timer to attempt to reconnect after every few milliseconds.
}
/*!
 * \brief Returns a correctly formed API request with the given \a path.
 */
QNetworkRequest NetworkManager::createApiRequest(const QString& path)
{
    constexpr const char* const CONTENT_TYPE = "application/x-www-form-urlencoded";
    constexpr const char* const USER_AGENT = "itch.io app 0.0"; //TODO Move this to the application class? And maybe use the VERSION macro in the .pro file.

    const QString& simplifiedPath = path.simplified();
    const QString& format = simplifiedPath.at(0) == '/' ? "%1%2" : "%1/%2";

    QNetworkRequest request(QUrl(QString(format).arg(NetworkManager::API_URL, simplifiedPath)));

    request.setHeader(QNetworkRequest::ContentTypeHeader, CONTENT_TYPE);
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);

    return request;
}
