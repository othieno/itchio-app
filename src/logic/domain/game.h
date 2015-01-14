#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QSet>
#include <QDateTime>
#include "price.h"

namespace itchio {

class QJsonObject;

/*
struct PublishStatistics
{
    unsigned int   gameIdentifier;
    Price          earnings;
    unsigned int   viewCount;
    unsigned int   purchaseCount;
    unsigned int   downloadCount;
};
struct BuyInfo
{
    bool           isPurchased;

    Price          minimumPrice;

    QString        itchURL;
    QString        googlePlayURL;
    QString        appleStoreURL;
};
*/

/*!
 * \brief Cover image resolution.
 */
constexpr static int COVER_IMAGE_WIDTH  = 315;
constexpr static int COVER_IMAGE_HEIGHT = 250;


struct Game
{
    /*!
     *
     */
    enum class Status
    {
        Cancelled,
        OnHold,
        InDevelopment,
        Prototype,
        Released
    };
    /*!
     *
     */
    enum class Genre
    {
        Action,
        Platformer,
        Shooter,
        Adventure,
        RolePlaying,
        Simulation,
        Strategy,
        Puzzle,
        Sports,
        Other
    };
    /*!
     *
     */
    enum class Visibility
    {
        Private,
        PublicRestricted,
        Public
    };
    /*!
     * An enumeration of supported platforms.
     */
    enum class Platform
    {
        Windows,
        OSX,
        iOS,
        Linux,
        Android,
        Web
    };

    unsigned int     identifier;
    QString          title;
    QString          author;
    QString          coverImageURL;
    QString          tagline; // a.k.a. shortText.
    QSet<Genre>      genres;
    QSet<Platform>   platforms;
    Status           status;
    QSet<QString>    tags;
    Visibility       visibility;
    QString          type; //TODO Find out exactly what a game 'type' is. Is it a genre?

    QDateTime        publishDate;

    static Game fromJson(/*const QJsonObject& object*/);
    operator QString() const;
};

} // namespace itchio

std::ostream& operator<<(std::ostream&, const QString&);
std::ostream& operator<<(std::ostream&, const itchio::Game&);

#endif // GAME_H
