#ifndef GAMEDAO_H
#define GAMEDAO_H

#include "abstractdao.h"
#include "game.h"

namespace itchio {

class GameDAO Q_DECL_FINAL : public AbstractDAO<Game, unsigned int>
{
public:
    explicit GameDAO(Database& database);

    void save(const Game& game) Q_DECL_OVERRIDE;

    Game get(const unsigned int& identifier) const Q_DECL_OVERRIDE;
    QList<Game> getAll() const Q_DECL_OVERRIDE;

    void remove(const unsigned int& identifier) Q_DECL_OVERRIDE;

    QList<Game> getGamesByTitle(const QString& title, const bool caseInsensitive = true) const;
    QList<Game> getGamesByAuthor(const QString& author, const bool caseInsensitive = true) const;
    QList<Game> getGamesByGenre(const Game::Genre& genre) const;
    QList<Game> getGamesByPlatform(const Game::Platform& platform) const;
    QList<Game> getGamesByStatus(const Game::Status& status) const;
    QList<Game> getGamesByVisibility(const Game::Visibility& visibility) const;
private:
    void createTables() Q_DECL_OVERRIDE;
    void dropTables() Q_DECL_OVERRIDE;
    void populateTables() Q_DECL_OVERRIDE;

    Game toDomainObject(const QSqlQuery& query) const Q_DECL_OVERRIDE;

    static int toInteger(const QSet<Game::Genre>& genres);
    static int toInteger(const QSet<Game::Platform>& platforms);

    static QSet<Game::Genre> toGenres(const int bitField);
    static QSet<Game::Platform> toPlatforms(const int bitField);
};

} // namespace itchio

#endif // GAMEDAO_H
