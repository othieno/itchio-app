//TODO Remove this.
#ifdef DEPRECATED

#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>

namespace itchio {

class Application;

//TODO Remove this class. It is a code smell.
class Manager : public QObject
{
public:
    const Application& application() const;
protected:
    explicit Manager(Application& application);

    Application& application_;
};

} // namespace itchio

#endif // MANAGER_H

#endif
