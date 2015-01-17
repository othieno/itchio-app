#ifndef AUTHENTICATIONVIEW_H
#define AUTHENTICATIONVIEW_H

#include "abstractview.h"
#include "ui_loginprompt.h"

class QLabel;
class QLineEdit;
class QPushButton;
namespace Ui { class LoginPromptView; } // TODO Change LoginPromptView to AuthenticationView.

namespace itchio {

class Authenticator;
class ModalDialog;

class AuthenticationView Q_DECL_FINAL : public AbstractView
{
    Q_OBJECT
public:
    AuthenticationView(ModalDialog& dialog, Authenticator& authenticator);

    inline QString title() const Q_DECL_OVERRIDE { return "Login"; }
    inline bool isResizable() const Q_DECL_OVERRIDE { return false; }
    inline bool isCentered() const Q_DECL_OVERRIDE { return true; }
private:
    void disableInputComponents(const bool disable = true);

    QString username() const;
    QString password() const;

    void setStatusMessage(const QString& message) const;

    Ui::LoginPromptView ui_;
    Authenticator& authenticator_;
private slots:
    void onInputChanged();
    void onLoginButtonClicked();
    void onAuthenticationFailed(const QString& message);
};

} // namespace itchio

#endif // AUTHENTICATIONVIEW_H
