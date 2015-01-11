#include "loginpromptview.h"
#include "authenticator.h"
#include "modalwindow.h"

using itchio::LoginPromptView;

LoginPromptView::LoginPromptView(Authenticator& authenticator, ModalWindow* const parent) :
View(View::Identifier::LoginPrompt, parent),
authenticator_(authenticator)
{
    ui_.setupUi(this);

    connect(loginButton(),   &QPushButton::clicked,   this, &LoginPromptView::onLoginButtonClicked);
    connect(usernameInput(), &QLineEdit::textChanged, this, &LoginPromptView::onInputChanged);
    connect(passwordInput(), &QLineEdit::textChanged, this, &LoginPromptView::onInputChanged);

    connect(&authenticator_, &Authenticator::authenticated, parent, &ModalWindow::accept);
    connect(&authenticator_, &Authenticator::authenticationFailed, this, &LoginPromptView::onAuthenticationFailed);

    // Disable the login button. It is only enabled if user input is valid.
    loginButton()->setEnabled(false);
}
/*!
 * \brief Validates user input and enables/disables the login button depending on the correctness of said input.
 */
void LoginPromptView::onInputChanged()
{
    //TODO Perform a more thorough validation.
    bool isValidInput = username() != "" && password() != "";

    loginButton()->setEnabled(isValidInput);
}
/*!
 * \brief Authenticates user input when the login button is pressed.
 */
void LoginPromptView::onLoginButtonClicked()
{
    printStatusMessage("Logging in...");

    // Disable all widgets to prevent any interruptions during the connection.
    for (auto* const widget : std::initializer_list<QWidget*>({loginButton(), usernameInput(), passwordInput()}))
        widget->setEnabled(false);

    authenticator_.authenticate(username(), password());
}
/*!
 * \brief Handles authentication failure.
 */
void LoginPromptView::onAuthenticationFailed(const QString& message)
{
    printStatusMessage(message);

    // Re-enable the widgets.
    for (auto* const widget : std::initializer_list<QWidget*>({loginButton(), usernameInput(), passwordInput()}))
        widget->setEnabled(true);
}
