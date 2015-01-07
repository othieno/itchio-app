#ifndef GAMEDAO_H
#define GAMEDAO_H

#include "abstractdao.h"
#include "game.h"

namespace itchio {

class GameDAO Q_DECL_FINAL : public AbstractDAO<Game, unsigned int>
{
public:
    explicit GameDAO(DatabaseManager& manager);

    void save(const Game& game) Q_DECL_OVERRIDE;

    Game get(const unsigned int& identifier) const Q_DECL_OVERRIDE;
    QList<Game> getAll() const Q_DECL_OVERRIDE;

    void remove(const unsigned int& identifier) Q_DECL_OVERRIDE;
    void remove(const Game& game) Q_DECL_OVERRIDE;

    QList<Game> getGamesByTitle(const QString& title) const;
    QList<Game> getGamesByAuthor(const QString& author) const;
//    QList<Game> getGamesByCollection(const unsigned int collection) const;
//    QList<Game> getGamesByPlatform(const Platform& platform);
};

} // namespace itchio

#endif // GAMEDAO_H
