#include "profilecaldialog.h"
#include "ui_profilecaldialog.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QRegExp>
#include <iostream>
#include <math.h>

ProfileCalDialog::ProfileCalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileCalDialog)
{
    ui->setupUi(this);
}

ProfileCalDialog::~ProfileCalDialog()
{
    delete ui;
}

bool isRight2(QString s)//验证字符串是否符合格式要求
{
    QRegExp rx("(-?\\d+(\\.\\d*)?\\s){2}\\S+");
    QRegExpValidator v(rx, 0);
    int pos = 0;
    if(v.validate(s, pos)==QRegExpValidator::Acceptable)
        return true;
    else return false;
}

void ProfileCalDialog::on_savedata_clicked()
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
    //存入剖面图坐标
    for(int i = 0;i<PosList.size();i++)
    {
       QString text = NULL;
       DThree one = PosList.at(i);
       if(i==0)
           text = QString::number(one.x,'f',2)+" "+QString::number(one.y,'f',2)+"\n";
       else if(i==1||i==(PosList.size()-1))
           text = QString::number(one.x,'f',2)+" "+QString::number(one.y,'f',2)+" "+one.name+"\n";
       else
           text = QString::number(one.x,'f',2)+" "+QString::number(one.y,'f',2)+" "+QString::number(one.z,'f',2)+" "+one.name+"\n";

       in<<text;
    }
    //存入像素坐标 以便计算纹理坐标
    in<<"0\n";
    for(int i = 3;i<PixelList.size();i++)
    {
       QString text = NULL;
       DTwo one = PixelList.at(i);
       text = QString::number(one.x,'f',2)+"\n";
       in<<text;
    }
    in<<QString::number(PixelList.at(0).x,'f',2)+"\n";
    QMessageBox::about(this, "提示", "保存成功");
    file.close();
}

void ProfileCalDialog::on_openfile_clicked()
{

    fileName= QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"*.bmp");
    if(fileName!=NULL) {
        scene= new LayerScene(fileName);
        this->ui->graphicsView->setScene(scene);
     }else{
         QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     }
}
void ProfileCalDialog::calculate(){

}

void ProfileCalDialog::on_calculate_clicked()
{
    //pixelList内部含有数据 格式如下
    //0。图片宽度、高度 1。记录点1像素坐标x、y  2。记录点2像素坐标x、y 3···
    PixelList = scene->getList();
    double z1 = this->ui->deepth1->text().toDouble();
    double z2 = this->ui->deepth2->text().toDouble();
    //深度方向单位像素代表实际深度
    double dz = (z1-z2)/(PixelList.at(1).y-PixelList.at(2).y);

    //计算图片上下顶边坐标 并保存到POSLIST中
    double zmin =  z1 + (0-PixelList.at(1).y)*dz;
    double zmax =  z1 + (PixelList.at(0).y-PixelList.at(1).y)*dz;
    PosList.append(DThree(zmin,zmax,0));

    //实际井口数
    int size = PixelList.size()-3;
    double *z = new double[size];
    for(int i=0;i<size;i++){
        z[i] = z1 + (PixelList.at(i+3).y-PixelList.at(1).y)*dz;
    }

    QString temp = ui->plainTextEdit->toPlainText();
    if( temp==NULL)
    {
        QMessageBox::about(this, "提示", "请选择点并填写坐标");
        return;
    }
    QStringList dataList = temp.split("\n");

    if( dataList.size()!=size)
    {
        QMessageBox::about(this, "提示", "请对应填写所有井坐标");
        return;
    }

    for(int i =0;i<size;i++)
    {
       if(!isRight2(dataList[i]))
       {
           QMessageBox::about(this, "提示", "您填写的数据格式不正确");
           return;
       }
    }

//计算图片最左边坐标
     QStringList well1 =   dataList.at(0).split(" ");
     double x1  = well1.at(0).toDouble();
     double y1  = well1.at(1).toDouble();
     double px1 = PixelList.at(3).x;

     QStringList well2 =   dataList.at(1).split(" ");
     double x2 = well2.at(0).toDouble();
     double y2 = well2.at(1).toDouble();
     double px2 = PixelList.at(4).x;

     double a = fabs(x1 - x2);
     double b = fabs(y1 - y2);
     double sum =  sqrt(a*a+b*b);

     double x0 = x1 + px1*sum/(px1-px2);
     double y0 = y1;

     PosList.append(DThree(x0,y0,0,"左"));

     //添加图片中间井口坐标
     for(int i=0;i<size;i++){
         QStringList well =   dataList.at(i).split(" ");
         double x = well.at(0).toDouble();
         double y = well.at(1).toDouble();
         QString name = well.at(2);
         PosList.append(DThree(x,y,z[i],name));
     }

  //计算图片最右边坐标
     well1 =   dataList.at(size-2).split(" ");
     x1  = well1.at(0).toDouble();
     y1  = well1.at(1).toDouble();
     px1 = PixelList.at(size+3-2).x;

     well2 =   dataList.at(size-1).split(" ");
     x2 = well2.at(0).toDouble();
     y2 = well2.at(1).toDouble();
     px2 = PixelList.at(size+3-1).x;

     a = fabs(x1 - x2);
     b = fabs(y1 - y2);
     sum =  sqrt(a*a+b*b);

     x0 = x2 - (px2-PixelList.at(0).x)*sum/(px2-px1);
     y0 = y2;

     PosList.append(DThree(x0,y0,0,"右"));


    ui->textBrowser->append(temp);
    ui->plainTextEdit->clear();
}
