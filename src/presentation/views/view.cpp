#include "view.h"
#include "application.h"

using itchio::View;

/*!
 * \brief Instantiates a View with the given \a identifier that is a child to the given \a parent.
 */
View::View(const View::Identifier& identifier, QWidget* const parent) :
QWidget(parent),
identifier_(identifier)
{}
/*!
 * \brief Returns the identifier assigned to this view.
 */
const View::Identifier& View::identifier() const
{
    return identifier_;
}
/*!
 * \brief Returns the view's title.
 */
QString View::title() const
{
    //TODO Complete me.
    switch (identifier_)
    {
        case Identifier::None:
            return QString();
        case Identifier::LoginPrompt:
            return "Login";
        default:
            return "[View::title] Implement me.";
    }
}
