#ifndef TESTGAMEDAO_H
#define TESTGAMEDAO_H

#include "abstracttest.h"

namespace itchio {

class TestGameDAO : public AbstractTest
{
    Q_OBJECT

public:
    explicit TestGameDAO(TestSuite* const suite);

private slots:
    void testAdd();
};

} // namespace itchio

#endif // TESTGAMEDAO_H
