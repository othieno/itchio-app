#include "window.h"
#include "ui_window.h"
#include <QSystemTrayIcon>

using itchio::Window;

/*!
 * \brief Instantiates the main window of the specified \a application.
 */
Window::Window(Application& application) :
QMainWindow(nullptr, Qt::CustomizeWindowHint | Qt::FramelessWindowHint),
application_(application),
ui_(nullptr),
catalogView_(nullptr),
libraryView_(nullptr),
systemTrayIcon_(nullptr)
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
 * \brief Displays the modal dialog with the specified \a identifier.
 * Returns true if the dialog was accepted, false otherwise.
 */
bool Window::openModalDialog(const ModalDialog::Identifier& identifier)
{
    // Note: QDialog::exec ensures modality, as opposed to QDialog::show.
    return ModalDialog(identifier, application_).exec() == QDialog::Accepted;
}
/*!
 * \brief Handles the window's show \a event.
 */
void Window::showEvent(QShowEvent* const event)
{
    // If the user interface has not been initialized, do so.
    if (ui_ == nullptr)
    {
        ui_ = new Ui::Window;
        Q_ASSERT(ui_ != nullptr);
        ui_->setupUi(this);

        setWindowIcon(QIcon(":/images/window.icon"));

#ifdef TODO
        //TODO Complete me.
//        catalogView_ = new CatalogView(this);
//        libraryView_ = new LibraryView(this);
#endif
        if (systemTrayIcon_ == nullptr)
        {
            systemTrayIcon_ = new QSystemTrayIcon(QIcon(":/images/tray.icon"), this);
            systemTrayIcon_->setContextMenu(nullptr); //FIXME Set correct context menu.
            systemTrayIcon_->show();
        }
    }
/*
        window.setupSizeGrip();
        layout.addWidget(libraryView_);
        window.sizeGrip->show();
        window.onWidgetChange(libraryView_);
        window.move(QApplication::desktop()->screen(QApplication::desktop()->screenNumber(&window))->rect().center() - window.rect().center());
*/
    QMainWindow::showEvent(event);
}
/*!
 * \brief Handles the window's close \a event.
 */
void Window::closeEvent(QCloseEvent* const event)
{
#ifdef TODO
    event->ignore();
    hide();
#endif
    QMainWindow::closeEvent(event);
}
