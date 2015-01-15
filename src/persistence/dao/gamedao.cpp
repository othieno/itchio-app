#include "gamedao.h"
#include "game.h"
#include "database.h"
#include <QSqlQuery>
#include <QVariant>

using itchio::GameDAO;
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
    constexpr const char* const CREATE_STATEMENT =
    "CREATE TABLE IF NOT EXISTS games ("
    "identifier      INTEGER PRIMARY KEY,"
    "title           VARCHAR(128),"
    "author          VARCHAR(128),"
    "coverImageURL   VARCHAR(128),"
    "tagline         VARCHAR(128),"
    "genres          INTEGER,"
    "platforms       INTEGER,"
    "status          INTEGER,"
    "tags            VARCHAR(128),"
    "visibility      INTEGER,"
    "type            VARCHAR(128),"
    "publishDate     VARCHAR(128)"
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
void GameDAO::populateTables()
{
    const auto& titles  = std::array<QString, 5>{"Hurricane","Metro","Asimov","Pelagic","Hurricane X"};
    const auto& authors = std::array<QString, 5>{"Me","Him","Her","Them","Me"};

    Game g;
    for (unsigned i = 0; i < titles.size(); ++i)
    {
        g.identifier = i;
        g.title = titles[i];
        g.author = authors[i];

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
    ":coverImageURL,"
    ":tagline,"
    ":genres,"
    ":platforms,"
    ":status,"
    "NULL," //TODO tags
    "NULL," //TODO visibility
    "NULL," //TODO type
    "NULL" //TODO publishDate
    ")";

    QSqlQuery query(database_);
    query.prepare(INSERT_STATEMENT);

    query.bindValue(":identifier", game.identifier);
    query.bindValue(":title", game.title);
    query.bindValue(":author", game.author);
    query.bindValue(":coverImageURL", game.coverImageURL);
    query.bindValue(":tagline", game.tagline);
    query.bindValue(":genres", toInteger(game.genres));
    query.bindValue(":platforms", toInteger(game.platforms));
    query.bindValue(":status", static_cast<int>(game.status));

    query.exec();
}
/*!
 * \brief Returns the game with the specified \a identifier in the database.
 */
Game GameDAO::get(const unsigned int& identifier) const
{
    const auto& SELECT_STATEMENT = QString("SELECT * FROM games WHERE identifier = '%1'").arg(identifier);

    auto query = database_.exec(SELECT_STATEMENT);

    return query.next() ? toDomainObject(query) : Game();
}
/*!
 * \brief Returns all games in the database.
 */
QList<Game> GameDAO::getAll() const
{
    QList<Game> result;
    auto query = database_.exec("SELECT * FROM games");
    while (query.next())
        result.append(toDomainObject(query));

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
        result.append(toDomainObject(query));

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
        result.append(toDomainObject(query));

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
        result.append(toDomainObject(query));

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
        result.append(toDomainObject(query));

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
        result.append(toDomainObject(query));

    return result;
}
/*!
 * \brief Returns all games with the specified \a visibility.
 */
QList<Game> GameDAO::getGamesByVisibility(const Game::Visibility& visibility) const
{
    const auto& SELECT_STATEMENT =
    QString("SELECT * FROM games WHERE visibility = '%1'").arg(static_cast<int>(visibility));

    QList<Game> result;
    auto query = database_.exec(SELECT_STATEMENT);
    while (query.next())
        result.append(toDomainObject(query));

    return result;
}
/*!
 * \brief Returns the result of an SQL query in the form of a Game object.
 */
Game GameDAO::toDomainObject(const QSqlQuery& query) const
{
    Game result;

    result.identifier     = query.value(0).toInt();
    result.title          = query.value(1).toString();
    result.author         = query.value(2).toString();
    result.coverImageURL  = query.value(3).toString();
    result.tagline        = query.value(4).toString();
    result.genres         = toGenres(query.value(5).toInt());
    result.platforms      = toPlatforms(query.value(6).toInt());
    result.status         = static_cast<Game::Status>(query.value(7).toInt());
//    result.tags           = query.value(8).toInt();
//    result.visibility     = query.value(9).toInt();
//    result.type           = query.value(10).toString();
//    result.publishDate    = query.value(11).toString();

    return result;
}
/*!
 * \brief Converts a set of \a genres into an integer bit field.
 */
int GameDAO::toInteger(const QSet<Game::Genre>& genres)
{
    //TODO Implement me.
    Q_UNUSED(genres);
    return 0;
}
/*!
 * \brief Converts a set of \a platforms into an integer bit field.
 */
int GameDAO::toInteger(const QSet<Game::Platform>& platforms)
{
    //TODO Implement me.
    Q_UNUSED(platforms);
    return 0;
}
/*!
 * \brief Converts an integer bit \a field into a set of genres.
 */
QSet<Game::Genre> GameDAO::toGenres(const int field)
{
    //TODO Implement me.
    Q_UNUSED(field);
    return QSet<Game::Genre>();
}
/*!
 * \brief Converts an integer bit \a field into a set of platforms.
 */
QSet<Game::Platform> GameDAO::toPlatforms(const int field)
{
    //TODO Implement me.
    Q_UNUSED(field);
    return QSet<Game::Platform>();
}
