#ifndef LOGINPROMPTVIEW_H
#define LOGINPROMPTVIEW_H

#include "view.h"
#include "ui_loginprompt.h"

namespace itchio {

class Authenticator;
class ModalWindow;

class LoginPromptView Q_DECL_FINAL : public View
{
    Q_OBJECT
public:
    LoginPromptView(Authenticator& authenticator, ModalWindow* const modalWindow);

    inline bool isResizable() const Q_DECL_OVERRIDE { return false; }
    inline bool isCentered() const Q_DECL_OVERRIDE { return true; }

private:
    inline QLineEdit* usernameInput() const { return ui_.usernameInput; }
    inline QLineEdit* passwordInput() const { return ui_.passwordInput; }
    inline QPushButton* loginButton() const { return ui_.loginButton; }
    inline QLabel*      statusLabel() const { return ui_.loginStatus; }

    inline QString username() const { return usernameInput()->text(); }
    inline QString password() const { return passwordInput()->text(); }

    inline void printStatusMessage(const QString& message) const { statusLabel()->setText(message); }

    Ui::LoginPromptView ui_;
    Authenticator& authenticator_;
private slots:
    void onInputChanged();
    void onLoginButtonClicked();
    void onAuthenticationFailed(const QString& message);
};

} // namespace itchio

#endif // LOGINPROMPTVIEW_H
