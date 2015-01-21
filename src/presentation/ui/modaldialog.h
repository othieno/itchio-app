#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <QDialog>

namespace Ui { class ModalDialog; }

namespace itchio {

class Application;
class Window;
class Titlebar;
class AbstractView;

class ModalDialog Q_DECL_FINAL : public QDialog
{
    friend class Window;
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
private:
    ModalDialog(const ModalDialog::View& view, Application& application);
    ~ModalDialog();

    void setView(const ModalDialog::View& view, Application& application);
    void changeEvent(QEvent* const event) Q_DECL_OVERRIDE;

    Ui::ModalDialog* const ui_;
    Titlebar* const titlebar_;
};

} // namespace itchio

#endif // MODALDIALOG_H
