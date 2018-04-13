#include "singlewelldialog.h"
#include "ui_singlewelldialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
SingleWellDialog::SingleWellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingleWellDialog)
{
    ui->setupUi(this);
}

SingleWellDialog::~SingleWellDialog()
{
    delete ui;
}

void SingleWellDialog::on_toolButton_5_clicked()
{
    fileName= QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"*.bmp");
    if(fileName!=NULL) {
        scene= new LayerScene(fileName);
        this->ui->graphicsView->setScene(scene);
     }else{
         QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
     }
}

void SingleWellDialog::on_toolButton_6_clicked()
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
    QString text = NULL;
    //正则表达式验证输入字符串是否是符合格式要求
    QRegExp rx("(-?\\d+(\\.\\d*)?\\s){2}(-?\\d+(\\.\\d*)?)");
    QString s1 = ui->lineEdit->text();
    QRegExpValidator v(rx, 0);
    int pos = 0;
    if(v.validate(s1, pos)!=QRegExpValidator::Acceptable)
    {
        QMessageBox::about(this, "提示", "你输入的数据格式不正确");
        return;
    }
    rx.setPattern("\\d+");            //只能为数字
    v.setRegExp(rx);
    QString s2 = ui->lineEdit_2->text();
    if(v.validate(s2, pos)!=QRegExpValidator::Acceptable)
    {
        QMessageBox::about(this, "提示", "你输入的缩放比例含有非数字字符");
        return;
    }

    text += s1+" ";
    DTwo HAndL = scene->getList().at(0);
    text += QString::number(HAndL.x,'f',0)+" "+QString::number(HAndL.y,'f',0)+" ";
    text += s2+" ";
    text += ui->lineEdit_3->text();
    in<<text;
    QMessageBox::about(this, "提示", "保存成功");
    file.close();

}
