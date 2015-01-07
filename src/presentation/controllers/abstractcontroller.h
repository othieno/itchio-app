#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include <QObject>

namespace itchio {

class Application;

class AbstractController : public QObject
{
public:
    inline const Application& application() const { return application_; }
    QString applicationName() const;
protected:
    explicit AbstractController(Application& application);

    Application& application_;
};

} // namespace itchio

#endif // ABSTRACTCONTROLLER_H
