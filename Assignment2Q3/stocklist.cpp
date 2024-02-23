#include "stocklist.h"
#include "confectionery.h"
#include "readingmaterial.h"

StockList* StockList::m_instance = nullptr;

StockList* StockList::instance()
{
    if (!m_instance)
        m_instance = new StockList();
    return m_instance;
}

void StockList::addStock(Stock* stock)
{
    QMetaObject::invokeMethod(this, [this, stock]() {
        if (dynamic_cast<Confectionery*>(stock))
            m_confectioneryList.append(stock);
        else if (dynamic_cast<ReadingMaterial*>(stock))
            m_readingMaterialList.append(stock);
        emit stockAdded(stock);
    });
}

QList<Stock*> StockList::getConfectioneryList() const
{
    return m_confectioneryList;
}

QList<Stock*> StockList::getReadingMaterialList() const
{
    return m_readingMaterialList;
}

StockList::StockList(QObject* parent)
    : QObject(parent)
{
}
