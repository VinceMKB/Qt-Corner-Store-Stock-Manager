#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QString>
#include <QListView>
#include <QStringListModel>

#include "stock.h"
#include "stocklist.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMenus();
    void updateListView(const QList<Stock*>& stockList);

    Ui::MainWindow *ui;
    StockList* stockList;
    QStringListModel* listModel;

private slots:
    void writeToXml();
    void showAddStockDialog();
    void showConfectioneryList();
    void showReadingMaterialList();
    void handleStockAdded(Stock* stock);
};

#endif // MAINWINDOW_H
