#include "inputdatawindow.h"
#include "ui_inputdatawindow.h"

inputdatawindow::inputdatawindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputdatawindow)
{
    ui->setupUi(this);

    connect(ui->acceptButton, &QPushButton::clicked, this, &inputdatawindow::onacceptButtonclicked);
}


inputdatawindow::~inputdatawindow()
{
    delete ui;
}

QString inputdatawindow::getItem() const
{
    return ui->itemLineEdit->text();
}

int inputdatawindow::getQuantity() const
{
    return ui->quantitySpinBox->value();
}

bool inputdatawindow::isConfectionerySelected() const
{
    return ui->confectioneryRadioButton->isChecked();
}

bool inputdatawindow::isReadingMaterialSelected() const
{
    return ui->readingMaterialRadioButton->isChecked();
}

int inputdatawindow::getWeight() const
{
    return ui->weightSpinBox->value();
}

QString inputdatawindow::getFrequency() const
{
    return ui->frequencyComboBox->currentText();
}

void inputdatawindow::onacceptButtonclicked()
{
    accept();
}
