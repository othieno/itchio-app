#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "framelesswidget.h"
#include "ui_window.h"

namespace itchio {

class AbstractView;

class Window final : public FramelessWidget<QMainWindow, Ui::Window>
{
    friend class Application;
private:
    explicit Window(Application& application);

    void initializeUi() override;
    void initializeContentViews();
    void initializeSystemTrayIcon();

    void closeEvent(QCloseEvent* const event) override;

    QSystemTrayIcon systemTrayIcon_;
private slots:
    void onViewChanged(AbstractView& view);
};

} // namespace itchio

#endif // WINDOW_H
