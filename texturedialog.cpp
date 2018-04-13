#include "texturedialog.h"
#include "ui_texturedialog.h"
#include <QFileDialog>
#include<iostream>

#include <string>
#include<ostream>
#include<list>
#include <sstream>
using namespace std;
TextureDialog::TextureDialog(double start,double end,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextureDialog)
{
    ui->setupUi(this);
    string Qstart;
    string Qend;
    std::cout<<end<<std::endl;
    ostringstream oss;
    oss<<start;
    Qstart = oss.str();
    oss<<end;
    Qend = oss.str();
    string title("贴图对话框（贴图范围"+Qstart+","+Qend+"）");
    setWindowTitle(QString::fromStdString(title));
    Form* m1 = new Form;
    Form* m2 = new Form;
    formList.append(m1);
    formList.append(m2);
    m1->setContentsMargins(0,0,0,0);
    e = new QVBoxLayout();
    e->setSizeConstraint(QLayout::SetDefaultConstraint);
    e->addWidget(m1);
    e->addWidget(m2);
    ui->scrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    ui->scrollAreaWidgetContents->setLayout(e);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

}

TextureDialog::~TextureDialog()
{
    delete ui;
}

void TextureDialog::on_confirmBtn_clicked()
{
   boxList.clear();
   for(int i = 0;i<formList.size();i++){
       if(formList[i]->isChoosed()){
           boxList.append(formList[i]->provide());
       }

   }
   this->accept();
}

void TextureDialog::on_concelBtn_clicked()
{
    this->close();

}



void TextureDialog::on_pushButton_clicked()
{
    Form *m = new Form;
    formList.append(m);
    e->addWidget(m);
}
