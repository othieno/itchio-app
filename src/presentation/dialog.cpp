#include "dialog.h"
#include "ui_window.h"
#include "application.h"
#include "authenticationview.h"

using itchio::Dialog;
using itchio::AbstractView;

/*!
 * Instantiates a Dialog with the specified \a type.
 */
Dialog::Dialog(const DialogViewType& type, Application& application) :
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
    auto* const view = createDialogView(type, application);
    if (view != nullptr)
    {
        setWindowTitle(QString("%1 - %2").arg(application.applicationName(), view->title()));
        setResizable(view->isResizable());
        setCentered(view->isCentered());
    }
}
/*!
 * \brief Destroys the Dialog instance.
 */
Dialog::~Dialog()
{
    delete ui_;
}
/*!
 * \brief Centers the dialog window if \a centered is set to true, otherwise does nothing.
 */
void Dialog::setCentered(const bool centered)
{
    if (centered)
        move(QPoint(0, 0));
}
/*!
 * \brief Enables window resizing if \a resizable is set to true, disables it otherwise.
 */
void Dialog::setResizable(const bool resizable)
{
    auto* const dialogLayout = layout();
    if (dialogLayout != nullptr)
        dialogLayout->setSizeConstraint(resizable ? QLayout::SetDefaultConstraint : QLayout::SetFixedSize);
}
/*!
 * \brief Instantiates an AbstractView with the specified \a type that is a child of this dialog window.
 */
AbstractView* Dialog::createDialogView(const DialogViewType& type, Application& application)
{
    switch (type)
    {
        case DialogViewType::Authentication:
            return new AuthenticationView(this, application.authenticator());
        default:
            return nullptr;
    }
}
