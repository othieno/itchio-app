#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <QDialog>
#include "ui_modaldialog.h"

namespace itchio {

class Application;
class Titlebar;

class ModalDialog Q_DECL_FINAL : public QDialog
{
public:
    /*!
     * \brief An enumeration identifying all possible modal dialog views.
     */
    enum class View
    {
        Authentication,
        Settings,
    };

    static bool open(const View& view, Application& application, const QVariant& args = QVariant());

    void setCentered();
    void setResizable(const bool resizable);
private:
    ModalDialog(const ModalDialog::View& view, Application& application, const QVariant& args);

    void setView(const ModalDialog::View& view, Application& application, const QVariant& args);
    void changeEvent(QEvent* const event) Q_DECL_OVERRIDE;

    Ui::ModalDialog ui_;
    Titlebar* const titlebar_;
};

} // namespace itchio

#endif // MODALDIALOG_H
