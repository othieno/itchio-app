#ifndef AUTHENTICATIONVIEW_H
#define AUTHENTICATIONVIEW_H

#include "abstractview.h"
#include "ui_authenticationview.h"
#include <QRegExpValidator>

namespace itchio {

class ModalDialog;
class Application;
class SessionManager;
class Settings;

class AuthenticationView final : public AbstractView
{
    Q_OBJECT
    friend class ModalDialog;
public:

    inline bool isResizable() const override { return false; }
    inline bool isCentered() const override { return true; }
private:
    AuthenticationView(ModalDialog& dialog, Application& application);
    void disableInputComponents(const bool disable = true);

    QString username() const;
    QString password() const;

    void setStatusMessage(const QString& message) const;

    Ui::AuthenticationView ui_;
    SessionManager& sessionManager_;
    const Settings& settings_;
    const QRegExpValidator usernameValidator_;
    bool enableApiKeyAuthentication_;
private slots:
    void onInputChanged();
    void onAuthenticateButtonClicked();
    void onUserAuthenticationFailed(const QString& message);
};

} // namespace itchio

#endif // AUTHENTICATIONVIEW_H
