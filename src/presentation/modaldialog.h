#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <QDialog>

namespace Ui { class Window; } //TODO Change to 'namespace Ui { class ModalDialog; }'

namespace itchio {

class Application;
class Window;
class AbstractView;

class ModalDialog Q_DECL_FINAL : public QDialog
{
    friend class Window;
public:
    /*!
     * \brief An enumeration identifying all possible modal dialogs.
     */
    enum class Identifier
    {
        Authentication,
        Settings,
    };

    void setCentered(const bool centered);
    void setResizable(const bool resizable);
private:
    ModalDialog(const ModalDialog::Identifier& identifier, Application& application);
    ~ModalDialog();

    AbstractView* createDialogView(const ModalDialog::Identifier& identifier, Application& application);

    Ui::Window* const ui_;
};

} // namespace itchio

#endif // MODALDIALOG_H
