#ifndef AUTHENTICATIONVIEW_H
#define AUTHENTICATIONVIEW_H

#include "abstractview.h"
#include "ui_authenticationview.h"

namespace itchio {

class Application;
class Authenticator;
class ModalDialog;
class Settings;

class AuthenticationView Q_DECL_FINAL : public AbstractView
{
    Q_OBJECT
public:
    AuthenticationView(ModalDialog& dialog, Application& application);

    QString caption() const Q_DECL_OVERRIDE;
    inline bool isResizable() const Q_DECL_OVERRIDE { return false; }
    inline bool isCentered() const Q_DECL_OVERRIDE { return true; }
private:
    void disableInputComponents(const bool disable = true);

    QString username() const;
    QString password() const;

    void setStatusMessage(const QString& message) const;

    Ui::AuthenticationView ui_;
    Authenticator& authenticator_;
    const Settings& settings_;

    bool doApiKeyAuthentication_;
private slots:
    void onInputChanged();
    void onLoginButtonClicked();
    void onAuthenticationFailed(const QString& message);
};

} // namespace itchio

#endif // AUTHENTICATIONVIEW_H
