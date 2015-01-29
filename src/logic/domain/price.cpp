#include "price.h"
#include <QJsonObject>

using itchio::Price;

/*!
 * \brief Instantiates a Price object with the specified \a amount and \a currency.
 */
Price::Price(const int amount, const Currency& currency) :
amount_(amount),
currency_(currency)
{}
/*!
 * \brief Converts the JSON \a object into a Price object.
 */
Price Price::fromJson(const QJsonObject& object)
{
    const auto& stringToCurrency = [](const QString& currencyString)
    {
        //TODO Implement me.

        Q_UNUSED(currencyString);
        return Currency::USD;
    };
    return Price(object["amount"].toInt(), stringToCurrency(object["currency"].toString()));
}
