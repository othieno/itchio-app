#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include "database.h"

namespace itchio {

class Application;

class DatabaseManager final : public QObject
{
    friend class Application;
public:
    static Database createDatabase(const QString& fileName);

    static QString databaseCacheLocation();
private:
    explicit DatabaseManager(Application& application);
};

} // namespace itchio

#endif // DATABASEMANAGER_H
