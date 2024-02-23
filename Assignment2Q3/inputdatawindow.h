#ifndef INPUTDATAWINDOW_H
#define INPUTDATAWINDOW_H

#include <QDialog>

namespace Ui {
class inputdatawindow;
}

class inputdatawindow : public QDialog
{
    Q_OBJECT

public:
    explicit inputdatawindow(QWidget *parent = nullptr);
    ~inputdatawindow();

    QString getItem() const;
    int getQuantity() const;
    bool isConfectionerySelected() const;
    bool isReadingMaterialSelected() const;
    int getWeight() const;
    QString getFrequency() const;

private slots:
    void onacceptButtonclicked();

private:
    Ui::inputdatawindow *ui;
};

#endif // INPUTDATAWINDOW_H
