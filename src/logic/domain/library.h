#ifndef LIBRARY_H
#define LIBRARY_H

#include <QList>

namespace itchio {

class LibraryController;

using Game = int;
using GameCollection = int;

class Library
{
    friend class LibraryController;

public:
    inline QList<Game>& games(){ return games_; }
    inline const QList<Game>& games() const { return games_; }

    inline QList<GameCollection>& collections(){ return collections_; }
    inline const QList<GameCollection>& collections() const { return collections_; }

    void addGame(const Game& game);
    void addGameCollection(const GameCollection& collection);

private:
    Library() = default;

    QList<Game> games_;
    QList<GameCollection> collections_;
};

} // namespace itchio

#endif // LIBRARY_H
