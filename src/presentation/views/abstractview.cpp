#include "abstractview.h"
#include "application.h"
#include <QStyleOption>
#include <QPainter>

using itchio::AbstractView;

/*!
 * \brief Instantiates an AbstractView that is a child of the specified \a parent.
 */
AbstractView::AbstractView(QWidget& parent) :
QWidget(&parent)
{}
/*!
 * \brief Returns the view's full title, i.e. the application name appended to the view's window title.
 */
QString AbstractView::fullWindowTitle() const
{
    return QString("%1 - %2").arg(windowTitle(), QCoreApplication::applicationName());
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
/*!
 * \brief Overwrites the paintEvent handler to enable custom widget stylsheets.
 */
void AbstractView::paintEvent(QPaintEvent *e)
{
    QStyleOption option;
    option.init(this);

    QPainter painter(this);

    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);

    QWidget::paintEvent(e);
}
