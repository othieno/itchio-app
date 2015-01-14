#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "manager.h"
#include "user.h"
#include "database.h"
#include <QTimer>

namespace itchio {

class GameDAO;

class ContentManager Q_DECL_FINAL : public Manager
{
    Q_OBJECT
public:
    explicit ContentManager(Application& application);

    const User& user() const;
    void setUser(const User& user);

    bool isAutoUpdateEnabled() const;
    void enableAutoUpdate(const bool enable = true);

    int autoUpdateInterval() const;
    void setAutoUpdateInterval(const int milliseconds);

    GameDAO& gameDAO();

    static QString cacheLocation();

    constexpr static int MINIMUM_AUTO_UPDATE_INTERVAL = 3  * 1000; // 3 seconds.
    constexpr static int DEFAULT_AUTO_UPDATE_INTERVAL = 60 * 1000; // 1 minute
public slots:
    void updateUserContent();
    void emptyCache();

private:
    QTimer autoUpdateTimer_;
    User user_;

    Database userDatabase_;
signals:
    void userContentUpdated();
    void cacheEmptied();
};

} // namespace itchio

#endif // CONTENTMANAGER_H
