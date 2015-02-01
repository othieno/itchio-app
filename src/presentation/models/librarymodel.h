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
private slots:
    void onFileCacheChanged(const QString& fileName) const;
signals:
    void updated();


    /*!
     * \brief This signal is emitted when the cover image of the content with the given \a identifier is modified.
     */
    void coverImageChanged(const int identifier) const;
};

} // namespace itchio

#endif // LIBRARYMODEL_H
