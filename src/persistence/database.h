#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

namespace itchio {

class DatabaseManager;

class Database : public QSqlDatabase
{
    friend class DatabaseManager;
public:
    Database();
private:
    explicit Database(const QString& name);
};

} // namespace itchio

#endif // DATABASE_H
