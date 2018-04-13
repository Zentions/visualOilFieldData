#include "checkdialog.h"
#include "ui_checkdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <string>
#include <QTextCodec>
CheckDialog::CheckDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckDialog)
{
    ui->setupUi(this);
    layerFlag = false;
    proFlag = false;
    init();
    connect(ui->treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));
}

CheckDialog::~CheckDialog()
{
    delete ui;
}

void CheckDialog::on_pushButton_clicked()
{
    layerFileName= QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"*.bmp");
    if(layerFileName!=NULL) {
        QStringList list = layerFileName.split(".");
        QString textFile = list[0]+"1.txt";
        readData(textFile,false);
        layerFlag = true;
     }else{
         QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     }
}

void CheckDialog::on_pushButton_2_clicked()
{
    profileFileName= QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"*.bmp");
    if(profileFileName!=NULL) {
        QStringList list = profileFileName.split(".");
        QString textFile = list[0]+"1.txt";
        readData(textFile,true);
        proFlag = true;
     }else{
         QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     }
}

void CheckDialog::on_pushButton_3_clicked()
{
    for(int i=0; i<group1->childCount(); i++)
    {
        if(Qt::Checked == group1->child(i)->checkState(0))
        {
            QString name = group1->child(i)->text(0);
            int j;
            for(j = 0;j<profileList.size();j++)
            {
                if(name==profileList[j].name)
                {
                    layerList[i].z = profileList[j].z;
//                    profileList[j].x = layerList[i].x;
//                    profileList[j].y = layerList[i].y;
                }
            }
        }
    }
    saveData(layerFileName,4);
//    saveData(profileFileName,1);
    QMessageBox::about(this, "提示", "校正成功");
}
void CheckDialog::readData(QString fileName,bool LOrP)
{

    if(fileName.isEmpty())
    {
        return ;
    }

    //读文件获得坐标
    QFile *file = new QFile(fileName);

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    int count = 0;
    while(!file->atEnd())
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");
        QByteArray line = file->readLine();

        QString str;
        str = codec->toUnicode(line);
        QStringList list=str.split(" ");
        //前三个是坐标
        count++;
        //true 是连井剖面图 false 是勘探成果图
        if(!LOrP)
        {
            if(count>4)
            {
               QTreeWidgetItem* subItem = new QTreeWidgetItem(group1);
               subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
               QString wellName = list[3];
               wellName = wellName.mid(0,wellName.length()-1);
               subItem->setText(0,wellName);  //设置井的名字
               subItem->setText(1,list[0]+" "+list[1]+" "+list[2]);
               subItem->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态
               layerList.append(DThree(list[0].toDouble(),list[1].toDouble(),list[2].toDouble(),wellName));
            }

        }
        else
        {
            if(list.size()==4)
            {
                QTreeWidgetItem* subItem = new QTreeWidgetItem(group2);
                subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                QString wellName = list[3];
                wellName = wellName.mid(0,wellName.length()-1);
                subItem->setDisabled(true);
                subItem->setText(0,wellName); //设置井的名字
                subItem->setText(1,list[0]+" "+list[1]+" "+list[2]);
                subItem->setCheckState(0,Qt::Unchecked); //设置子选项的显示格式和状态
                profileList.append(DThree(list[0].toDouble(),list[1].toDouble(),list[2].toDouble(),wellName));
            }

        }

    }
}
void CheckDialog::init()
{
    ui->treeWidget->clear();   //初始化树形控件

    //定义第一个树形组
    group1 = new QTreeWidgetItem(ui->treeWidget);
    group1->setText(0,"勘探成果图");    //树形控件显示的文本信息
    group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);   //设置树形控件子项的属性
    group1->setCheckState(0,Qt::Unchecked); //初始状态没有被选

    //定义第二个树形组
    group2 = new QTreeWidgetItem(ui->treeWidget);
    group2->setText(0,"连井剖面");
    group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group2->setCheckState(0,Qt::Unchecked);
}
void CheckDialog::treeItemChanged(QTreeWidgetItem* item, int column)
{
    //QString itemText = item->text(0);
    if(Qt::Checked == item->checkState(0))
    {
       // QTreeWidgetItem* parent = item->parent();
        int count = item->childCount(); //返回子项的个数
        if(count >0)
        {
            for(int i=0; i<count; i++)
            {
                item->child(i)->setCheckState(0,Qt::Checked);
            }
        }
        else
        {
            updateParentItem(item);
        }
     }
    else if(Qt::Unchecked == item->checkState(0))
    {
        int count = item->childCount();
        if(count > 0)
        {
            for(int i=0; i<count; i++)
            {
                item->child(i)->setCheckState(0,Qt::Unchecked);
            }
        }
        else
        {
            updateParentItem(item);
        }
    }
}
void CheckDialog::updateParentItem(QTreeWidgetItem* item)
{

    QTreeWidgetItem *parent = item->parent();
    if(parent == NULL)
    {
        return ;
    }
    int selectedCount = 0;
    int childCount = parent->childCount();
    for(int i=0; i<childCount; i++) //判断有多少个子项被选中
    {
        QTreeWidgetItem* childItem = parent->child(i);
        if(childItem->checkState(0) == Qt::Checked)
        {
            selectedCount++;
        }
    }
    if(selectedCount <= 0)  //如果没有子项被选中，父项设置为未选中状态
    {
        parent->setCheckState(0,Qt::Unchecked);
    }
    else if(selectedCount>0 && selectedCount<childCount)    //如果有部分子项被选中，父项设置为部分选中状态，即用灰色显示
    {
        parent->setCheckState(0,Qt::PartiallyChecked);
    }
    else if(selectedCount == childCount)    //如果子项全部被选中，父项则设置为选中状态
    {
        parent->setCheckState(0,Qt::Checked);
    }
}
void CheckDialog::saveData(QString fileName,int num)
{
    QStringList list = fileName.split(".");
    QString textFile = list[0]+"1.txt";
    QFile *file = new QFile(textFile);

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    int count = 0;
    QString str = NULL;
    while(!file->atEnd())
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");
        QByteArray line = file->readLine();
        str += codec->toUnicode(line);
        count++;
        if(count==num)break;

    }
    file->close();
    //写文件
    if(!file->open(QIODevice::WriteOnly  | QIODevice::Text))
    {
        std::cout<<"操作文件失败"<<std::endl;
        return;
    }
    QTextStream in(file);
    in<<str;
    if(num==4)
    {
        for(int i = 0;i<layerList.size();i++)
        {
           QString text = NULL;
           DThree one = layerList.at(i);
           text = QString::number(one.x,'f',2)+" "+QString::number(one.y,'f',2)+" "+QString::number(one.z,'f',2)+" "+one.name+"\n";
           in<<text;
        }
    }
    else
    {
        for(int i = 0;i<profileList.size();i++)
        {
           QString text = NULL;
           DThree one = profileList.at(i);
           text = QString::number(one.x,'f',2)+" "+QString::number(one.y,'f',2)+" "+QString::number(one.z,'f',2)+" "+one.name+"\n";
           in<<text;
        }
    }

    file->close();
}

void CheckDialog::on_pushButton_4_clicked()
{
    for(int i=0; i<layerList.size(); i++)
    {
        QString name = layerList[i].name;
        int j;
        for(j = 0;j<profileList.size();j++)
        {
            if(name==profileList[j].name)
            {
                layerList[i].z = profileList[j].z;
//                profileList[j].x = layerList[i].x;
//                profileList[j].y = layerList[i].y;
            }
        }

    }
    saveData(layerFileName,4);
    QMessageBox::about(this, "提示", "校正成功");
}
