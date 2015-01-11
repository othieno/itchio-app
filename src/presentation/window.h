#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "view.h"

namespace itchio {

class Application;
class ModalWindow;

class Window Q_DECL_FINAL : public QMainWindow
{
    friend class Application;

public:
    View::Identifier viewIdentifier() const;
    void setView(const View::Identifier& view);

    int openModalWindow(const View::Identifier& view, const Qt::WindowModality modality = Qt::WindowModal);

private:
    explicit Window(Application& application);

    Application& application_;
};

} // namespace itchio

#endif // WINDOW_H
