#include "libraryview.h"
#include "application.h"
#include "gamedao.h"
#include <QSqlQuery>

using itchio::LibraryView;

/*!
 * \brief Instantiates a LibraryView that is a child of \a parent.
 */
LibraryView::LibraryView(QWidget& parent, Application& application) :
AbstractView(parent),
contentManager_(application.contentManager()),
filter_(Filter::All)
{
    ui_.setupUi(this);
    ui_.contentTitleView->setModel(&model_);

    connect(ui_.contentTitleView, &QListView::clicked, this, &LibraryView::onItemSelected);
    connect(&delayTimer_, &QTimer::timeout, this, &LibraryView::onUpdateDetailedView);
    connect(&contentManager_, &ContentManager::libraryUpdated, this, &LibraryView::onLibraryUpdated);

    delayTimer_.setSingleShot(true);
    delayTimer_.setInterval(LibraryView::DELAY_TIMER_INTERVAL);

    // Initialize the model.
    model_.setQuery(filterQuery(filter_));
}
/*!
 * \brief Sets the view's \a filter.
 */
void LibraryView::setFilter(const Filter& filter)
{
    if (filter_ != filter)
    {
        filter_ = filter;
        model_.setQuery(filterQuery(filter));
    }
}
/*!
 * \brief Returns the current filter.
 */
const LibraryView::Filter& LibraryView::filter() const
{
    return filter_;
}
/*!
 * \brief Returns the database query associated with a specified \a filter.
 */
QSqlQuery LibraryView::filterQuery(const Filter& filter) const
{
    switch (filter)
    {
        case Filter::All:
            return contentManager_.executeDatabaseQuery("SELECT title, identifier FROM games");
        default:
            return QSqlQuery();
    }
}
/*!
 * \brief Starts the delay timer when a new item is selected.
 * When the delay timer times out, then the detailed view is updated.
 */
void LibraryView::onItemSelected(const QModelIndex& index)
{
    if (selectedIndex_ != index)
    {
        selectedIndex_ = index;
        delayTimer_.start();
    }
}
/*!
 * \brief Updates the detailed view.
 */
void LibraryView::onUpdateDetailedView()
{
    const auto& gameIdentifier = unsigned(model_.data(model_.index(selectedIndex_.row(), 1)).toInt());
    const auto& game = contentManager_.gameDAO().get(gameIdentifier);

    ui_.detail->setText(game);
}
/*!
 * \brief Updates the view when the library is updated.
 */
void LibraryView::onLibraryUpdated()
{
    //TODO Implement me.
}
