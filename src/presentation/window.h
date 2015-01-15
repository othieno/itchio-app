#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "dialogviewtype.h"

namespace Ui { class Window; }

namespace itchio {

class Application;
class ContentView;

class Window Q_DECL_FINAL : public QMainWindow
{
    friend class Application;
public:
    bool openDialog(const DialogViewType& type);
private:
    explicit Window(Application& application);
    ~Window();

    void showEvent(QShowEvent* const event) Q_DECL_OVERRIDE;

    Application& application_;
    Ui::Window* ui_;
    ContentView* contentView_;
};

} // namespace itchio

#endif // WINDOW_H
