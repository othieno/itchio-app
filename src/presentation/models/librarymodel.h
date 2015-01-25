#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <QSqlQueryModel>
#include "game.h"

namespace itchio {

class LibraryView;
class ContentManager;
class GameDAO;

class LibraryModel Q_DECL_FINAL : public QSqlQueryModel
{
    Q_OBJECT
    friend class LibraryView;
public:
    enum class Filter
    {
        None,
        Purchases
    };

    void setFilter(const Filter& filter);
    const Filter& filter() const;
    QSqlQuery filterQuery(const Filter& filter) const;

    Game contentAt(const QModelIndex& index) const;
private:
    explicit LibraryModel(ContentManager& contentManager);

    ContentManager& contentManager_;
    const GameDAO& gameDAO_;

    Filter filter_;
signals:
    void updated();
};

} // namespace itchio

#endif // LIBRARYMODEL_H
