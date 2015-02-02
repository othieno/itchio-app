#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "settings.h"
#include "window.h"
#include "databasemanager.h"
#include "networkmanager.h"
#include "sessionmanager.h"
#include "contentmanager.h"

namespace itchio {

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int& argc, char** argv);

    Settings& settings();
    const Settings& settings() const;

    void showWindow();

    DatabaseManager& databaseManager();
    const DatabaseManager& databaseManager() const;

    NetworkManager& networkManager();
    const NetworkManager& networkManager() const;

    SessionManager& sessionManager();
    const SessionManager& sessionManager() const;

    ContentManager& contentManager();
    const ContentManager& contentManager() const;

    QString userAgent() const;

    static QString dataLocation();
    static bool createDataDirectories();

    static constexpr int RESTART_ON_EXIT_CODE = 0x49544348; // 0x49544348 = 'ITCH' (ASCII 8).
public slots:
    void restart();
private:
    void setApplicationStyle();

    Settings settings_;

    Window window_;

    DatabaseManager databaseManager_;
    NetworkManager networkManager_;
    SessionManager sessionManager_;
    ContentManager contentManager_;
private slots:
    void onUserSessionOpened(const User& user);
    void onAboutToQuit();
};

} // namespace itchio

#endif // APPLICATION_H
