#include "user.h"
#include "contentmanager.h"
#include "databasemanager.h"
#include <QJsonObject>

using itchio::User;

/*!
 * \brief Instantiates a User from the specified JSON \a object.
 */
User::User(const QJsonObject& object)
{
    identifier = unsigned(object["user_id"].toInt());
    key = object["key"].toString();
//    username = object[].toString();
//    avatarImageURL = object[].toString();
//    webPageURL = object[].toString();
    memberSince = QDateTime::fromString(object["created_at"].toString(), Content::DATE_TIME_FORMAT);
    lastUpdated = QDateTime::fromString(object["updated_at"].toString(), Content::DATE_TIME_FORMAT);
}
/*!
 * \brief Returns the user's avatar location in the local file cache.
 */
QString User::avatarImageCacheLocation() const
{
    return QString("%1%2").arg(ContentManager::avatarImageFilePrefix(), Content::identifierToHex(identifier));
}
/*!
 * \brief Returns the user's database file location.
 */
QString User::databaseFileLocation() const
{
    return QString("%1/%2.sqlite").arg(DatabaseManager::databaseCacheLocation(), QString::number(identifier));
}
