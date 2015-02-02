#include "databasemanager.h"
#include "database.h"
#include "application.h"
#include <QSqlError>

using itchio::DatabaseManager;
using itchio::Database;

/*!
 * \brief Instantiates a DatabaseManager attached to an \a application.
 */
DatabaseManager::DatabaseManager(Application& application)
{
    Q_UNUSED(application);
}
/*!
 * \brief Creates and opens the database with the specified \a name.
 * If the database already exists, then it is only opened for use. If creation fails,
 * an invalid database instance is returned.
 */
Database DatabaseManager::createDatabase(const QString& name)
{
    Database database(name);
    if (!database.open())
    {
        const char* const dbName = qPrintable(database.databaseName());
        const char* const error = qPrintable(database.lastError().databaseText());
        qWarning("[DatabaseManager] WARN: Could not open %s: '%s'.", dbName, error);

        return Database();
    }
    return database;
}
/*!
 * \brief Returns the location to the directory where all databases are stored.
 */
QString DatabaseManager::databaseCacheLocation()
{
    return Application::dataLocation().append("/db");
}
