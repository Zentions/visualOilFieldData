#include "propertysetdialog.h"
#include "ui_propertysetdialog.h"
#include <QtGui>

PropertySetDialog::PropertySetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertySetDialog)
{
    ui->setupUi(this);
    this->confirm = -1;
}

PropertySetDialog::~PropertySetDialog()
{
    delete ui;
}
void PropertySetDialog::getPropertyData(QStringList propertyname){
    if(!propertyname.isEmpty())
    {

            QStringListModel *model = new QStringListModel(propertyname);
            ui->listView->setModel(model);
    }

}
int PropertySetDialog::getchoice(){
    return this->confirm;
}

void PropertySetDialog::on_ok_clicked()
{
    this->confirm = this->ui->listView->currentIndex().row();
    this->close();
}

void PropertySetDialog::on_pushButton_2_clicked()
{
    this->close();
}

