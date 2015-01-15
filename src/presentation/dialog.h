#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "dialogviewtype.h"

namespace Ui { class Window; } //TODO Change to 'namespace Ui { class Dialog; }'

namespace itchio {

class Application;
class Window;
class AbstractView;

class Dialog Q_DECL_FINAL : public QDialog
{
    friend class Window;
public:
    void setCentered(const bool centered);
    void setResizable(const bool resizable);
private:
    Dialog(const DialogViewType& type, Application& application);
    ~Dialog();

    AbstractView* createDialogView(const DialogViewType& type, Application& application);

    Ui::Window* const ui_;
};

} // namespace itchio

#endif // DIALOG_H
