#ifndef GAME_H
#define GAME_H

#include "content.h"
#include "price.h"
#include <QLinkedList>

class QJsonObject;

namespace itchio {

struct Game : public Content
{
    /*!
     * An enumeration of all possible genres.
     * PS. If a new genre is added, make sure the listOfGameGenres function is updated.
     */
    enum class Genre
    {
        Other         = 0x0000,
        Action        = 0x0001,
        Platformer    = 0x0002,
        Shooter       = 0x0004,
        Adventure     = 0x0008,
        RolePlaying   = 0x0010,
        Simulation    = 0x0020,
        Strategy      = 0x0040,
        Puzzle        = 0x0080,
        Sports        = 0x0100
    };
    Q_DECLARE_FLAGS(Genres, Genre)
    static QLinkedList<Genre> listOfGameGenres();

    Game();
    explicit Game(const QJsonObject& jsonObject);
    explicit Game(const QSqlRecord& sqlRecord);

    QString tagline; // a.k.a. shortText.
    QString type; //TODO Find out exactly what a game 'type' is. Is it a genre? Or does it refer to a content type?
    Genres  genres;
};

} // namespace itchio

Q_DECLARE_OPERATORS_FOR_FLAGS(itchio::Game::Genres)

#endif // GAME_H
