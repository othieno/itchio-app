#include "libraryview.h"
#include "application.h"

using itchio::LibraryView;

/*!
 * \brief Instantiates a LibraryView that is a child of \a parent.
 */
LibraryView::LibraryView(QWidget& parent, Application& application) :
AbstractView(parent),
model_(application.contentManager())
{
    ui_.setupUi(this);
    ui_.contentTitleView->setModel(&model_);

    connect(ui_.contentTitleView, &QListView::clicked, this, &LibraryView::onItemSelected);
    connect(&delayTimer_, &QTimer::timeout, this, &LibraryView::onUpdateDetails);
    connect(&model_, &LibraryModel::updated, this, &LibraryView::onLibraryUpdated);

    delayTimer_.setSingleShot(true);
    delayTimer_.setInterval(LibraryView::DELAY_TIMER_INTERVAL);
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
void LibraryView::onUpdateDetails()
{
    ui_.detail->setText(model_.contentAt(selectedIndex_));
}
/*!
 * \brief Updates the view when the library is updated.
 */
void LibraryView::onLibraryUpdated()
{
    //TODO Implement me.
}
