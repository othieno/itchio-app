#include "authenticationview.h"
#include "modaldialog.h"
#include "application.h"

using itchio::AuthenticationView;

AuthenticationView::AuthenticationView(ModalDialog& dialog, Application& application) :
AbstractView(dialog),
sessionManager_(application.sessionManager()),
settings_(application.settings()),
usernameValidator_(/*QRegExp("")*/), //TODO Find the regular expression that accepts a valid username.
enableApiKeyAuthentication_(false)
{
    ui_.setupUi(this);
    ui_.usernameInput->setValidator(&usernameValidator_);

    //TODO Implement this.
    ui_.rememberUserButton->hide();

    connect(ui_.authenticateButton, &QPushButton::clicked, this, &AuthenticationView::onAuthenticateButtonClicked);
    connect(&sessionManager_, &SessionManager::userAuthenticated, &dialog, &ModalDialog::accept);
    connect(&sessionManager_, &SessionManager::userAuthenticationFailed, this, &AuthenticationView::onUserAuthenticationFailed);

    // If user credentials were previously saved and are still valid, use them.
    auto savedUsername = settings_.username();
    auto savedUsernameLength = savedUsername.length();

    enableApiKeyAuthentication_ =
    settings_.autoLogin() &&
    settings_.hasValidApiKey() &&
    savedUsernameLength > 0 &&
    usernameValidator_.validate(savedUsername, savedUsernameLength) == QValidator::Acceptable;

    if (enableApiKeyAuthentication_)
    {
        ui_.usernameInput->setText(savedUsername);
        ui_.passwordInput->setText("PasswordPlaceholder");

        setStatusMessage(tr("Enabled API key authentication"));
    }
    else
    {
        // Disable the authenticate button. It is only enabled if user input is valid.
        ui_.authenticateButton->setEnabled(false);
    }

    // Enable input handlers.
    // PS. This is done purposefully after determining whether or not to enable API key authentication
    // since the QLineEdit::setText emits the QLineEdit::textChanged signal, and QLineEdit::textEdited
    // is unfortunately not a solution.
    connect(ui_.usernameInput, &QLineEdit::textChanged, this, &AuthenticationView::onInputChanged);
    connect(ui_.passwordInput, &QLineEdit::textChanged, this, &AuthenticationView::onInputChanged);
}
/*!
 * \brief Disables the view's input components if \a disable is set to true.
 */
void AuthenticationView::disableInputComponents(const bool disable)
{
    const std::initializer_list<QWidget*>& widgets =
    {
        ui_.authenticateButton,
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
    if (enableApiKeyAuthentication_)
    {
        enableApiKeyAuthentication_ = false;
        ui_.usernameInput->setText(QString());
        ui_.passwordInput->setText(QString());

        setStatusMessage(tr("Disabled API key authentication."));
    }

    ui_.authenticateButton->setEnabled(!username().isEmpty() && !password().isEmpty());
}
/*!
 * \brief Authenticates user input when the authenticate button is pressed.
 */
void AuthenticationView::onAuthenticateButtonClicked()
{
    setStatusMessage(tr("Authenticating ..."));

    // Disable all input components to prevent any interference during the authentication phase.
    disableInputComponents();

    const auto& key = enableApiKeyAuthentication_ ? settings_.apiKey() : password();

    sessionManager_.authenticateUser(username(), key, enableApiKeyAuthentication_);
}
/*!
 * \brief Handles a user authentication failure.
 */
void AuthenticationView::onUserAuthenticationFailed(const QString& message)
{
    setStatusMessage(message);
    disableInputComponents(false);

    if (enableApiKeyAuthentication_)
    {
        enableApiKeyAuthentication_ = false;
        ui_.passwordInput->setText(QString());
    }
}
