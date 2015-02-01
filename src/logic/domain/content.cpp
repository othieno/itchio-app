#include "content.h"
#include "contentmanager.h"
#include <QJsonObject>
#include <QSqlRecord>
#include <QVariant>
#include <QFileInfo>

using itchio::Content;

/*!
 * \brief Instantiates a Content object with the specified \a type.
 */
Content::Content(const Type& t) :
type(t)
{}
/*!
 * \brief Constructs a Content object with the specified \a type from the given JSON \a object.
 */
Content::Content(const Type& t, const QJsonObject& object) :
Content(t)
{
    identifier = object["id"].toInt();
    title = object["title"].toString();
    author = object["author"].toString();
    coverImageURL = object["cover_url"].toString();
    published = object["published"].toBool();
    creationDate = QDateTime::fromString(object["created_at"].toString(), DATE_TIME_FORMAT);
    publishDate = QDateTime::fromString(object["published_at"].toString(), DATE_TIME_FORMAT);
    webPageURL = object["url"].toString();

    //TODO Complete me.
//    tags = 0;
//    status = 0;
//    access = 0;

    downloadCount = object["downloads_count"].toInt();
    viewCount = object["views_count"].toInt();
    purchaseCount = object["purchases_count"].toInt();

    if (object["p_android"].toBool()) platforms |= Platform::Android;
    if (object["p_linux"].toBool())   platforms |= Platform::Linux;
    if (object["p_osx"].toBool())     platforms |= Platform::OSX;
    if (object["p_windows"].toBool()) platforms |= Platform::Windows;
}
/*!
 * \brief Constructs a Content object with the specified \a type from the given SQL \a record.
 */
Content::Content(const Type& t, const QSqlRecord& record) :
Content(t)
{
    identifier = record.value(record.indexOf("identifier")).toUInt();
    title = record.value(record.indexOf("title")).toString();
    author = record.value(record.indexOf("author")).toString();
    coverImageURL = record.value(record.indexOf("coverImageURL")).toString();
    published = record.value(record.indexOf("published")).toBool();
    creationDate = QDateTime::fromString(record.value(record.indexOf("creationDate")).toString(), DATE_TIME_FORMAT);
    publishDate = QDateTime::fromString(record.value(record.indexOf("publishDate")).toString(), DATE_TIME_FORMAT);
    webPageURL = record.value(record.indexOf("webPageURL")).toString();

    //TODO Complete me.
//    tags = 0;
//    status = 0;
//    access = 0;

    downloadCount = record.value(record.indexOf("downloadCount")).toUInt();
    viewCount = record.value(record.indexOf("viewCount")).toUInt();
    purchaseCount = record.value(record.indexOf("purchaseCount")).toUInt();

    platforms = static_cast<Platforms>(record.value(record.indexOf("platforms")).toInt());
}
/*!
 * Returns the \a identifier as a hexadecimal value.
 */
QString Content::identifierToHex(const int identifier)
{
    // When the length of the hexadecimal value is shorter than 'IDENTIFIER_HEXADECIMAL_LENGTH',
    // then it's padded with leading zeros.
    return QString("%1").arg(identifier, IDENTIFIER_HEXADECIMAL_LENGTH, 16, QChar('0')).toUpper();
}
/*!
 * Returns the cover image location in the cache directory for the content with the specified \a identifier.
 */
QString Content::coverImageCacheLocation(const int identifier)
{
    return QString("%1%2").arg(ContentManager::coverImageFilePrefix(), identifierToHex(identifier));
}
