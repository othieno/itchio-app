#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "settings.h"
#include "window.h"
#include "networkmanager.h"
#include "authenticator.h"
#include "contentmanager.h"

namespace itchio {

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int& argc, char** argv);

    Settings& settings();
    const Settings& settings() const;

    Window& window();
    const Window& window() const;

    NetworkManager& networkManager();
    const NetworkManager& networkManager() const;

    Authenticator& authenticator();
    const Authenticator& authenticator() const;

    ContentManager& contentManager();
    const ContentManager& contentManager() const;

    QString dataLocation() const;

    constexpr static unsigned int RESTART_ON_EXIT_CODE = 0x49544348; // 0x49544348 = 'ITCH' (ASCII 8).
private:
    QString settingsFileLocation() const;

    void setApplicationStyleSheet();

    Settings settings_;

    Window window_;

    NetworkManager networkManager_;
    Authenticator authenticator_;
    ContentManager contentManager_;
private slots:
    void onNetworkManagerInitialized();
    void onUserAuthenticated(const User& user);
    void onUserSessionClosed();
    void onRestart();
};

} // namespace itchio

#endif // APPLICATION_H
