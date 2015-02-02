#include "sessionmanager.h"
#include "networkmanager.h"
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

using itchio::SessionManager;
using itchio::User;

/*!
 * \brief Instantiates a SessionManager that is attached to the specified \a networkManager.
 */
SessionManager::SessionManager(NetworkManager& networkManager) :
networkManager_(networkManager)
{
    connect(this, &SessionManager::userAuthenticated, this, &SessionManager::openUserSession);
}
/*!
 * \brief Returns the current user, authenticated or not.
 */
const User& SessionManager::user() const
{
    return user_;
}
/*!
 * \brief Returns the location of the database used by the current user.
 */
const QString& SessionManager::userDatabaseLocation() const
{
    return userDatabaseLocation_;
}
/*!
 * \brief Authenticates a \a username and \a password pair.
 * If \a passwordIsApiKey is set to true, then \a password is assumed to be the user's API key.
 */
void SessionManager::authenticateUser(const QString& username, const QString& password, const bool passwordIsApiKey)
{
    //TODO Remove this block when done debugging.
    {
        user_.identifier = 0;
        user_.name = "root";
        user_.key = "TheQuickBrownFoxJumpsOverTheLazyDog";
        emit userAuthenticated(user_);
        return;
    }

    auto* const reply = passwordIsApiKey ?
    networkManager_.requestUserProfile(password) : networkManager_.requestUserAuthentication(username, password);

    if (reply != nullptr)
    {
        connect(reply, &QNetworkReply::finished, [this, reply, username, password, passwordIsApiKey]()
        {
            const auto& error = reply->error();
            if (error != QNetworkReply::NoError)
                emit userAuthenticationFailed(reply->errorString());
            else
            {
                const auto& json = QJsonDocument::fromJson(reply->readAll()).object();
                const auto& jsonError = json["errors"];
                if (!jsonError.isUndefined())
                    emit userAuthenticationFailed(jsonError.toArray()[0].toString());
                else
                {
                    //TODO Check for null JSON objects.
                    //FIXME The fact that there're two different JSON responses causes discrepancies when it comes to creating a User object.
                    if (!passwordIsApiKey)
                    {
                        user_ = User(json["key"].toObject()); //Note: "key" is not a typo.
                        user_.name = username;

                        emit userAuthenticated(user_);
                    }
                    else
                    {
                        //FIXME The user cannot be fully constructed from this JSON response. This is an API issue.
                        const auto& object = json["user"].toObject();
                        if (object["username"].toString() == username)
                        {
                            user_.name = object["username"].toString();
                            user_.identifier = object["id"].toInt();
                            user_.key = password;

                            emit userAuthenticated(user_);
                        }
                        else
                            emit userAuthenticationFailed("Mismatching API key.");
                    }
                }
            }
            reply->close();
            reply->deleteLater();
        });
    }
    else
        emit userAuthenticationFailed(tr("Could not instantiate authentication request."));
}
/*!
 * \brief Opens a user session.
 */
void SessionManager::openUserSession()
{
    const QFileInfo fileInfo(user_.databaseFileLocation());

    const bool useEphemeralDatabase =
    ( fileInfo.exists() && (!fileInfo.isFile() || !fileInfo.isWritable())) ||
    (!fileInfo.exists() &&  !QFile(fileInfo.filePath()).open(QIODevice::ReadWrite));

    userDatabaseLocation_ = useEphemeralDatabase ? ":memory:" : fileInfo.filePath();

    emit userSessionOpened(user_);
}
/*!
 * \brief Closes the currently opened user session.
 */
void SessionManager::closeUserSession()
{
    // Reset the user's properties.
    user_ = User();
}
