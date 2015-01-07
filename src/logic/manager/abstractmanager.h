#ifndef ABSTRACTMANAGER_H
#define ABSTRACTMANAGER_H

#include <QObject>

namespace itchio {

class Application;

class AbstractManager : public QObject
{
public:
    Application& application();
    const Application& application() const;
protected:
    explicit AbstractManager(Application& application);

    Application& application_;
};

} // namespace itchio

#endif // ABSTRACTMANAGER_H
