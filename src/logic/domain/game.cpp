#include "game.h"
#include <sstream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

using itchio::Game;

//TODO Move to header file.
static constexpr const unsigned int MAX_TITLE_LENGTH = 128;
static constexpr const unsigned int MAX_AUTHOR_LENGTH = 128;
static constexpr const unsigned int MAX_DESCRIPTION_LENGTH = 128;
static constexpr const unsigned int MAX_WEBPAGEURL_LENGTH = 128;
static constexpr const unsigned int MAX_GOOGLEPLAYURL_LENGTH = 128;
static constexpr const unsigned int MAX_APPLESTOREURL_LENGTH = 128;
static constexpr const unsigned int MAX_COVERIMAGEURL_LENGTH = 128;
static constexpr const unsigned int MAX_TAG_COUNT = 10;

constexpr const char* const SAMPLE =
"{\
   \"games\":[\
      {\
         \"cover_url\":\"http://img.itch.io/aW1hZ2UvMy8xODM3LnBuZw==/315x250%23/y2uYQI.png\",\
         \"created_at\":\"2013-03-03 23:02:14\",\
         \"downloads_count\":109,\
         \"id\":3,\
         \"min_price\":0,\
         \"p_android\":false,\
         \"p_linux\":true,\
         \"p_osx\":true,\
         \"p_windows\":true,\
         \"published\":true,\
         \"published_at\":\"2013-03-03 23:02:14\",\
         \"purchases_count\":4,\
         \"short_text\":\"Humans have been colonizing planets. It's time to stop them!\",\
         \"title\":\"X-Moon\",\
         \"type\":\"default\",\
         \"url\":\"http://leafo.itch.io/x-moon\",\
         \"views_count\":2682,\
         \"earnings\":[\
            {\
               \"currency\":\"USD\",\
               \"amount_formatted\":\"$50.47\",\
               \"amount\":5047\
            }\
         ]\
      }\
   ]\
}";

#include <QDebug> //TODO Remove me.
Game Game::fromJson(/*const QJsonObject&*/)
{
    constexpr const char* const KEY_ID = "id";
    constexpr const char* const KEY_TITLE = "title";
    constexpr const char* const KEY_AUTHOR = "author";
    constexpr const char* const KEY_TAGLINE = "short_text";
#ifdef EXPERIMENTAL
    constexpr const char* const KEY_HOMEPAGEURL = "url";
    constexpr const char* const KEY_GOOGLEPLAYURL = ""; //FIXME
    constexpr const char* const KEY_APPLESTOREURL = ""; //FIXME
    constexpr const char* const KEY_COVERIMAGEURL = "cover_url";
#endif
    Game game;

    const auto& object = QJsonDocument::fromJson(SAMPLE).object()["games"].toArray()[0].toObject();
//    return Game::fromJson(QJsonObject::fromJson(SAMPLE));

    game.identifier = object[KEY_ID].toInt();
    game.title = object[KEY_TITLE].toString();
    game.author = object[KEY_AUTHOR].toString();
    game.tagline = object[KEY_TAGLINE].toString();

#ifdef EXPERIMENTAL
//    game.coverImageURL = object[KEY_COVERIMAGEURL].toString();


//    QSet<Platform> platforms;
//    QSet<QString>  tags;


    game.homePageURL   = object[KEY_HOMEPAGEURL].toString();
    game.googlePlayURL = object[KEY_GOOGLEPLAYURL].toString();
    game.appleStoreURL = object[KEY_APPLESTOREURL].toString();










//    QSet<Platform> platforms;
//    QSet<QString>  tags;



/*
    {
        "created_at":"2013-03-03 23:02:14",
        "downloads_count":109,
        "earnings":[{"amount":5047,"amount_formatted":"$50.47","currency":"USD"}],
        "min_price":0,
        "p_android":false,
        "p_linux":true,
        "p_osx":true,
        "p_windows":true,
        "published":true,
        "published_at":"2013-03-03 23:02:14",
        "purchases_count":4,
        "type":"default",
        "url":"http://leafo.itch.io/x-moon",
        "views_count":2682
    }
*/
#endif
    return game;
}

Game::operator QString() const
{
    std::stringstream ss;
    ss << *this;

    return QString::fromStdString(ss.str());
}

std::ostream& operator<<(std::ostream& os, const QString& s)
{
    os << s.toStdString();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Game& game)
{
    os
    << "Title: " << game.title << std::endl
    << "Author: " << game.author << std::endl
    << "Identifier: " << game.identifier << std::endl
    << "Tagline: " << game.tagline << std::endl;
#ifdef EXPERIMENTAL
    << "Cover Image: " << game.coverImageURL.filename << std::endl
    << "Home page: " << game.homePageURL << std::endl
    << "Google Play Store: " << game.googlePlayURL << std::endl
    << "Apple App Store: " << game.appleStoreURL << std::endl;
#endif
    return os;
}
