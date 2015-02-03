#include "titlebar.h"
#include "framelesswidget.h"
#include "modaldialog.h"
#include <QMouseEvent>

//FIXME There is a bug when the window snaps to the desktop. The resize buttons should change
//      state but this doesn't happen. PS. Is this really a bug or more of a missing feature?

//FIXME There is a bug that unmaximizes (and minimizes) the window when the minimize button is pressed.

using itchio::TitleBar;

/*
 * Instantiates a TitleBar that interfaces with the specified \a widget.
 * The widget is implied to be frameless.
 */
TitleBar::TitleBar(QWidget& widget) :
widget_(widget),
widgetMovementToggled_(false),
showResizeButtons_(true),
showUnmaximizeButton_(false),
showMaximizeButton_(false)
{
    setupUi(this);

    connect(minimizeButton,   &QPushButton::clicked, this, &TitleBar::onMinimizeButtonClicked);
    connect(unmaximizeButton, &QPushButton::clicked, this, &TitleBar::onUnmaximizeButtonClicked);
    connect(maximizeButton,   &QPushButton::clicked, this, &TitleBar::onMaximizeButtonClicked);
    connect(closeButton,      &QPushButton::clicked, this, &TitleBar::onCloseButtonClicked);

    widgetMovementDelayTimer_.setInterval(DELAY_TIMER_INTERVAL);
    widgetMovementDelayTimer_.setSingleShot(true);

    connect(&widgetMovementDelayTimer_, &QTimer::timeout, [this]()
    {
        widgetMovementToggled_ = true;
        QApplication::setOverrideCursor(QCursor(Qt::ClosedHandCursor));
    });

    onWindowStateChange(widget_.windowState());
}
/*!
 * \brief Returns the settings button.
 */
QPushButton* TitleBar::settingsButton() const
{
    return Ui::TitleBar::settingsButton;
}
/*!
 * \brief Updates the title bar icon when the window \a icon changes.
 */
void TitleBar::onWindowIconChange(const QIcon& icon)
{
    Ui::TitleBar::icon->setPixmap(icon.pixmap(icon.actualSize(QSize(TITLEBAR_ICON_WIDTH, TITLEBAR_ICON_HEIGHT))));
}
/*!
 * \brief Updates the title bar's title when the window \a title changes.
 */
void TitleBar::onWindowTitleChange(const QString& title)
{
    Ui::TitleBar::title->setText(title);
}
/*!
 * \brief Updates the title bar when the window changes \a states.
 */
void TitleBar::onWindowStateChange(const Qt::WindowStates& states)
{
    showUnmaximizeButton_ = states.testFlag(Qt::WindowMaximized);
    showMaximizeButton_ = !showUnmaximizeButton_;

    unmaximizeButton->setVisible(showResizeButtons_ && showUnmaximizeButton_);
    maximizeButton->setVisible(showResizeButtons_ && showMaximizeButton_);
}
/*
 * Shows the settings button if \a show is set to true, hides it otherwise.
 */
void TitleBar::showSettingsButton(const bool show)
{
    settingsButton()->setVisible(show);
}
/*
 * Shows the minimize button if \a show is set to true, hides it otherwise.
 */
void TitleBar::showMinimizeButton(const bool show)
{
    minimizeButton->setVisible(show);
}
/*
 * Shows the resize buttons if \a show is set to true, hides them otherwise.
 */
void TitleBar::showResizeButtons(const bool show)
{
    showResizeButtons_ = show;
    onWindowStateChange(widget_.windowState());
}
/*!
 * \brief Handles the title bar's mouse click \a event.
 */
void TitleBar::mousePressEvent(QMouseEvent* const event)
{
    if (event->button() == Qt::MiddleButton)
        widget_.showMinimized();
    else
    {
        widgetInitialPosition_ = event->pos();
        widgetMovementDelayTimer_.start();
    }

    QWidget::mousePressEvent(event);
}
/*!
 * \brief Handles the title bar's mouse double-click \a event.
 */
void TitleBar::mouseDoubleClickEvent(QMouseEvent* const event)
{
    if (widget_.windowState().testFlag(Qt::WindowMaximized))
        widget_.showMinimized();
    else
        widget_.showMaximized();

    QWidget::mouseDoubleClickEvent(event);
}
/*!
 * \brief Handles the title bar's mouse release \a event.
 */
void TitleBar::mouseReleaseEvent(QMouseEvent* const event)
{
    if (widgetMovementDelayTimer_.isActive())
        widgetMovementDelayTimer_.stop();

    if (widgetMovementToggled_)
    {
        widgetMovementToggled_ = false;
        QApplication::restoreOverrideCursor();
    }

    QWidget::mouseReleaseEvent(event);
}
/*!
 * \brief Handles the title bar's mouse movement \a event.
 */
void TitleBar::mouseMoveEvent(QMouseEvent* const event)
{
    if (widgetMovementToggled_)
        widget_.move(event->globalPos() - widgetInitialPosition_);

    QWidget::mouseMoveEvent(event);
}
/*!
 * \brief Handles the minimize button's 'clicked' signal.
 */
void TitleBar::onMinimizeButtonClicked()
{
    widget_.showMinimized();
}
/*!
 * \brief Handles the unmaximize button's 'clicked' signal.
 */
void TitleBar::onUnmaximizeButtonClicked()
{
    widget_.showNormal();
}
/*!
 * \brief Handles the maximize button's 'clicked' signal.
 */
void TitleBar::onMaximizeButtonClicked()
{
    widget_.showMaximized();
}
/*!
 * \brief Handles the close button's 'clicked' signal.
 */
void TitleBar::onCloseButtonClicked()
{
    widget_.close();
}
