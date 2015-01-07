#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <QtTest>
#include "testgamedao.h"

namespace itchio {

struct TestSuite : public QObject
{
    template<class... Tests> int run(int& argc, char** argv)
    {
        int status = 0;
        for (AbstractTest* const test : {(new Tests(this))...})
        {
            status |= QTest::qExec(test, argc, argv);
            delete test;
        }
        return status;
    }
};

} // namespace itchio

#endif // TESTSUITE_H
