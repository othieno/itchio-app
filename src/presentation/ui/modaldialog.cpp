#include "modaldialog.h"
#include "ui_modaldialog.h"
#include "titlebar.h"
#include "application.h"
#include "authenticationview.h"

using itchio::ModalDialog;
using itchio::AbstractView;

/*!
 * Instantiates a ModalDialog with the specified \a view.
 */
ModalDialog::ModalDialog(const ModalDialog::View& view, Application& application) :
QDialog(nullptr, Qt::CustomizeWindowHint |  Qt::FramelessWindowHint | Qt::Dialog),
ui_(new Ui::ModalDialog),
titlebar_(new Titlebar(*this))
{
    Q_ASSERT(ui_ != nullptr);
    Q_ASSERT(titlebar_ != nullptr);

    ui_->setupUi(this);
    ui_->titlebarFrameLayout->addWidget(titlebar_);



    //TODO Implement me.
    ui_->buttonBox->hide();



    setWindowIcon(QIcon(":/icon/window"));
    setModal(true);
    setView(view, application);

    titlebar_->showSettingsButton(false);
    titlebar_->showMinimizeButton(false);
}
/*!
 * \brief Destroys the ModalDialog instance.
 */
ModalDialog::~ModalDialog()
{
    // Note that titlebar_ is a child to another QObject child so it's memory cleanup is handled by Qt.
    delete ui_;
}
/*!
 * \brief Centers the modal dialog.
 */
void ModalDialog::setCentered()
{
    move(QPoint(0, 0));
}
/*!
 * \brief Enables window resizing if \a resizable is set to true, disables it otherwise.
 */
void ModalDialog::setResizable(const bool resizable)
{
    auto* const dialogLayout = ui_->modalDialogLayout;
    if (dialogLayout != nullptr)
        dialogLayout->setSizeConstraint(resizable ? QLayout::SetDefaultConstraint : QLayout::SetFixedSize);

    titlebar_->showResizeButtons(resizable);
}
/*!
 * \brief Sets the modal dialog's central widget to the specified \a view.
 */
void ModalDialog::setView(const ModalDialog::View& view, Application& application)
{
    auto* const layout = ui_->contentFrameLayout;
    if (layout != nullptr)
    {
        AbstractView* viewInstance = nullptr;

        switch (view)
        {
            case ModalDialog::View::Authentication:
                viewInstance = new AuthenticationView(*this, application);
                break;
            default:
                break;
        }

        if (viewInstance != nullptr)
        {
            // Move the view instance to the content frame so it's properly positioned in the GUI.
            layout->addWidget(viewInstance);

            titlebar_->setTitle(viewInstance->title());
            setResizable(viewInstance->isResizable());

            if (viewInstance->isCentered())
                setCentered();
        }
    }
}
/*!
 * \brief Handles a dialog's change \a event, more specifically the window state change event.
 */
void ModalDialog::changeEvent(QEvent* const event)
{
    if (titlebar_ != nullptr && event != nullptr && event->type() == QEvent::WindowStateChange)
        titlebar_->onWindowStateChanged();

    QDialog::changeEvent(event);
}
