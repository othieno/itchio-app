#include "modaldialog.h"
#include "ui_modaldialog.h"
#include "titlebar.h"
#include "application.h"
#include "authenticationview.h"
#include "settingsview.h"

using itchio::ModalDialog;
using itchio::AbstractView;

/*!
 * Instantiates a ModalDialog with the specified \a view.
 */
ModalDialog::ModalDialog(const ModalDialog::View& view, Application& application, const QVariant& args) :
FramelessWidget<QDialog, Ui::ModalDialog>(application, QIcon(":/icon/window")),
view_(view),
viewArguments_(args)
{}
/*!
 * \brief Displays a modal dialog with the specified \a view.
 * Returns true if the dialog was accepted, false otherwise.
 */
bool ModalDialog::open(const ModalDialog::View& view, Application& application, const QVariant& args)
{
    return ModalDialog(view, application, args).exec() == QDialog::Accepted;
}
/*!
 * \brief Initializes the modal dialog's GUI.
 */
void ModalDialog::initializeUi()
{
    setView(view_, application_, viewArguments_);
}
/*!
 * \brief Centers the modal dialog.
 */
void ModalDialog::setCentered()
{
    //TODO Implement me.
//    move(QApplication::desktop()->screen(QApplication::desktop()->screenNumber(this))->rect().center() - rect().center());
}
/*!
 * \brief Enables window resizing if \a resizable is set to true, disables it otherwise.
 */
void ModalDialog::setResizable(const bool resizable)
{
    if (modalDialogLayout != nullptr)
    {
        modalDialogLayout->setSizeConstraint(resizable ? QLayout::SetDefaultConstraint : QLayout::SetFixedSize);
        titleBar_.showResizeButtons(resizable);
    }
}
/*!
 * \brief Sets the modal dialog's central widget to the specified \a view.
 */
void ModalDialog::setView(const ModalDialog::View& view, Application& application, const QVariant&)
{
    if (contentFrameLayout != nullptr)
    {
        AbstractView* viewInstance = nullptr;

        switch (view)
        {
            case ModalDialog::View::Authentication:
                viewInstance = new AuthenticationView(*this, application);
                break;
            case ModalDialog::View::Settings:
                viewInstance = new SettingsView(*this, application);
                break;
            default:
                break;
        }

        if (viewInstance != nullptr)
        {
            // Move the view instance to the content frame so it's properly positioned in the GUI.
            contentFrameLayout->addWidget(viewInstance);

            setWindowTitle(viewInstance->fullWindowTitle());
            setResizable(viewInstance->isResizable());

            if (viewInstance->isCentered())
                setCentered();
        }

        //TODO Implement button box.
        buttonBox->hide();
    }
}
