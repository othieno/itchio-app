#include "application.h"
#include "modaldialog.h"

int main(int argc, char** argv)
{
    // The following properties must be set before the application is instantiated.
    QCoreApplication::setOrganizationDomain("itch.io");
    QCoreApplication::setOrganizationName("itch.io");
    QCoreApplication::setApplicationName("itch.io");
    QCoreApplication::setApplicationVersion("0.0");

    do
    {
        // Make sure we have access to a directory where application data can be stored.
        if (!itchio::Application::createDataDirectories())
            qFatal("FATAL: Could not create the application's data directories.");

        itchio::Application application(argc, argv);

        // If the authentication dialog is rejected, the user explicitly closed the
        // authentication window. The application should gracefully exit.
        if (!itchio::ModalDialog::open(itchio::ModalDialog::View::Authentication, application))
            return 0;

        application.showWindow();

        const int status = application.exec();
        if (status != itchio::Application::RESTART_ON_EXIT_CODE)
            return status;

    } while (true);
}
