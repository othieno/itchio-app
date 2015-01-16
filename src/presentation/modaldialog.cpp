#include "modaldialog.h"
#include "ui_window.h"
#include "application.h"
#include "authenticationview.h"

using itchio::ModalDialog;
using itchio::AbstractView;

/*!
 * Instantiates a ModalDialog with the specified \a type.
 */
ModalDialog::ModalDialog(const ModalDialog::Identifier& identifier, Application& application) :
QDialog(nullptr/*TODO , Qt::CustomizeWindowHint |  Qt::FramelessWindowHint | Qt::Dialog*/),
ui_(new Ui::Window)
{
    Q_ASSERT(ui_ != nullptr);
    //TODO Uncomment this when the dialog UI is complete.
//    ui_->setupUi(this);

    setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));
    setModal(true);
#ifdef FIXME
//    setupSizeGrip();
//    onWidgetChange(*this);
//    sizeGrip->hide();
#endif
    auto* const view = createDialogView(identifier, application);
    if (view != nullptr)
    {
        setWindowTitle(QString("%1 - %2").arg(application.applicationName(), view->title()));
        setResizable(view->isResizable());
        setCentered(view->isCentered());
    }
}
/*!
 * \brief Destroys the ModalDialog instance.
 */
ModalDialog::~ModalDialog()
{
    delete ui_;
}
/*!
 * \brief Centers the modal dialog if \a centered is set to true, otherwise does nothing.
 */
void ModalDialog::setCentered(const bool centered)
{
    if (centered)
        move(QPoint(0, 0));
}
/*!
 * \brief Enables window resizing if \a resizable is set to true, disables it otherwise.
 */
void ModalDialog::setResizable(const bool resizable)
{
    auto* const dialogLayout = layout();
    if (dialogLayout != nullptr)
        dialogLayout->setSizeConstraint(resizable ? QLayout::SetDefaultConstraint : QLayout::SetFixedSize);
}
/*!
 * \brief Instantiates an AbstractView with the specified \a identifier that is a child of this dialog window.
 */
AbstractView* ModalDialog::createDialogView(const ModalDialog::Identifier& identifier, Application& application)
{
    switch (identifier)
    {
        case ModalDialog::Identifier::Authentication:
            return new AuthenticationView(*this, application.authenticator());
        default:
            return nullptr;
    }
}
