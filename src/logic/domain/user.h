#ifndef USER_H
#define USER_H

#include <QString>

namespace itchio {

/**
 * A user profile.
 */
struct User
{
public:
    unsigned int identifier;

    QString username;
    QString key;



#ifdef TODO
public:
    inline unsigned int identifier() const { return identifier_; }
    inline const QString& username() const { return username_; }
    inline const QString& displayName() const { return !displayName_.isNull() ? displayName_ : username_; }
private:
    unsigned int identifier_;

    QString username_;
    QString displayName_;





    QString key;


    QString website_;
    QString twitter_;
    bool isDeveloper;
#endif
};

} // namespace itchio

#endif // USER_H
