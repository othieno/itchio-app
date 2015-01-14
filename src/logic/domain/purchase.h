#ifndef PURCHASE_H
#define PURCHASE_H

#include <QString>
#include <QDateTime>
#include "price.h"

namespace itchio {

class Purchase
{
public:
    unsigned int identifier;
    unsigned int gameIdentifier;

    QString      email;
    QString      source;

    QDateTime    when;

    bool         donation;
    Price        price;
    unsigned int saleRate;
};

} // namespace itchio

#endif // PURCHASE_H
