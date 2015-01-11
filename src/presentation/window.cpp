#include "window.h"
#include "modalwindow.h"

using itchio::Window;
using itchio::ModalWindow;
using itchio::View;

/*!
 * \brief Instantiates the main window of a specified \a application.
 */
Window::Window(Application& application) :
application_(application)
{}
/*!
 * \brief Returns the current view's identifier, or View::Identifier::None is no view is set.
 */
View::Identifier Window::viewIdentifier() const
{
    return View::Identifier::None;//TODO view_ != nullptr ? view_->identifier() : View::Identifier::None;
}
/*!
 * \brief Sets the window's view to the view with the specified \a identifier.
 */
void Window::setView(const View::Identifier& identifier)
{
    //TODO Implement me.
    Q_UNUSED(identifier);
}
/*!
 * \brief Displays the modal dialog with the view specified by \a identifier.
 */
int Window::openModalWindow(const View::Identifier& identifier, const Qt::WindowModality modality)
{
    // QDialog::exec ensures modality, as opposed to QDialog::show.
    return ModalWindow(modality, application_, identifier).exec();
}
