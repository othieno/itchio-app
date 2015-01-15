#include "authenticationview.h"
#include "ui_loginprompt.h"
#include "authenticator.h"
#include "dialog.h"

using itchio::AuthenticationView;


AuthenticationView::AuthenticationView(Dialog* const parent, Authenticator& authenticator) :
AbstractView(parent),
ui_(new Ui::LoginPromptView),
authenticator_(authenticator)
{
    Q_ASSERT(ui_ != nullptr);
    ui_->setupUi(this);

    connect(ui_->loginButton,   &QPushButton::clicked,   this, &AuthenticationView::onLoginButtonClicked);
    connect(ui_->usernameInput, &QLineEdit::textChanged, this, &AuthenticationView::onInputChanged);
    connect(ui_->passwordInput, &QLineEdit::textChanged, this, &AuthenticationView::onInputChanged);

    connect(&authenticator_, &Authenticator::authenticated, parent, &Dialog::accept);
    connect(&authenticator_, &Authenticator::authenticationFailed, this, &AuthenticationView::onAuthenticationFailed);

    // Disable the login button. It is only enabled if user input is valid.
    ui_->loginButton->setEnabled(false);
}
/*!
 * \brief Destroys the AuthenticationView instance.
 */
AuthenticationView::~AuthenticationView()
{
    delete ui_;
}
/*!
 * \brief Disables the view's input components if \a disable is set to true.
 */
void AuthenticationView::disableInputComponents(const bool disable)
{
    const std::initializer_list<QWidget*>& widgets =
    {
        ui_->loginButton,
        ui_->usernameInput,
        ui_->passwordInput
    };
    for (auto* const widget : widgets)
    {
        if (widget != nullptr)
            widget->setDisabled(disable);
    }
}
/*!
 * \brief Returns the current username.
 */
QString AuthenticationView::username() const
{
    return ui_->usernameInput->text().trimmed();
}
/*!
 * \brief Returns the current password.
 */
QString AuthenticationView::password() const
{
    return ui_->passwordInput->text();
}
/*!
 * \brief Sets the status \a message.
 */
void AuthenticationView::setStatusMessage(const QString& message) const
{
    return ui_->loginStatus->setText(message);
}
/*!
 * \brief Validates user input and enables/disables the login button depending on the correctness of said input.
 */
void AuthenticationView::onInputChanged()
{
    //TODO Perform a more thorough validation.
    bool isValidInput = username() != "" && password() != "";

    ui_->loginButton->setEnabled(isValidInput);
}
/*!
 * \brief Authenticates user input when the login button is pressed.
 */
void AuthenticationView::onLoginButtonClicked()
{
    setStatusMessage("Logging in...");

    // Disable all input components to prevent any interference during the authentication phase.
    disableInputComponents();

    authenticator_.authenticate(username(), password());
}
/*!
 * \brief Handles authentication failure.
 */
void AuthenticationView::onAuthenticationFailed(const QString& message)
{
    setStatusMessage(message);
    disableInputComponents(false);
}
