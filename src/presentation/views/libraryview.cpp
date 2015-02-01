#include "libraryview.h"
#include "application.h"
#include "content.h"

using itchio::LibraryView;

/*!
 * \brief Instantiates a LibraryView that is a child of \a parent.
 */
LibraryView::LibraryView(QWidget& parent, Application& application) :
AbstractView(parent),
model_(application.contentManager()),
selectedIndex_(model_.index(0, 0))
{
    ui_.setupUi(this);
    ui_.contentTitles->setModel(&model_);
    ui_.contentTitles->setCurrentIndex(selectedIndex_);
//    ui_.contentPlatforms->hide();

    ui_.contentCoverImage->setMinimumSize(COVER_IMAGE_WIDTH, COVER_IMAGE_HEIGHT);
    ui_.contentCoverImage->setMaximumSize(COVER_IMAGE_WIDTH, COVER_IMAGE_HEIGHT);

    connect(ui_.contentTitles, &QListView::clicked, this, &LibraryView::onItemSelected);
    connect(&delayTimer_, &QTimer::timeout, this, &LibraryView::onUpdateDetails);
    connect(&model_, &LibraryModel::updated, this, &LibraryView::onLibraryUpdated);
    connect(&model_, &LibraryModel::coverImageChanged, this, &LibraryView::onCoverImageChanged);

    delayTimer_.setSingleShot(true);
    delayTimer_.setInterval(LibraryView::DELAY_TIMER_INTERVAL);

    // Update the details section.
    onUpdateDetails();
}
/*!
 * Creates a subtitle string.
 */
QString LibraryView::createSubtitleString(const Content& content)
{
    const auto& genres = "Action/Adventure";
    const auto& releaseDate = content.published ? content.publishDate.toString("MMMM yyyy") : "TBA";

    return QString("%1 %2 %3, %4").arg(genres, "&bull;", content.author, releaseDate);
}
#ifdef TODO
/*!
 * Creates a platform string.
 */
QString LibraryView::createPlatformsString(const Content::Platforms&)
{
    return QString("Available for Windows, OSX and Linux");
}
#endif
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
    const auto& content = model_.contentAt(selectedIndex_);

    currentContentIdentifier_ = content.identifier;

//    ui_.contentDetails->hide();

    ui_.contentCoverImage->setPixmap(QPixmap(content.coverImageCacheLocation()));
    ui_.contentTitle->setText(content.title);
    ui_.contentSubtitle->setText(createSubtitleString(content));
//    ui_.contentPlatforms->setText(createPlatformsString(content.platforms));
    ui_.contentTagline->setText(content.tagline);

//    ui_.contentDetails->show();
}
/*!
 * \brief Updates the view when the library is updated.
 */
void LibraryView::onLibraryUpdated()
{
    //TODO Implement me.
}
/*!
 * \brief Updates the cover image when it has been changed.
 */
void LibraryView::onCoverImageChanged(const int identifier)
{
    if (currentContentIdentifier_ == identifier)
        ui_.contentCoverImage->setPixmap(QPixmap(Content::coverImageCacheLocation(identifier)));
}
