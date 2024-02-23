#ifndef STOCKFACTORY_H
#define STOCKFACTORY_H

#include <QString>
#include "stock.h"

class StockFactory
{
public:
    static Stock* createStock(const QString& itemType, const QString& item, int quantity, int weight, const QString& frequency);
};

#endif // STOCKFACTORY_H
