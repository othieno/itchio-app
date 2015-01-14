#ifndef USER_H
#define USER_H

#include <QString>

namespace itchio {

/**
 * A user profile.
 */
struct User
{
    unsigned int identifier;

    QString username;
    QString key;

    QString displayName;
};

} // namespace itchio

#endif // USER_H
