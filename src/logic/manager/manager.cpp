#ifdef DEPRECATED

#include "manager.h"
#include "application.h"

using itchio::Manager;
using itchio::Application;

/*!
 * \brief Instantiates a Manager that is attached to a parent \a application.
 */
Manager::Manager(Application& application) :
application_(application)
{}
/*!
 * \brief Returns a const-reference to the parent application.
 */
const Application& Manager::application() const
{
    return application_;
}
#endif
