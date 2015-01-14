#include "database.h"

using itchio::Database;

/*!
 * \brief The type of database to use.
 */
constexpr static const char* const DATABASE_TYPE = "QSQLITE";
/*!
 * \brief Instantiates an empty, invalid database.
 */
Database::Database() :
QSqlDatabase(DATABASE_TYPE)
{}
/*!
 * \brief Instantiates a database with the specified \a name.
 */
Database::Database(const QString& name) :
Database()
{
    setDatabaseName(name);
}
