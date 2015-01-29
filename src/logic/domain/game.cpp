#include "game.h"
#include <sstream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlRecord>
#include <QVariant>

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

//TODO Move to NetworkManager::receivedGames.
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



/*!
 * \brief Instantiates a Game object.
 */
Game::Game() :
//Content(Type::Game),
Game(QJsonDocument::fromJson(SAMPLE).object()["games"].toArray()[0].toObject())
{}
/*!
 * \brief Constructs a Game object from the specified JSON \a object.
 */
Game::Game(const QJsonObject& object) :
Content(Type::Game, object)
{
    coverImageURL = object["cover_url"].toString();
    tagline = object["short_text"].toString();
    type = object["type"].toString();
#ifdef TODO
    genres = 0;
    minimumPrice = Price::fromJson(object["min_price"].toObject());
    earnings = Price::fromJson(object["type"].toObject());
    googlePlayURL = object["google_play_url"].toString();
    appleStoreURL = object["apple_store_url"].toString();
#endif
}
/*!
 * \brief Constructs a Game object from the specified SQL \a record.
 */
Game::Game(const QSqlRecord& record) :
Content(Type::Game, record)
{
    coverImageURL = record.value(record.indexOf("coverImageURL")).toString();
    tagline = record.value(record.indexOf("tagline")).toString();
    type = record.value(record.indexOf("type")).toString();
    genres = static_cast<Genres>(record.value(record.indexOf("genres")).toInt());
}
/*!
 * Returns a list containing all genres.
 */
QLinkedList<Game::Genre> Game::listOfGameGenres()
{
    return QLinkedList<Game::Genre>()
    << Genre::Action
    << Genre::Platformer
    << Genre::Shooter
    << Genre::Adventure
    << Genre::RolePlaying
    << Genre::Simulation
    << Genre::Strategy
    << Genre::Puzzle
    << Genre::Sports
    << Genre::Other;
}
