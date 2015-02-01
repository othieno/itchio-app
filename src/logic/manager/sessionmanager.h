#ifdef TODO
#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "manager.h"

namespace itchio {

class Application;

class SessionManager : public Manager
{
    friend class Application;
public:
    void authenticate();
private:
    explicit SessionManager(Application& application);

    User user_;
signals:
    void authenticated(const User& user);
    void sessionOpened(const User& user);
    void sessionClosed();
};

} // namespace itchio

#endif // SESSIONMANAGER_H
#endif
