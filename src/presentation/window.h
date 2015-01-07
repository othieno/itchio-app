#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "modaldialog.h"

namespace itchio {

class Application;

class Window Q_DECL_FINAL : public QMainWindow
{
    friend class Application;
public:
    inline const Application& application() const { return application_; }

    inline ModalDialog& modalDialog(){ return modalDialog_; }
    inline const ModalDialog& modalDialog() const { return modalDialog_; }
private:
    explicit Window(Application& application);

    Application& application_;
    ModalDialog modalDialog_;
};

} // namespace itchio

#endif // WINDOW_H
