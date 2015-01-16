#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "modaldialog.h"

class QSystemTrayIcon;
namespace Ui { class Window; }

namespace itchio {

class Application;
class CatalogView;
class LibraryView;

class Window Q_DECL_FINAL : public QMainWindow
{
    friend class Application;
public:
    bool openModalDialog(const ModalDialog::Identifier& identifier);
private:
    explicit Window(Application& application);
    ~Window();

    void showEvent(QShowEvent* const event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent* const event) Q_DECL_OVERRIDE;

    Application& application_;
    Ui::Window* ui_;

    CatalogView* catalogView_;
    LibraryView* libraryView_;

    QSystemTrayIcon* systemTrayIcon_;
};

} // namespace itchio

#endif // WINDOW_H
