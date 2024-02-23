#ifndef STOCKLIST_H
#define STOCKLIST_H

#include <QObject>
#include <QList>
#include "stock.h"

class StockList : public QObject
{
    Q_OBJECT
public:
    static StockList* instance();

    void addStock(Stock* stock);

    QList<Stock*> getConfectioneryList() const;
    QList<Stock*> getReadingMaterialList() const;

signals:
    void stockAdded(Stock* stock);

private:
    StockList(QObject* parent = nullptr);

    static StockList* m_instance;
    QList<Stock*> m_confectioneryList;
    QList<Stock*> m_readingMaterialList;
};

#endif // STOCKLIST_H
