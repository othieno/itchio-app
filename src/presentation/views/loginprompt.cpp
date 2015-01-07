#include "loginprompt.h"

using itchio::LoginPrompt;

LoginPrompt::LoginPrompt(Authenticator& controller, ModalDialog& modalDialog) :
AbstractView(controller, modalDialog),
loginButton_(ui_->loginButton),
usernameInput_(ui_->loginUsernameInput),
passwordInput_(ui_->loginPasswordInput),
statusLabel_(ui_->loginStatusLabel)
{
    connect(loginButton_,   &QPushButton::clicked,   this, &LoginPrompt::onLoginButtonClicked);
    connect(usernameInput_, &QLineEdit::textChanged, this, &LoginPrompt::onInputChanged);
    connect(passwordInput_, &QLineEdit::textChanged, this, &LoginPrompt::onInputChanged);
    connect(&controller_,   &Authenticator::authenticationFailed, this, &LoginPrompt::onAuthenticationFailed);

    // Disable the login button. It is only enabled if the input is valid.
    loginButton_->setEnabled(false);

    modalDialog.setWindowTitle(fullViewTitle("Login"));
    modalDialog.setResizable(false);
    modalDialog.center();






//    modal.setupSizeGrip();
//    modal.onWidgetChange(*this);
//    modal.sizeGrip->hide();
}

void LoginPrompt::printMessage(const QString& message)
{
    statusLabel_->setText(message);
}

void LoginPrompt::onInputChanged()
{
    const auto& username = usernameInput_->text();
    const auto& password = passwordInput_->text();

    //TODO Perform a more thorough validation.
    bool isValidInput = username != "" && password != "";

    loginButton_->setEnabled(isValidInput);
}

void LoginPrompt::onLoginButtonClicked()
{
    printMessage("Logging in...");

    // Disable input fields to prevent any interruptions during the connection.
    for (auto* const input : std::initializer_list<QWidget*>({loginButton_, usernameInput_, passwordInput_}))
        input->setEnabled(false);

    controller_.authenticate(usernameInput_->text(), passwordInput_->text());
}

void LoginPrompt::onAuthenticationFailed(const QString& message)
{
    printMessage(message);

    // Re-enable input fields.
    for (auto* const input : std::initializer_list<QWidget*>({loginButton_, usernameInput_, passwordInput_}))
        input->setEnabled(true);
}
