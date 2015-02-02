#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

class QJsonObject;

namespace itchio {

/**
 * A user profile.
 */
struct User
{
    User() = default;
    explicit User(const QJsonObject& jsonObject);

    unsigned int identifier;
    QString name;
    QString displayName;
    QString key;
    QString avatarImageURL;
    QString avatarImageCacheLocation() const;
    QString webPageURL;

    QDateTime memberSince;
    QDateTime lastUpdated;

    QString databaseFileLocation() const;
};

} // namespace itchio

#endif // USER_H
