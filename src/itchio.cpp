#include "application.h"

int main(int argc, char** argv)
{
    // The following properties must be set before the application is instantiated.
    QCoreApplication::setOrganizationDomain("itch.io");
    QCoreApplication::setOrganizationName("itch.io");
    QCoreApplication::setApplicationVersion("0.0");
    QCoreApplication::setApplicationName("itch");

    int status = 0;
    do
    {
        // Make sure we have access to a directory where application data can be stored.
        if (!itchio::Application::createDataDirectories())
            qFatal("FATAL: Could not create the application's data directories.");

        status = itchio::Application(argc, argv).exec();
    } while (status == itchio::Application::RESTART_ON_EXIT_CODE);

    return status;
}
