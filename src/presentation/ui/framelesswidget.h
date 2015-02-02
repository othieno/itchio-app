#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

#include "titlebar.h"

namespace itchio {

class Application;

template<class Widget, class WidgetUi>
class FramelessWidget : public Widget, protected WidgetUi
{
protected:
    FramelessWidget(Application& application, const QIcon& icon);

    virtual void initializeUi() = 0;

    void showEvent(QShowEvent* const event) override;
    void changeEvent(QEvent* const event) override;

    QLayout* titlebarLayout();

    void setupTitleBar(QLayout& layout);
    void setupSizeGrip(QLayout& layout);

    Application& application_;
    TitleBar titleBar_;
//TODO    SizeGrip sizeGrip_;
private:
    bool initializedUi_;
};

/*!
 * \brief Instantiates a FramelessWidget attached to the given \a application and with the specified window \a icon.
 */
template<class Widget, class WidgetUi>
FramelessWidget<Widget, WidgetUi>::FramelessWidget(Application& application, const QIcon& icon) :
application_(application),
titleBar_(*this),
initializedUi_(false)
{
    // Window flags to make the widget frameless. Note that when the widget is a QDialog,
    // an extra flag is needed to make it frameless.
    Qt::WindowFlags framelessWindowFlags = Qt::CustomizeWindowHint |  Qt::FramelessWindowHint;
    if (std::is_same<Widget, QDialog>::value)
        framelessWindowFlags |= Qt::Dialog;

    Widget::setWindowFlags(framelessWindowFlags);
    Widget::setWindowIcon(icon);
}
/*!
 * \brief Handles the show \a event.
 * This reimplementation initializes the widget's UI the first time it is displayed.
 */
template<class Widget, class WidgetUi>
void FramelessWidget<Widget, WidgetUi>::showEvent(QShowEvent* const event)
{
    if (!initializedUi_)
    {
        WidgetUi::setupUi(this);

        // Note that a layout named 'titleBarFrameLayout' must exist in the widget's UI.
        if (WidgetUi::titleBarFrameLayout != nullptr)
            setupTitleBar(*WidgetUi::titleBarFrameLayout);

//        auto* const sizeGripLayout_ = sizeGripLayout();
//        if (sizeGripLayout_ != nullptr)
//            setupSizeGrip(*sizeGripLayout_);

        initializeUi();
        initializedUi_ = true;
    }
    Widget::showEvent(event);
}
/*!
 * \brief Handles the change \a event.
 * This reimplementation handles the 'WindowIconChange', 'WindowTitleChange' and 'WindowStateChange' events.
 */
template<class Widget, class _>
void FramelessWidget<Widget, _>::changeEvent(QEvent* const event)
{
    switch (event->type())
    {
        case QEvent::WindowIconChange:
            titleBar_.onWindowIconChange(Widget::windowIcon());
            break;
        case QEvent::WindowTitleChange:
            titleBar_.onWindowTitleChange(Widget::windowTitle());
            break;
        case QEvent::WindowStateChange:
            titleBar_.onWindowStateChange(Widget::windowState());
            break;
        default:
            break;
    }
    Widget::changeEvent(event);
}
/*!
 * \brief Sets up the frameless widget's title bar.
 */
template<class Widget, class _>
void FramelessWidget<Widget, _>::setupTitleBar(QLayout& layout)
{
    // When showing a modal dialog, hide the minimize (modals cannot be minimized) and settings buttons.
    if (std::is_same<Widget, QDialog>::value)
    {
        titleBar_.showSettingsButton(false);
        titleBar_.showMinimizeButton(false);
    }

    layout.addWidget(&titleBar_);
}
/*!
 * \brief Sets up the frameless widget's size grip.
 */
template<class _, class __>
void FramelessWidget<_, __>::setupSizeGrip(QLayout&)
{
    //TODO Implement me.
}

} // namespace itchio

#endif // FRAMELESSWIDGET_H
