#ifndef CONTENT_H
#define CONTENT_H

#include <QString>
#include <QDateTime>
#include <QFlags>
#include <QStringList>

class QJsonObject;
class QSqlRecord;

namespace itchio {

struct Content
{
    /*!
     * An enumeration of available content types.
     * PS. If a new content type is added, make sure the listOfContentTypes function is updated.
     */
    enum class Type
    {
        Game,
        Tool
    };
    static QLinkedList<Type> listOfContentTypes();
    /*!
     * An enumeration of content statuses.
     * PS. If a new status is added, make sure the listOfContentStatuses function is updated.
     */
    enum class Status
    {
        Cancelled,
        OnHold,
        InDevelopment,
        Prototype,
        Released
    };
    static QLinkedList<Status> listOfContentStatuses();
    /*!
     * An enumeration of content permissions (access rights).
     * PS. If a new access right is added, make sure the listOfContentPermissions function is updated.
     */
    enum class Permission
    {
        Private,
        PublicRestricted,
        Public
    };
    static QLinkedList<Permission> listOfContentPermissions();
    /*!
     * An enumeration of supported platforms.
     * PS. If a new platform is added, make sure the listOfContentPlatforms function is updated.
     */
    enum class Platform
    {
        Windows  = 0x01,
        OSX      = 0x02,
        iOS      = 0x04,
        Linux    = 0x08,
        Android  = 0x10,
        Web      = 0x20
    };
    Q_DECLARE_FLAGS(Platforms, Platform)
    static QLinkedList<Platform> listOfContentPlatforms();

    static QString identifierToHex(const int identifier);
    static QString coverImageCacheLocation(const int identifier);

    const Type     type;
    unsigned int   identifier;
    inline QString identifierToHex() const { return identifierToHex(identifier); }
    QString        title;
    QString        author;
    QString        coverImageURL;
    inline QString coverImageCacheLocation() const { return coverImageCacheLocation(identifier); }
    bool           published;
    QDateTime      creationDate;
    QDateTime      publishDate;
    QString        webPageURL;
//    QStringList    tags;

//    Status         status;
//    Access         access;

    unsigned int   downloadCount;
    unsigned int   viewCount;
    unsigned int   purchaseCount;

    Platforms      platforms;

    /*!
     * The default date-time format.
     */
    constexpr static const char* const DATE_TIME_FORMAT = "yyyy-MM-dd hh:mm:ss";
    /*!
     * The number of characters used to represent the identifier's hexadecimal value.
     * For example, all signed 32-bit integers can be represented with a hex value
     * consisting of 8 characters.
     */
    constexpr static unsigned int IDENTIFIER_HEXADECIMAL_LENGTH = sizeof(Content::identifier) << 1;
protected:
    explicit Content(const Type& type);
    Content(const Type& type, const QJsonObject& jsonObject);
    Content(const Type& type, const QSqlRecord& sqlRecord);
};

/*
QString toString(const Content::Type& type);
QString toString(const Content::Status& status);
QString toString(const Content::Access& access);
QString toString(const Content::Platform& platform);
*/
} // namespace itchio

Q_DECLARE_OPERATORS_FOR_FLAGS(itchio::Content::Platforms)

#endif // CONTENT_H
