#include "databasemanager.h"
#include "database.h"
#include "application.h"
#include <QSqlError>
#include <QDir>

using itchio::DatabaseManager;
using itchio::Database;

/*!
 * \brief Instantiates a DatabaseManager attached to an \a application.
 */
DatabaseManager::DatabaseManager(Application& application) :
Manager(application)
{}
/*!
 * \brief Creates and opens the database with the specified \a name.
 * If the database already exists, then it is only opened for use. If creation failed,
 * then an invalid database instance is returned.
 */
Database DatabaseManager::createDatabase(const QString& name)
{
    Database database(QString("%1/%2").arg(databaseLocation(), name));
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
 * \brief Creates a temporary database in memory.
 */
Database DatabaseManager::createInMemoryDatabase()
{
    Database database(":memory:");
    if (!database.open())
    {
        const char* const error = qPrintable(database.lastError().databaseText());
        qWarning("[DatabaseManager] WARN: Could not open in-memory database: '%s'.", error);

        database = Database();
    }
    return database;
}
/*!
 * \brief Returns the location to the directory where all databases are stored.
 */
QString DatabaseManager::databaseLocation()
{
    return Application::dataLocation().append("/db");
}
