#include "modalwindow.h"
#include "window.h"
#include "application.h"
#include "loginpromptview.h"
#include <QLayout>

using itchio::ModalWindow;
using itchio::View;

/*!
 * TODO Document me.
 */
ModalWindow::ModalWindow(const Qt::WindowModality modality, Application& application, const View::Identifier& identifier) :
QDialog(nullptr)//, Qt::CustomizeWindowHint |  Qt::FramelessWindowHint | Qt::Dialog)
{
//    ui_.setupUi(this);

    setWindowModality(modality);
    setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));
    setModal(true);
#ifdef FIXME
//    setupSizeGrip();
//    onWidgetChange(*this);
//    sizeGrip->hide();
#endif
    auto* const view = createModalView(identifier, application);
    if (view != nullptr)
    {
        setWindowTitle(QString("%1 - %2").arg(application.applicationName(), view->title()));
        setResizable(view->isResizable());
        setCentered(view->isCentered());
    }
}
/*!
 * \brief Instantiates a View with the specified \a identifier that is a child of this modal window.
 */
View* ModalWindow::createModalView(const View::Identifier& identifier, Application& application)
{
    switch (identifier)
    {
        case View::Identifier::LoginPrompt:
            return new LoginPromptView(application.authenticator(), this);

        case View::Identifier::None:
        default:
            return nullptr;
    }
}
/*!
 * \brief Centers the modal window if \a centered is set to true.
 */
void ModalWindow::setCentered(const bool centered)
{
    if (centered)
        move(QPoint(0, 0));
}
/*!
 * \brief Enables window resizing if \a resizable is set to true, disables it otherwise.
 */
void ModalWindow::setResizable(const bool resizable)
{
    auto* const l = layout();
    if (l != nullptr)
        l->setSizeConstraint(resizable ? QLayout::SetDefaultConstraint : QLayout::SetFixedSize);
}
