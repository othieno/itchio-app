#include "testsuite.h"

using namespace itchio;

int main(int argc, char** argv)
{
    return TestSuite().run<TestGameDAO,
                           TestGameDAO>(argc, argv);
}
