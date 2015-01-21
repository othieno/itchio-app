#include "libraryview.h"

using itchio::LibraryView;

/*!
 * \brief Instantiates a LibraryView that is a child of \a parent.
 */
LibraryView::LibraryView(QWidget& parent, Application& application) :
AbstractView(parent)
{
    ui_.setupUi(this);
    Q_UNUSED(application);
}
/*!
 * \brief Returns the view's caption.
 */
QString LibraryView::caption() const
{
    return "Library";
}
