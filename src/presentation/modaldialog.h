#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <QDialog>

namespace itchio {

class Window;

class ModalDialog Q_DECL_FINAL : public QDialog
{
    friend class Window;
public:
    void center();
    void setResizable(const bool resizable = true);
private:
    explicit ModalDialog(Window* const parent);
};

} // namespace itchio

#endif // MODALDIALOG_H
