#ifndef MODALWINDOW_H
#define MODALWINDOW_H

#include <QDialog>
#include "view.h"
#include "ui_window.h"

namespace itchio {

class Window;

class ModalWindow Q_DECL_FINAL : public QDialog
{
    friend class Window;
public:
    void setCentered(const bool centered = true);
    void setResizable(const bool resizable = true);

private:
     ModalWindow(const Qt::WindowModality modality, Application& application, const View::Identifier& identifier);

     View* createModalView(const View::Identifier& identifier, Application& application);

     Ui::Window ui_;
};

} // namespace itchio

#endif // MODALWINDOW_H
