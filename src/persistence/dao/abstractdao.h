#ifndef ABSTRACTDAO_H
#define ABSTRACTDAO_H

#include <QHash>

namespace itchio {

class DatabaseManager;

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
     * Removes the entry with the specified \a identifier from the database.
     */
    virtual void remove(const Identifier& identifier) = 0;
    /*!
     * Removes the specified \a entry from the database.
     */
    virtual void remove(const Entry& entry) = 0;

protected:
    /*!
     * Instantiates an abstract data access object (DAO) that interfaces with the
     * specified database \a manager.
     */
    explicit AbstractDAO(DatabaseManager& manager) :
    databaseManager_(manager)
    {}
    /*!
     * A reference to the manager that interfaces with the underlying database.
     */
    DatabaseManager& databaseManager_;

    /*!
     * A mock database.
     * TODO Remove this when the database implementation is complete.
     */
    QHash<Identifier, Entry> database_;
};

} // namespace itchio

#endif // ABSTRACTDAO_H
