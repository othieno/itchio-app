#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <QDialog>
#include "framelesswidget.h"
#include "ui_modaldialog.h"

namespace itchio {

class ModalDialog final : public FramelessWidget<QDialog, Ui::ModalDialog>
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
    void setCentered();
    void setResizable(const bool resizable);

    static bool open(const View& view, Application& application, const QVariant& args = QVariant());
private:
    ModalDialog(const ModalDialog::View& view, Application& application, const QVariant& args);

    void initializeUi() override;
    void setView(const ModalDialog::View& view, Application& application, const QVariant& args);

    const View view_;
    const QVariant viewArguments_;
};

} // namespace itchio

#endif // MODALDIALOG_H
