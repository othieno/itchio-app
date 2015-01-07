#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "abstractmanager.h"
#include "user.h"
#include <QTimer>

namespace itchio {

class ContentManager Q_DECL_FINAL : public AbstractManager
{
    Q_OBJECT

public:
    explicit ContentManager(Application& application);

    void showUserContent(const User& user);

public slots:
    void onUserDisconnected();

private:
    QString databaseLocation() const;
    QString cacheDataLocation() const;


    void createUserSession();
    void closeUserSession();

    User currentUser_;

signals:
    void sessionCreated(const User& user);
    void sessionClosed();
};

/*
class Window;
using Library = int;

class Curator Q_DECL_FINAL : public QObject
{
    Q_OBJECT
    friend class Application;
public:
    inline const Library& library() const { return library_; }

    inline int autoUpdateInterval() const { return autoUpdateTimer_.interval(); }
    inline void setAutoUpdateInterval(const int milliseconds){ autoUpdateTimer_.setInterval(milliseconds); }
public slots:
    void refresh();
private:
    explicit Curator(Application& application);

    Window& window_;
    User user_;
    Library library_;
    QTimer autoUpdateTimer_;
signals:
    void disconnected();
    void refreshed();
    void libraryUpdated();
};
*/

} // namespace itchio

#endif // CONTENTMANAGER_H
