#include "form.h"
#include "ui_form.h"
#include <QFileDialog>
#include<iostream>
#include <QMessageBox>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setSizeIncrement(375, 86);
}

Form::~Form()
{
    delete ui;
}




void Form::on_choose_clicked()
{
    ui->name_1->setText(QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"*.bmp"));
}
bool Form::isChoosed(){
   if(ui->check->isChecked())return true;
   else return false;
}
Data Form::provide(){
    Data data;
    if((ui->name_1->text()=="")||(ui->name_2->text()=="")||(ui->name_3->text()==""))
    {
        data.path = "NULL";
        data.start = "NULL";
        data.end = "NULL";
    }
    else{
        data.path = ui->name_1->text();
        data.start = ui->name_2->text();
        data.end = ui->name_3->text();
    }
    return data;

}
