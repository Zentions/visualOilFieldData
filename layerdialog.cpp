#include "layerdialog.h"
#include "ui_layerdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QRegExp>
#include <iostream>
LayerDialog::LayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayerDialog)
{
    ui->setupUi(this);
    ui->toolButton_2->setEnabled(false);
}

LayerDialog::~LayerDialog()
{
    delete ui;
}
bool isRight(QString s)//验证字符串是否符合格式要求
{
    QRegExp rx("(-?\\d+(\\.\\d*)?\\s){3}\\S+");
    QRegExpValidator v(rx, 0);
    int pos = 0;
    if(v.validate(s, pos)==QRegExpValidator::Acceptable)
        return true;
    else return false;
}

void LayerDialog::on_toolButton_clicked()
{
    if(scene->getSize()>3)
    {
        QMessageBox::about(this, "提示", "您选中了大于两个的点，我们将以前两个为参考");
        for(int i = 3;i<scene->getSize();i++)
        {
            scene->getList().removeAt(i);
        }
        return;
    }
    if(scene->getSize()<3)
    {
        QMessageBox::about(this, "提示", "请在图中选择两个点");
        return;
    }
    if(ui->lineEdit->text()==NULL ||ui->lineEdit_2->text()==NULL)
    {
        QMessageBox::about(this, "提示", "请填写您选择两个点的实际坐标");
        return;
    }

    QString str1 = ui->lineEdit->text();
    QString str2 = ui->lineEdit_2->text();
    if((!isRight(str1))|| (!isRight(str2)))
    {
        QMessageBox::about(this, "提示", "您填写的数据格式不正确");
        return;
    }
    //验证通过后做一些设置
    if(scene->getSize()==3)ui->toolButton_2->setEnabled(true);
    ui->toolButton->setEnabled(false);
    scene->setClickToFalse();
    QStringList list1 = str1.split(" ");
    QStringList list2 = str2.split(" ");
    first.x = list1[0].toDouble();
    first.y = list1[1].toDouble();
    first.z = list1[2].toDouble();
    first.name = list1[3];
    second.x = list2[0].toDouble();
    second.y = list2[1].toDouble();
    second.z = list2[2].toDouble();
    second.name = list2[3];
    calculate();
}

void LayerDialog::on_toolButton_2_clicked()
{
    QString temp = ui->plainTextEdit->toPlainText();
    if( temp==NULL)
    {
        QMessageBox::about(this, "提示", "请选择点并填写坐标");
        return;
    }
    QStringList dataList = temp.split("\n");
    for(int i =0;i<dataList.size();i++)
    {
       if(!isRight(dataList[i]))
       {
           QMessageBox::about(this, "提示", "您填写的数据格式不正确");
           return;
       }
    }
    ui->textBrowser->append(temp);
    ui->plainTextEdit->clear();
}

void LayerDialog::on_toolButton_3_clicked()
{
    QStringList list = fileName.split(".");
    QString textFile = list[0]+"1.txt";
    QFile file(textFile);
    if(!file.open(QIODevice::WriteOnly  | QIODevice::Text))
    {
        std::cout<<"操作文件失败"<<std::endl;
        return;
    }
    QTextStream in(&file);
    for(int i = 0;i<PosList.size();i++)
    {
       QString text = NULL;
       DThree one = PosList.at(i);
       if(isLayerOrPro && i==0) text = QString::number(one.x,'f',2)+" "+QString::number(one.y,'f',2)+"\n";
       else text = QString::number(one.x,'f',2)+" "+QString::number(one.y,'f',2)+" "+QString::number(one.z,'f',2)+" "+one.name+"\n";
       in<<text;
    }
    QString temp = ui->textBrowser->toPlainText();
    in<<temp;
    QMessageBox::about(this, "提示", "保存成功");
    file.close();

}
//生成四脚坐标
void LayerDialog::calculate()
{
    double x,x0,y0,y,z,z0;
    PixelList = scene->getList();
    ui->textBrowser->append(QString::number(first.x,'f',2)+" "+QString::number(first.y,'f',2)+" "+QString::number(first.z,'f',2)+" "+first.name);
    ui->textBrowser->append(QString::number(second.x,'f',2)+" "+QString::number(second.y,'f',2)+" "+QString::number(second.z,'f',2)+" "+second.name);
    if(!isLayerOrPro)
    {
        rateY = (first.y - second.y)*1.0/(PixelList.at(1).y-PixelList.at(2).y);
        if(rateY<0)rateY *= -1;
        y0 = first.y - (0-PixelList.at(1).y)*rateY;
        y = first.y - (PixelList.at(0).y-PixelList.at(1).y)*rateY;
        rateX = (first.x - second.x)*1.0/(PixelList.at(1).x-PixelList.at(2).x);
        if(rateX<0)rateX *= -1;
        x0 = first.x + (0-PixelList.at(1).x)*rateX;
        x = first.x + (PixelList.at(0).x-PixelList.at(1).x)*rateX;
        PosList.append(DThree(x0,y0,0,"左上"));
        PosList.append(DThree(x0,y,0,"左下"));
        PosList.append(DThree(x,y0,0,"右上"));
        PosList.append(DThree(x,y,0,"右下"));
    }
    else
    {
        rateZ = (first.z - second.z)*1.0/(PixelList.at(1).y-PixelList.at(2).y);
        if(rateZ<0)rateZ *= -1;
        z0 = first.z - (0-PixelList.at(1).y)*rateZ;
        z = first.z - (PixelList.at(0).y-PixelList.at(1).y)*rateZ;
        PosList.append(DThree(z0,z,0));
    }
//    PosList.append(first);
//    PosList.append(second);
}

void LayerDialog::on_toolButton_4_clicked()
{

    fileName= QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"*.bmp");
    if(fileName!=NULL) {
        scene= new LayerScene(fileName);
        this->ui->graphicsView->setScene(scene);
        isLayerOrPro = false;
     }else{
         QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     }

}



void LayerDialog::on_toolButton_5_clicked()
{
    fileName= QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"*.bmp");
    if(fileName!=NULL) {
        scene= new LayerScene(fileName);
        this->ui->graphicsView->setScene(scene);
        isLayerOrPro = true;
     }else{
         QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     }
}
