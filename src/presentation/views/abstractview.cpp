#include "abstractview.h"
#include "application.h"

using itchio::AbstractView;

/*!
 * \brief Instantiates an AbstractView that is a child of the specified \a parent.
 */
AbstractView::AbstractView(QWidget& parent) :
QWidget(&parent)
{}
/*!
 * \brief Returns the view's full title, i.e. the application name appended to the view's caption.
 */
QString AbstractView::title() const
{
    return QString("%1 - %2").arg(caption(), QCoreApplication::applicationName());
}
/*!
 * \brief Returns true if this view is resizable, false otherwise.
 */
bool AbstractView::isResizable() const
{
    return true;
}
/*!
 * \brief Returns true if this view is centered on the screen by default, false otherwise.
 */
bool AbstractView::isCentered() const
{
    return false;
}
