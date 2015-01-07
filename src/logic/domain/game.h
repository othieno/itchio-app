#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QSet>
#include <QDateTime>
#include "price.h"

namespace itchio {

class QJsonObject;

struct CoverImage
{
    constexpr static const unsigned int WIDTH  = 315;
    constexpr static const unsigned int HEIGHT = 250;

    QString filename;
    QString fileURL;
};


struct Game
{
    /*!
     *
     */
    enum class Status
    {
        Canceled,
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
     *
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

    unsigned int   identifier;
    QString        title;
    QString        author;
    QString        tagline;

#ifdef EXPERIMENTAL
    CoverImage     coverImage;
    QSet<Genre>    genres;
    QSet<Platform> platforms;
    QSet<QString>  tags;
    Status         status;
//    QString        type; //TODO Find out what this is.
    QString        itchURL;
    QString        googlePlayURL;
    QString        appleStoreURL;

    QDateTime      publishDate;
    QDateTime      lastUpdated;

//    QDateTime      lastPlayed;

    Price          minimumPrice;
    bool           purchased;

    bool           downloaded;
    unsigned int   downloadCount; //TODO Make this a 64-bit value.


    // These are author specific.
    QDateTime      creationDate;
    Visibility     visibility;
    Price          earnings;
    unsigned int   viewCount;
    unsigned int   purchaseCount;
#endif
    static Game fromJson(/*const QJsonObject& object*/);
    operator QString() const;
};

} // namespace itchio

std::ostream& operator<<(std::ostream&, const QString&);
std::ostream& operator<<(std::ostream&, const itchio::Game&);

#endif // GAME_H
