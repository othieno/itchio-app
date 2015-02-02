#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QTimer>
#include "ui_titlebar.h"

namespace itchio {

class TitleBar final : public QWidget, private Ui::TitleBar
{
public:
    explicit TitleBar(QWidget& widget);

    QPushButton* settingsButton() const;

    void onWindowIconChange(const QIcon& icon);
    void onWindowTitleChange(const QString& title);
    void onWindowStateChange(const Qt::WindowStates& states);

    void showSettingsButton(const bool show = true);
    void showMinimizeButton(const bool show = true);
    void showResizeButtons(const bool show = true);
private:
    void mousePressEvent(QMouseEvent* const event) override;
    void mouseDoubleClickEvent(QMouseEvent* const event) override;
    void mouseReleaseEvent(QMouseEvent* const event) override;
    void mouseMoveEvent(QMouseEvent* const event) override;

    QWidget& widget_;
    bool widgetMovementToggled_;
    QPoint widgetInitialPosition_;
    QTimer widgetMovementDelayTimer_;

    bool showResizeButtons_;
    bool showUnmaximizeButton_;
    bool showMaximizeButton_;

    constexpr static int DELAY_TIMER_INTERVAL = 200;
private slots:
    void onMinimizeButtonClicked();
    void onUnmaximizeButtonClicked();
    void onMaximizeButtonClicked();
    void onCloseButtonClicked();
};

} // namespace itchio

#endif // TITLEBAR_H
