#include "window.h"
#include "ui_window.h"
#include "modaldialog.h"
#include <QPushButton>
#include "titlebar.h"
#include "application.h"
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
titlebar_(nullptr),
systemTrayIcon_(QIcon(":/icon/system-tray"))
{
    setWindowIcon(QIcon(":/icon/window"));
}
/*!
 * \brief Destroys the Window instance.
 */
Window::~Window()
{
    // Note that titlebar_ is a child to another QObject child so it's memory cleanup is handled by Qt.
    if (ui_ != nullptr)
        delete ui_;
}
/*!
 * \brief Initializes the content views.
 */
void Window::initializeUserInterface()
{
    ui_ = new Ui::Window;
    titlebar_ = new Titlebar(*this);

    Q_ASSERT(ui_ != nullptr);
    Q_ASSERT(titlebar_ != nullptr);

    ui_->setupUi(this);
    ui_->titlebarFrameLayout->addWidget(titlebar_);

    connect(titlebar_->settingsButton(), &QPushButton::clicked, [this](){ ModalDialog::open(ModalDialog::View::Settings, application_); });
    titlebar_->setTitle(application_.organizationDomain());
}
/*!
 * \brief Initializes the content views.
 */
void Window::initializeContentViews()
{
    auto& parent = *ui_->centralWidgetContent;

    if (ui_ != nullptr && ui_->centralWidgetContent != nullptr)
    {
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
                parent.addTab(view, view->windowTitle());
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
 * \brief Handles a window's change \a event, more specifically the window state change event.
 */
void Window::changeEvent(QEvent* const event)
{
    if (titlebar_ != nullptr && event != nullptr && event->type() == QEvent::WindowStateChange)
        titlebar_->onWindowStateChanged();

    QMainWindow::changeEvent(event);
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
