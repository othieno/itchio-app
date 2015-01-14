#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "manager.h"
#include "database.h"

namespace itchio {

class DatabaseManager : public Manager
{
    friend class Application;
public:
    static Database createDatabase(const QString& name);
    static Database createInMemoryDatabase();

    static QString databaseLocation();
private:
    explicit DatabaseManager(Application& application);
};

} // namespace itchio

#endif // DATABASEMANAGER_H
