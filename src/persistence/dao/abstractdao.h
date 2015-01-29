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
     * Creates the database tables used by this data access object.
     */
    virtual void createTables() = 0;
    /*!
     * Drops all database tables used by this data access object.
     */
    virtual void dropTables() = 0;
    /*!
     * Populates the database with mock data.
     */
    virtual void insertMockRecords() = 0;
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
    explicit AbstractDAO(Database& database) :
    database_(database)
    {}
    /*!
     * The database to query.
     */
    Database& database_;
};

} // namespace itchio

#endif // ABSTRACTDAO_H
