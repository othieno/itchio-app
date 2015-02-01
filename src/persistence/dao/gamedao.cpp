#include "gamedao.h"
#include "game.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

using itchio::GameDAO;
using itchio::Content;
using itchio::Game;

/*!
 * \brief Instantiates a GameDAO that interacts with the specified \a database.
 */
GameDAO::GameDAO(Database& database) :
AbstractDAO(database)
{}
/*!
 * \brief Creates the database tables used by this DAO.
 */
void GameDAO::createTables()
{
    //TODO Set VARCHAR maximum limits.
    constexpr const char* const CREATE_STATEMENT =
    "CREATE TABLE IF NOT EXISTS games ("
    "identifier      INTEGER PRIMARY KEY,"
    "title           VARCHAR,"
    "author          VARCHAR,"
    "published       BOOLEAN,"
    "creationDate    VARCHAR,"
    "publishDate     VARCHAR,"
    "webPageURL      VARCHAR,"
    "tags            VARCHAR,"
    "status          INTEGER,"
    "access          INTEGER,"
    "downloadCount   INTEGER,"
    "viewCount       INTEGER,"
    "purchaseCount   INTEGER,"
    "platforms       INTEGER,"
    "coverImageURL   VARCHAR,"
    "tagline         VARCHAR,"
    "type            VARCHAR,"
    "genres          INTEGER"
    ")";
    database_.exec(CREATE_STATEMENT);
}
/*!
 * \brief Drops all database tables created by this DAO.
 */
void GameDAO::dropTables()
{
    database_.exec("DROP TABLE games");
}
/*!
 * \brief Populates tables with mock data.
 */
void GameDAO::insertMockRecords()
{
    const std::array<QString, 28 * 2> entries =
    {
        "Metal Gear Solid V: The Phantom Pain","Kojima Productions",
        "Asimov",                  "After Dark Studios",
        "Pelagic",                 "After Dark Studios",
        "Naut",                    "The Klondike Collective",
        "PARTICLE MACE",           "Andy Wallace",
        "Glass Wing",              "From Soy Sauce",
        "Super Galaxy Squadron",   "Nick Clinkscales",
        "Precipice",               "Ryan Trawick",
        "GLASS CANNONS",           "Alpha Six Productions",
        "Sandstorm",               "Daniel Linssen",
        "C64anabalt",              "Paul Koller",
        "LISA: The Painful RPG",   "dingalingboy",
        "PARTICLE MACE",           "Andy Wallace",
        "Glass Wing",              "From Soy Sauce",
        "Super Galaxy Squadron",   "Nick Clinkscales",
        "Precipice",               "Ryan Trawick",
        "GLASS CANNONS",           "Alpha Six Productions",
        "Sandstorm",               "Daniel Linssen",
        "C64anabalt",              "Paul Koller",
        "LISA: The Painful RPG",   "dingalingboy",
        "PARTICLE MACE",           "Andy Wallace",
        "Glass Wing",              "From Soy Sauce",
        "Super Galaxy Squadron",   "Nick Clinkscales",
        "Precipice",               "Ryan Trawick",
        "GLASS CANNONS",           "Alpha Six Productions",
        "Sandstorm",               "Daniel Linssen",
        "C64anabalt",              "Paul Koller",
        "LISA: The Painful RPG",   "dingalingboy",
    };

    Game g;
    for (unsigned i = 0; i < entries.size(); i += 2)
    {
        g.identifier = i + 1000;
        g.title      = entries[i];
        g.author     = entries[i + 1];

        save(g);
    }
}
/*!
 * \brief Saves the \a game to the database.
 */
void GameDAO::save(const Game& game)
{
    constexpr const char* const INSERT_STATEMENT =
    "INSERT INTO games VALUES ("
    ":identifier,"
    ":title,"
    ":author,"
    ":published,"
    ":creationDate,"
    ":publishDate,"
    ":webPageURL,"
    "NULL," //":tags,"
    "NULL," //":status,"
    "NULL," //":access,"
    ":downloadCount,"
    ":viewCount,"
    ":purchaseCount,"
    ":platforms,"
    ":coverImageURL,"
    ":tagline,"
    ":type,"
    ":genres"
    ")";

    QSqlQuery query(database_);
    query.prepare(INSERT_STATEMENT);

    query.bindValue(":identifier", game.identifier);
    query.bindValue(":title", game.title);
    query.bindValue(":author", game.author);
    query.bindValue(":published", game.published);
    query.bindValue(":creationDate", game.creationDate.toString(Content::DATE_TIME_FORMAT));
    query.bindValue(":publishDate", game.publishDate.toString(Content::DATE_TIME_FORMAT));
    query.bindValue(":webPageURL", game.webPageURL);

    query.bindValue(":downloadCount", game.downloadCount);
    query.bindValue(":viewCount", game.viewCount);
    query.bindValue(":purchaseCount", game.purchaseCount);
    query.bindValue(":platforms", int(game.platforms));
    query.bindValue(":coverImageURL", game.coverImageURL);
    query.bindValue(":tagline", game.tagline);
    query.bindValue(":type", game.type);
    query.bindValue(":genres", int(game.genres));

    query.exec();
}
/*!
 * \brief Returns the game with the specified \a identifier in the database.
 */
