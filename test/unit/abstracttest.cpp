#include "abstracttest.h"
#include "testsuite.h"
#include <iostream>

using itchio::AbstractTest;

AbstractTest::AbstractTest(TestSuite* const suite) :
QObject(suite)
{}
