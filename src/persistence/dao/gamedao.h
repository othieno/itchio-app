#ifndef GAMEDAO_H
#define GAMEDAO_H

#include "abstractdao.h"
#include "game.h"

namespace itchio {

class GameDAO Q_DECL_FINAL : public AbstractDAO<Game, unsigned int>
{
public:
    explicit GameDAO(Database& database);

    void createTables() Q_DECL_OVERRIDE;
    void dropTables() Q_DECL_OVERRIDE;
    void insertMockRecords() Q_DECL_OVERRIDE;

    void save(const Game& game) Q_DECL_OVERRIDE;

    Game get(const unsigned int& identifier) const Q_DECL_OVERRIDE;
    QList<Game> getAll() const Q_DECL_OVERRIDE;

    void remove(const unsigned int& identifier) Q_DECL_OVERRIDE;

    QList<Game> getGamesByTitle(const QString& title, const bool caseInsensitive = true) const;
    QList<Game> getGamesByAuthor(const QString& author, const bool caseInsensitive = true) const;
    QList<Game> getGamesByGenre(const Game::Genre& genre) const;
    QList<Game> getGamesByPlatform(const Content::Platform& platform) const;
    QList<Game> getGamesByStatus(const Content::Status& status) const;
    QList<Game> getGamesByPermission(const Content::Permission& permission) const;
};

} // namespace itchio

#endif // GAMEDAO_H
