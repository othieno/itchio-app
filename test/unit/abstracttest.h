#ifndef ABSTRACTTEST_H
#define ABSTRACTTEST_H

#include <QObject>

namespace itchio {

class TestSuite;

class AbstractTest : public QObject
{
protected:
    explicit AbstractTest(TestSuite* const suite);
};

} // namespace itchio

#endif // ABSTRACTTEST_H
