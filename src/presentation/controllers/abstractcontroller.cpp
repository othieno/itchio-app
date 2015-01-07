#include "abstractcontroller.h"
#include "application.h"

using itchio::AbstractController;

AbstractController::AbstractController(Application& application) :
application_(application)
{}

QString AbstractController::applicationName() const
{
    return application_.applicationName();
}
