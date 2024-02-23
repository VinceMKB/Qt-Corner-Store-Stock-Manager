#include "stockfactory.h"
#include "confectionery.h"
#include "readingmaterial.h"

Stock* StockFactory::createStock(const QString& itemType, const QString& item, int quantity, int weight, const QString& frequency)
{
    if (itemType == "Confectionery")
    {
        return new Confectionery(item, quantity, weight);
    }
    else if (itemType == "ReadingMaterial")
    {
        return new ReadingMaterial(item, quantity, frequency);
    }

    return nullptr;
}
