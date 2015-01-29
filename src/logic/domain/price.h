#ifndef PRICE_H
#define PRICE_H

#include <ostream>

class QJsonObject;

namespace itchio {

class Price
{
public:
    enum class Currency
    {
        USD,
        GBP,
        EUR,
    };

    Price(const int amount, const Currency& currency);
//    operator QString();

    const Currency& currency() const;
    void setCurrency(const Currency& currency);

    int amount() const;

    int whole() const;
    int cents() const;

    static Price fromJson(const QJsonObject& object);
private:
    int amount_;
    Currency currency_;
};

} // namespace itchio

std::ostream& operator<<(std::ostream&, const itchio::Price&);
std::ostream& operator<<(std::ostream&, const itchio::Price::Currency&);

#endif // PRICE_H
