#include "titlebar.h"
#include "ui_titlebar.h"

//FIXME There is a bug when the window snaps to the desktop. The resize buttons should change
//      state but this doesn't happen.

using itchio::Titlebar;

/*
 * Instantiates a Titlebar with the specified \a parent.
 */
Titlebar::Titlebar(QWidget& parent) :
QWidget(&parent),
parent_(parent),
ui_(new Ui::Titlebar),
showResizeButtons_(true),
showUnmaximizeButton_(false),
showMaximizeButton_(false)
{
    Q_ASSERT(ui_ != nullptr);
    ui_->setupUi(this);

    connect(ui_->minimizeButton,   &QPushButton::clicked, &parent_, &QWidget::showMinimized);
    connect(ui_->unmaximizeButton, &QPushButton::clicked, [this](){ parent_.showNormal(); });
    connect(ui_->maximizeButton,   &QPushButton::clicked, [this](){ parent_.showMaximized(); });
    connect(ui_->closeButton,      &QPushButton::clicked, &parent_, &QWidget::close);

    onWindowStateChanged();
}
/*
 * Destroys the Titlebar instance.
 */
Titlebar::~Titlebar()
{
    delete ui_;
}
/*
 * Sets the both the titlebar and parent window's \a title.
 */
void Titlebar::setTitle(const QString& title)
{
    ui_->title->setText(title);
    parent_.setWindowTitle(title);
}
/*
 * Sets the both the titlebar and parent window's \a title.
 */
void Titlebar::onWindowStateChanged()
{
    showUnmaximizeButton_ = parent_.windowState().testFlag(Qt::WindowMaximized);
    showMaximizeButton_ = !showUnmaximizeButton_;

    ui_->unmaximizeButton->setVisible(showResizeButtons_ && showUnmaximizeButton_);
    ui_->maximizeButton->setVisible(showResizeButtons_ && showMaximizeButton_);
}
/*!
 * \brief Returns a pointer to the settings button.
 */
QPushButton* Titlebar::settingsButton() const
{
    return ui_->settingsButton;
}
/*
 * Shows the settings button if \a show is set to true, hides it otherwise.
 */
void Titlebar::showSettingsButton(const bool show)
{
    ui_->settingsButton->setVisible(show);
}
/*
 * Shows the minimize button if \a show is set to true, hides it otherwise.
 */
void Titlebar::showMinimizeButton(const bool show)
{
    ui_->minimizeButton->setVisible(show);
}
/*
 * Shows the resize buttons if \a show is set to true, hides them otherwise.
 */
void Titlebar::showResizeButtons(const bool show)
{
    showResizeButtons_ = show;
    onWindowStateChanged();
}
