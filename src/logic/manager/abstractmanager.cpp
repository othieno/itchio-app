#include "abstractmanager.h"
#include "application.h"

using itchio::AbstractManager;
using itchio::Application;

/*!
 * \brief Instantiates an AbstractManager that is attached to a parent \a application.
 */
AbstractManager::AbstractManager(Application& application) :
application_(application)
{}
/*!
 * \brief Returns a reference to the parent application.
 */
Application& AbstractManager::application()
{
    return application_;
}
/*!
 * \brief Returns a const-reference to the parent application.
 */
const Application& AbstractManager::application() const
{
    return application_;
}
