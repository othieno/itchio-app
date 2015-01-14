#ifndef ABSTRACTDAO_H
#define ABSTRACTDAO_H

#include <QList>

class QSqlQuery;

namespace itchio {

class Database;

template<class Entry, class Identifier>
class AbstractDAO
{
public:
    /*!
     * Adds the \a entry to the database if it doesn't exist, or updates it otherwise.
     */
    virtual void save(const Entry& entry) = 0;
    /*!
     * Returns the entry with the specified unique \a identifier in the database.
     */
    virtual Entry get(const Identifier& identifier) const = 0;
    /*!
     * Returns all stored entries .
     */
    virtual QList<Entry> getAll() const = 0;
    /*!
     * Removes the entry with the specified \a identifier (primary key) from the database.
     */
    virtual void remove(const Identifier& identifier) = 0;
protected:
    /*!
     * Instantiates an abstract data access object that interacts with the specified \a database.
     */
    explicit AbstractDAO(Database* const database) :
    database_(database)
    {
        Q_ASSERT(database_ != nullptr);
    }
    /*!
     * Creates the database tables used by this data access object.
     */
    virtual void createTables() = 0;
    /*!
     * Drops all the database tables used by this data access object.
     */
    virtual void dropTables() = 0;
    /*!
     * Populates the database.
     */
    virtual void populateTables() = 0;
    /*!
     * Converts the result of an SQL query into the Entry type.
     */
    virtual Entry toDomainObject(const QSqlQuery& query) const = 0;
    /*!
     * The database to query.
     */
    Database* const database_;
};

} // namespace itchio

#endif // ABSTRACTDAO_H
