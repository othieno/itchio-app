#include "librarymodel.h"
#include "contentmanager.h"
#include <QSqlQuery>

using itchio::LibraryModel;
using itchio::Game;

/*!
 * \brief Instantiates a LibraryModel that is bound to the specified \a contentManager.
 */
LibraryModel::LibraryModel(ContentManager& contentManager) :
contentManager_(contentManager),
gameDAO_(contentManager_.gameDAO()),
filter_(Filter::None)
{
    setQuery(filterQuery(filter_));
}
/*!
 * \brief Sets the model's \a filter.
 */
void LibraryModel::setFilter(const Filter& filter)
{
    if (filter_ != filter)
    {
        filter_ = filter;
        setQuery(filterQuery(filter));
    }
}
/*!
 * \brief Returns the model's current filter.
 */
const LibraryModel::Filter& LibraryModel::filter() const
{
    return filter_;
}
/*!
 * \brief Returns the database query associated with a specified \a filter.
 */
QSqlQuery LibraryModel::filterQuery(const Filter& filter) const
{
    switch (filter)
    {
        case Filter::None:
            return contentManager_.executeDatabaseQuery("SELECT title, identifier FROM games");
        default:
            return QSqlQuery();
    }
}
/*!
 * \brief Returns the content that corresponds to the specified view \a index.
 */
Game LibraryModel::contentAt(const QModelIndex& index) const
{
    return index.isValid() ? gameDAO_.get(unsigned(data(this->index(index.row(), 1)).toInt())) : Game();
}
