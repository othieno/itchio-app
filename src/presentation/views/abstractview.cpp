#include "abstractview.h"

using itchio::AbstractView;

/*!
 * \brief Instantiates an AbstractView that is a child to the specified \a parent.
 */
AbstractView::AbstractView(QWidget* const parent) :
QWidget(parent)
{}
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
