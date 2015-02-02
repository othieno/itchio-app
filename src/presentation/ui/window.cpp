#include "window.h"
#include "application.h"
#include "modaldialog.h"
#include "catalogview.h"
#include "libraryview.h"

using itchio::Window;

/*!
 * \brief Instantiates the main window of the specified \a application.
 */
Window::Window(Application& application) :
FramelessWidget<QMainWindow, Ui::Window>(application, QIcon(":/icon/window")),
systemTrayIcon_(QIcon(":/icon/system-tray"))
{
    connect(titleBar_.settingsButton(), &QPushButton::clicked, [this](){ ModalDialog::open(ModalDialog::View::Settings, application_); });
}
/*!
 * \brief Initializes the window's GUI.
 */
void Window::initializeUi()
{
    initializeContentViews();
    initializeSystemTrayIcon();
}
/*!
 * \brief Initializes the content views.
 */
void Window::initializeContentViews()
{
    if (centralWidgetContent != nullptr)
    {
        connect(centralWidgetContent, &QTabWidget::currentChanged, [this]
        {
            auto* const currentView = centralWidgetContent->currentWidget();
            if (currentView != nullptr)
                onViewChanged(static_cast<AbstractView&>(*currentView));
        });

        for (auto* const view : std::initializer_list<AbstractView*>
        {
            new CatalogView(*centralWidgetContent, application_),
            new LibraryView(*centralWidgetContent, application_),
        })
        {
            if (view != nullptr)
                centralWidgetContent->addTab(view, view->windowTitle());
        }
        // Select the LibraryView by default.
        centralWidgetContent->setCurrentIndex(1);
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
    setWindowTitle(view.fullWindowTitle());
}
