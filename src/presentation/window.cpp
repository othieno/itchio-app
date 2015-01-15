#include "window.h"
#include "ui_window.h"
#include "dialog.h"

using itchio::Window;

/*!
 * \brief Instantiates the main window of a specified \a application.
 */
Window::Window(Application& application) :
application_(application),
ui_(nullptr),
contentView_(nullptr)
{}
/*!
 * \brief Destroys the Window instance.
 */
Window::~Window()
{
    if (ui_ != nullptr)
        delete ui_;
}
/*!
 * \brief Displays the modal dialog with the specified view \a type.
 * Returns true if the dialog was accepted, false otherwise.
 */
bool Window::openDialog(const DialogViewType& type)
{
    // Note: QDialog::exec ensures modality, as opposed to QDialog::show.
    return Dialog(type, application_).exec() == QDialog::Accepted;
}
/*!
 * \brief Handles QShowEvents for the Window.
 */
void Window::showEvent(QShowEvent* const event)
{
#ifdef TODO
    // If the user interface has not been initialized, do so.
    if (ui_ == nullptr)
    {
        ui_ = new Ui::Window;
        Q_ASSERT(ui_ != nullptr);
        ui_->setupUi(this);

        //TODO Complete custom show event handler.
//        contentView_ = new ContentView();
    }

/*
        auto& layout = *window.widgetsLayout;

        window.hide();
        window.setupSizeGrip();
        layout.addWidget(libraryView_);
        window.sizeGrip->show();
        window.onWidgetChange(libraryView_);
        window.move(QApplication::desktop()->screen(QApplication::desktop()->screenNumber(&window))->rect().center() - window.rect().center());
        window.show();
*/
#endif
    QMainWindow::showEvent(event);
}
