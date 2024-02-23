#include "mainwindow.h"
#include "confectionery.h"
#include "readingmaterial.h"
#include "ui_mainwindow.h"
#include "inputdatawindow.h"
#include "stockfactory.h"

#include <QFile>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), stockList(StockList::instance())
{
    ui->setupUi(this);
    createMenus();
    connect(stockList, &StockList::stockAdded, this, &MainWindow::handleStockAdded);

    // Create the list model and set it on the list view
    listModel = new QStringListModel(this);
    ui->listView->setModel(listModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus()
{
    connect(ui->actionAddStockItem, &QAction::triggered, this, &MainWindow::showAddStockDialog);
    connect(ui->actionConfectioneryList, &QAction::triggered, this, &MainWindow::showConfectioneryList);
    connect(ui->actionReadingMaterialList, &QAction::triggered, this, &MainWindow::showReadingMaterialList);
    connect(ui->actionWriteToXML, &QAction::triggered, this, &MainWindow::writeToXml);

}

void MainWindow::showAddStockDialog()
{
    inputdatawindow dialog;
    if (dialog.exec() == QDialog::Accepted) {
        QString item = dialog.getItem();
        int quantity = dialog.getQuantity();
        QString itemType;

        if (dialog.isConfectionerySelected()) {
            int weight = dialog.getWeight();
            itemType = "Confectionery";
            Stock* stock = StockFactory::createStock(itemType, item, quantity, weight, "");
            if (stock) {
                stockList->addStock(stock);
            }
        } else if (dialog.isReadingMaterialSelected()) {
            QString frequency = dialog.getFrequency();
            itemType = "ReadingMaterial";
            Stock* stock = StockFactory::createStock(itemType, item, quantity, 0, frequency);
            if (stock) {
                stockList->addStock(stock);
            }
        }
    }
    dialog.close(); // Close the dialog
}



void MainWindow::showConfectioneryList()
{
    QList<Stock*> confectioneryList = stockList->getConfectioneryList();
    updateListView(confectioneryList);
}

void MainWindow::showReadingMaterialList()
{
    QList<Stock*> readingMaterialList = stockList->getReadingMaterialList();
    updateListView(readingMaterialList);
}

void MainWindow::handleStockAdded(Stock* stock)
{
    if (Confectionery* confectionery = dynamic_cast<Confectionery*>(stock)) {
        listModel->insertRow(listModel->rowCount());
        QModelIndex index = listModel->index(listModel->rowCount() - 1);
        listModel->setData(index, confectionery->toString());
    } else if (ReadingMaterial* readingMaterial = dynamic_cast<ReadingMaterial*>(stock)) {
        listModel->insertRow(listModel->rowCount());
        QModelIndex index = listModel->index(listModel->rowCount() - 1);
        listModel->setData(index, readingMaterial->toString());
    }

    ui->listView->viewport()->update();
}



void MainWindow::updateListView(const QList<Stock*>& stockList)
{
    QStringList itemList;
    for (Stock* stock : stockList) {
        itemList << stock->toString();
    }
    listModel->setStringList(itemList);
}

void MainWindow::writeToXml()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save XML File"), "", tr("XML Files (*.xml)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file for writing."));
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("stockList");

    QList<Stock*> confectioneryList = stockList->getConfectioneryList();
    QList<Stock*> readingMaterialList = stockList->getReadingMaterialList();

    // Write Confectionery items
    for (Stock* stock : confectioneryList)
    {
        Confectionery* confectionery = dynamic_cast<Confectionery*>(stock);
        if (confectionery)
        {
            xmlWriter.writeStartElement("stockItem");
            xmlWriter.writeAttribute("type", "Confectionery");

            xmlWriter.writeStartElement("item");
            xmlWriter.writeCharacters(confectionery->getItem());
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("quantity");
            xmlWriter.writeCharacters(QString::number(confectionery->getQuantity()));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("weight");
            xmlWriter.writeCharacters(QString::number(confectionery->getWeight()));
            xmlWriter.writeEndElement();

            xmlWriter.writeEndElement(); // End of stockItem
        }
    }

    // Write ReadingMaterial items
    for (Stock* stock : readingMaterialList)
    {
        ReadingMaterial* readingMaterial = dynamic_cast<ReadingMaterial*>(stock);
        if (readingMaterial)
        {
            xmlWriter.writeStartElement("stockItem");
            xmlWriter.writeAttribute("type", "ReadingMaterial");

            xmlWriter.writeStartElement("item");
            xmlWriter.writeCharacters(readingMaterial->getItem());
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("quantity");
            xmlWriter.writeCharacters(QString::number(readingMaterial->getQuantity()));
            xmlWriter.writeEndElement();

            xmlWriter.writeStartElement("frequency");
            xmlWriter.writeCharacters(readingMaterial->getFrequency());
            xmlWriter.writeEndElement();

            xmlWriter.writeEndElement(); // End of stockItem
        }
    }

    xmlWriter.writeEndElement(); // End of stockList
    xmlWriter.writeEndDocument();

    file.close();

    QMessageBox::information(this, tr("Write to XML"), tr("Stock list has been written to XML file."));
}

