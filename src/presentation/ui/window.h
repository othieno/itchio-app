#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "modaldialog.h"

class QSystemTrayIcon;
namespace Ui { class Window; }

namespace itchio {

class Application;
class AbstractView;
class Titlebar;

class Window Q_DECL_FINAL : public QMainWindow
{
    friend class Application;
public:
    bool openModalDialog(const ModalDialog::View& view);
private:
    explicit Window(Application& application);
    ~Window();

    void initializeUserInterface();
    void initializeContentViews();
    void initializeSystemTrayIcon();

    void changeEvent(QEvent* const event) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent* const event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent* const event) Q_DECL_OVERRIDE;

    Application& application_;

    Ui::Window* ui_;
    Titlebar* titlebar_;
    QSystemTrayIcon systemTrayIcon_;
private slots:
    void onViewChanged(AbstractView& view);
};

} // namespace itchio

#endif // WINDOW_H
