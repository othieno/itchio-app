#include "application.h"

int main(int argc, char** argv)
{
    int status = 0;
    do
    {
        status = itchio::Application(argc, argv).exec();
    } while (status == itchio::Application::RESTART_ON_EXIT_CODE);
    return status;
}