Game GameDAO::get(const unsigned int& identifier) const
{
    const auto& SELECT_STATEMENT = QString("SELECT * FROM games WHERE identifier = '%1'").arg(identifier);

    auto query = database_.exec(SELECT_STATEMENT);

    return query.next() ? Game(query.record()) : Game();
}
/*!
 * \brief Returns all games in the database.
 */
QList<Game> GameDAO::getAll() const
{
    QList<Game> result;
    auto query = database_.exec("SELECT * FROM games");
    while (query.next())
        result.append(Game(query.record()));

    return result;
}
/*!
 * \brief Removes the game with the specified \a identifier from the database.
 */
void GameDAO::remove(const unsigned int& identifier)
{
    const auto& DELETE_STATEMENT = QString("DELETE FROM games WHERE identifier = '%1'").arg(identifier);

    database_.exec(DELETE_STATEMENT);
}
/*!
 * \brief Returns all games with the specified \a title.
 */
QList<Game> GameDAO::getGamesByTitle(const QString& title, const bool caseInsensitive) const
{
    QString SELECT_STATEMENT = QString("SELECT * FROM games WHERE title = '%1'").arg(title);
    if (caseInsensitive)
    {
        SELECT_STATEMENT.append(" COLLATE NOCASE");
    }

    QList<Game> result;
    auto query = database_.exec(SELECT_STATEMENT);
    while (query.next())
        result.append(Game(query.record()));

    return result;
}
/*!
 * \brief Returns all games with the specified \a author.
 */
QList<Game> GameDAO::getGamesByAuthor(const QString& author, const bool caseInsensitive) const
{
    QString SELECT_STATEMENT = QString("SELECT * FROM games WHERE author = '%1'").arg(author);
    if (caseInsensitive)
    {
        SELECT_STATEMENT.append(" COLLATE NOCASE");
    }

    QList<Game> result;
    auto query = database_.exec(SELECT_STATEMENT);
    while (query.next())
        result.append(Game(query.record()));

    return result;
}
/*!
 * \brief Returns all games with the specified \a genre.
 */
QList<Game> GameDAO::getGamesByGenre(const Game::Genre& genre) const
{
    //TODO Implement me.
    Q_UNUSED(genre);
    return QList<Game>();
/*
    QString SELECT_STATEMENT = QString("SELECT * FROM games");






    QList<Game> result;
    auto query = database_.exec(SELECT_STATEMENT);
    while (query.next())
        result.append(Game(query.record()));

    return result;
*/
}
/*!
 * \brief Returns all games on the specified \a platform.
 */
QList<Game> GameDAO::getGamesByPlatform(const Game::Platform& platform) const
{
    //TODO Implement me.
    Q_UNUSED(platform);
    return QList<Game>();
/*
    QString SELECT_STATEMENT = QString("SELECT * FROM games");






    QList<Game> result;
    auto query = database_.exec(SELECT_STATEMENT);
    while (query.next())
        result.append(Game(query.record()));

    return result;
*/
}
/*!
 * \brief Returns all games with the specified \a status.
 */
QList<Game> GameDAO::getGamesByStatus(const Game::Status& status) const
{
    const auto& SELECT_STATEMENT =
    QString("SELECT * FROM games WHERE status = '%1'").arg(static_cast<int>(status));

    QList<Game> result;
    auto query = database_.exec(SELECT_STATEMENT);
    while (query.next())
        result.append(Game(query.record()));

    return result;
}
/*!
 * \brief Returns all games with the specified \a permission.
 */
QList<Game> GameDAO::getGamesByPermission(const Content::Permission& permission) const
{
    const auto& SELECT_STATEMENT =
    QString("SELECT * FROM games WHERE access = '%1'").arg(static_cast<int>(permission));

    QList<Game> result;
    auto query = database_.exec(SELECT_STATEMENT);
    while (query.next())
        result.append(Game(query.record()));

    return result;
}
