#include "authenticationview.h"
#include "modaldialog.h"
#include "application.h"

using itchio::AuthenticationView;

AuthenticationView::AuthenticationView(ModalDialog& dialog, Application& application) :
AbstractView(dialog),
authenticator_(application.authenticator()),
settings_(application.settings()),
doApiKeyAuthentication_(false)
{
    ui_.setupUi(this);


    //TODO Refactor these.
    ui_.changeUserButton->hide();
    ui_.offlineLoginButton->hide();
    ui_.rememberUserCheckbox->hide();



    connect(ui_.loginButton,   &QPushButton::clicked,  this, &AuthenticationView::onLoginButtonClicked);
    connect(ui_.usernameInput, &QLineEdit::textEdited, this, &AuthenticationView::onInputChanged);
    connect(ui_.passwordInput, &QLineEdit::textEdited, this, &AuthenticationView::onInputChanged);

    connect(&authenticator_, &Authenticator::authenticated, &dialog, &ModalDialog::accept);
    connect(&authenticator_, &Authenticator::authenticationFailed, this, &AuthenticationView::onAuthenticationFailed);

    // Disable the login button. It is only enabled if user input is valid.
    ui_.loginButton->setEnabled(false);

    // If user credentials have been saved, use them.
    if (settings_.autoLogin() && settings_.username() != "" && settings_.hasValidApiKey())
    {
        doApiKeyAuthentication_ = true;

        ui_.usernameInput->setText(settings_.username());
        ui_.passwordInput->setText("PasswordPlaceholder");
        ui_.loginButton->setText("Authenticate API Key");
        ui_.loginButton->setEnabled(true);
    }
}
/*!
 * \brief Disables the view's input components if \a disable is set to true.
 */
void AuthenticationView::disableInputComponents(const bool disable)
{
    const std::initializer_list<QWidget*>& widgets =
    {
        ui_.loginButton,
        ui_.usernameInput,
        ui_.passwordInput
    };
    for (auto* const widget : widgets)
    {
        if (widget != nullptr)
            widget->setDisabled(disable);
    }
}
/*!
 * \brief Returns the current trimmed (no leading or trailing spaces) username.
 */
QString AuthenticationView::username() const
{
    return ui_.usernameInput->text().trimmed();
}
/*!
 * \brief Returns the current password.
 */
QString AuthenticationView::password() const
{
    return ui_.passwordInput->text();
}
/*!
 * \brief Sets the status \a message.
 */
void AuthenticationView::setStatusMessage(const QString& message) const
{
    return ui_.statusMessage->setText(message);
}
/*!
 * \brief Validates user input and enables/disables the login button depending on the correctness of said input.
 */
void AuthenticationView::onInputChanged()
{
    // If the user input changes, then it's likely a username/password pair that differs
    // from the saved one has been entered. Consequently, the saved API key is useless.
    if (doApiKeyAuthentication_)
    {
        doApiKeyAuthentication_ = false;
        ui_.loginButton->setText("Authenticate");
    }

    //TODO Perform a more thorough validation.
    bool isValidInput = username() != "" && password() != "";

    ui_.loginButton->setEnabled(isValidInput);
}
/*!
 * \brief Authenticates user input when the login button is pressed.
 */
void AuthenticationView::onLoginButtonClicked()
{
    setStatusMessage("Authenticating ...");

    // Disable all input components to prevent any interference during the authentication phase.
    disableInputComponents();

    const auto& key = doApiKeyAuthentication_ ? settings_.apiKey() : password();

    authenticator_.authenticate(username(), key, doApiKeyAuthentication_);
}
/*!
 * \brief Handles authentication failure.
 */
void AuthenticationView::onAuthenticationFailed(const QString& message)
{
    setStatusMessage(message);
    disableInputComponents(false);

    if (doApiKeyAuthentication_)
    {
        doApiKeyAuthentication_ = false;
        ui_.passwordInput->setText(QString());
        ui_.loginButton->setText("Authenticate");
        ui_.loginButton->setDisabled(true);
    }
}
