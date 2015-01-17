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

class Window Q_DECL_FINAL : public QMainWindow
{
    friend class Application;
public:
    bool openModalDialog(const ModalDialog::Identifier& identifier);
private:
    explicit Window(Application& application);
    ~Window();

    void initializeUserInterface();
    void initializeContentViews();
    void initializeSystemTrayIcon();

    void showEvent(QShowEvent* const event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent* const event) Q_DECL_OVERRIDE;

    Application& application_;
    Ui::Window* ui_;
    QSystemTrayIcon systemTrayIcon_;
private slots:
    void onViewChanged(AbstractView& view);
};

} // namespace itchio

#endif // WINDOW_H
