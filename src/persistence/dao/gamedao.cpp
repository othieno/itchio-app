#include "gamedao.h"
#include "game.h"

using itchio::GameDAO;

GameDAO::GameDAO(DatabaseManager& manager) :
AbstractDAO(manager)
{}

void GameDAO::save(const Game& game)
{
    database_.insert(game.identifier, game);
}

itchio::Game GameDAO::get(const unsigned int& identifier) const
{
    return database_.value(identifier);
}

QList<itchio::Game> GameDAO::getAll() const
{
    return database_.values();
}

void GameDAO::remove(const unsigned int& identifier)
{
    database_.remove(identifier);
}

void GameDAO::remove(const Game& game)
{
    remove(game.identifier);
}

QList<itchio::Game> GameDAO::getGamesByTitle(const QString& title) const
{
    QList<Game> results;
    for (const auto& game : getAll())
    {
        if (game.title == title)
            results.append(game);
    }
    return results;
}

QList<itchio::Game> GameDAO::getGamesByAuthor(const QString& author) const
{
    QList<Game> results;
    for (const auto& game : getAll())
    {
        if (game.author == author)
            results.append(game);
    }
    return results;
}
