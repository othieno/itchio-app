#ifndef LOGINPROMPT_H
#define LOGINPROMPT_H

#include "abstractview.h"
#include "ui_loginwidget.h"
#include "authenticator.h"
#include "window.h"
#include <QGridLayout>

namespace itchio {

class LoginPrompt Q_DECL_FINAL : public AbstractView<Ui::LoginWidget, QGridLayout, Authenticator>
{
    Q_OBJECT
public:
    LoginPrompt(Authenticator& authenticator, ModalDialog& modalDialog);
private:
    void printMessage(const QString&);

    QPushButton* const loginButton_;
    QLineEdit* const usernameInput_;
    QLineEdit* const passwordInput_;
    QLabel* const statusLabel_;
private slots:
    void onInputChanged();
    void onLoginButtonClicked();
    void onAuthenticationFailed(const QString& message);
};

} // namespace itchio

#endif // LOGINPROMPT_H
