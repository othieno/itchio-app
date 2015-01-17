#include "window.h"
#include "ui_window.h"
#include "catalogview.h"
#include "libraryview.h"

using itchio::Window;

/*!
 * \brief Instantiates the main window of the specified \a application.
 */
Window::Window(Application& application) :
QMainWindow(nullptr, Qt::CustomizeWindowHint | Qt::FramelessWindowHint),
application_(application),
ui_(nullptr),
systemTrayIcon_(QIcon(":/images/tray.icon"))
{
    setWindowIcon(QIcon(":/images/window.icon"));
}
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
    return ModalDialog(identifier, application_).exec() == QDialog::Accepted;
}
/*!
 * \brief Initializes the content views.
 */
void Window::initializeUserInterface()
{
    ui_ = new Ui::Window;
    Q_ASSERT(ui_ != nullptr);
    ui_->setupUi(this);

    connect(ui_->settingsButton, &QPushButton::clicked, [this]
    {
        openModalDialog(ModalDialog::Identifier::Settings);
    });
}
/*!
 * \brief Initializes the content views.
 */
void Window::initializeContentViews()
{
    if (ui_ != nullptr && ui_->centralWidgetContent != nullptr)
    {
        auto& parent = *ui_->centralWidgetContent;

        connect(&parent, &QTabWidget::currentChanged, [this, &parent]
        {
            auto* const currentView = parent.currentWidget();
            if (currentView != nullptr)
                onViewChanged(static_cast<AbstractView&>(*currentView));
        });

        for (auto* const view : std::initializer_list<AbstractView*>
        {
            new CatalogView(parent, application_),
            new LibraryView(parent, application_),
        })
        {
            if (view != nullptr)
                parent.addTab(view, view->title());
        }
        // Select the LibraryView by default.
        parent.setCurrentIndex(1);
    }
}
/*!
 * \brief Initializes the system tray icon.
 */
void Window::initializeSystemTrayIcon()
{
    systemTrayIcon_.setContextMenu(nullptr); //FIXME Set correct context menu.
    systemTrayIcon_.show();
}
/*!
 * \brief Handles the window's show \a event.
 */
void Window::showEvent(QShowEvent* const event)
{
    // If the user interface has not been initialized, do so.
    if (ui_ == nullptr)
    {
        initializeUserInterface();
        initializeContentViews();
        initializeSystemTrayIcon();
    }
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
/*!
 * \brief Handles the signal emitted when views are changed.
 */
void Window::onViewChanged(AbstractView& view)
{
    //TODO Implement me.
    Q_UNUSED(view);
}
