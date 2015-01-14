#include "authenticator.h"
#include "application.h"
#include "modalwindow.h"
#include "user.h"
#include "networkmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

using itchio::Authenticator;

Authenticator::Authenticator(Application& application) :
AbstractController(application),
networkManager_(application.networkManager())
{
    connect(&networkManager_, &NetworkManager::receivedUserAuthentication, this, &Authenticator::onReceivedUserAuthentication);
}
/*!
 * \brief Displays the authentication screen.
 */
void Authenticator::showUserAuthentication()
{
    auto& window = application_.window();

    // If the modal window was rejected, then the user explicitly closed the authentication window.
    // The application is exited as a consequence.
    if (window.openModalWindow(View::Identifier::LoginPrompt, Qt::ApplicationModal) == QDialog::Rejected)
        exit(0);











/*
    // A login prompt is created only if we have no API key, or a key that cannot be authenticated.
    const auto& settings = application_.settings();
    if (!settings.hasValidApiKey())
        onUserDisconnected();
    else
    {
        //TODO Complete me.
        const auto& username = settings.username();
        const auto& key = settings.apiKey();
    }
*/
}

void Authenticator::authenticate(const QString& username, const QString& password)
{
    currentUsername_ = username;

    // Upon completion, the NetworkManager emits a 'receivedUserAuthentication'
    // signal which is handled by the 'onReceivedUserAuthentication' slot.
    networkManager_.requestUserAuthentication(username, password);
}


void Authenticator::authenticate(const QString&)
{
    //TODO Implement me.
}



void Authenticator::onReceivedUserAuthentication(const QNetworkReply::NetworkError& error, const QByteArray& response)
{
    if (error != QNetworkReply::NoError)
        emit authenticationFailed(QString(response));
    else
    {
        constexpr const char* const KEY_ERROR      = "errors";
        constexpr const char* const KEY_USER       = "key"; // This is NOT a typo.
        constexpr const char* const KEY_USER_ID    = "user_id";
        constexpr const char* const KEY_API_KEY    = "key";
//        constexpr const char* const KEY_CREATED_AT = "created_at";
//        constexpr const char* const KEY_UPDATED_AT = "updated_at";

        const auto& json = QJsonDocument::fromJson(response).object();

        // If we managed to connect, but a server-side error occured, emit the authenticationFailed
        // signal with the corresponding error message.
        const auto& jsonError = json[KEY_ERROR];
        if (!jsonError.isUndefined())
            emit authenticationFailed(jsonError.toArray()[0].toString());
        else
        {
            // Obtain the user credentials associated with the login request.
            const auto& jsonUser = json[KEY_USER].toObject();

            User user;
            user.identifier = jsonUser[KEY_USER_ID].toInt();
            user.key = jsonUser[KEY_API_KEY].toString();
            user.username = currentUsername_;

            emit authenticated(user);
        }
    }
#ifdef DEPRECATED
    QJsonValue keyValue;

    if(userKey == "")
    {
        keyValue = res.object()["key"];

        if (!keyValue.isNull()) {
            QJsonObject key = keyValue.toObject();
            userKey = key["key"].toString();
            userId = key["user_id"].toInt();
            qDebug() << "\nLogged in with" << userKey << userId;

            onLogin();
            return;
        }
    } else {
        keyValue = res.object()["user"];

        if (!keyValue.isNull()) {
            QJsonObject key = keyValue.toObject();
            userName = key["username"].toString();
            userId = key["id"].toInt();
            qDebug() << "\nLogged in with" << userKey << userId;
            onLogin();
            return;
        }
    }
#endif
}