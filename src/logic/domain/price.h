#ifndef PRICE_H
#define PRICE_H

#include <ostream>

namespace itchio {

struct Price
{
    enum class Currency
    {
        USD,
        GBP,
        EUR,
    };

    unsigned int whole; // TODO Find a better name for this, i.e. the part before the decimal.
    unsigned int cents; // TODO Find a better name for this, i.e. the part after the decimal.
    Currency currency;
};

} // namespace itchio

std::ostream& operator<<(std::ostream&, const itchio::Price&);
std::ostream& operator<<(std::ostream&, const itchio::Price::Currency&);

#endif // PRICE_H
