#include "projectDialog.h"
#include "ui_projectDialog.h"

ProjectDialog::ProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDialog)
{

    ui->setupUi(this);

    //设置复选框的默认状态
    ui->explorationResult->setChecked(true);

    ui->profile->setChecked(true);


}

ProjectDialog::~ProjectDialog()
{
    delete ui;
}
//将用户输入的数据作为信号发送
void ProjectDialog::on_confirmBtn_clicked()
{

    itemList = new QList<QCheckBox*>;
    itemStructList = new QList<PROJECTITEM*>;

    //获取用户输入的工程名称
    if(ui->projectName->text()=="")
    {
        QMessageBox::information(this,"Error Message","请输入名称");
        return;
    }

    //获取用户选择的目录名称
    if(ui->projectPath->text()=="")
    {
        QMessageBox::information(this,"Error Message","请选择工程路径");
        return ;
    }

    //获取用户选择的项目内容
    //获取用户选择的项目内容
    if(ui->strataSurface->checkState())
    {
        itemList->append(ui->strataSurface);
        itemStruct = new PROJECTITEM;
        itemStruct->name=ui->strataSurface->objectName();
        itemStruct->text=ui->strataSurface->text();
        itemStruct->type=MARK_TYPE_STRATASURFACE;
        itemStructList->append(itemStruct);
    }
    if(ui->fault->checkState())
    {
        itemList->append(ui->fault);
        itemStruct = new PROJECTITEM;
        itemStruct->name=ui->fault->objectName();
        itemStruct->text=ui->fault->text();
        itemStruct->type=MARK_TYPE_FAULT;
        itemStructList->append(itemStruct);
    }
    if(ui->well->checkState())
    {
        itemList->append(ui->well);
        itemStruct = new PROJECTITEM;
        itemStruct->name=ui->well->objectName();
        itemStruct->text=ui->well->text();
        itemStruct->type=MARK_TYPE_WELL;
        itemStructList->append(itemStruct);
    }
    if(ui->surfaceStrataModel->checkState())
    {
        itemList->append(ui->surfaceStrataModel);
        itemStruct = new PROJECTITEM;
        itemStruct->name=ui->surfaceStrataModel->objectName();
        itemStruct->text=ui->surfaceStrataModel->text();
        itemStruct->type=MARK_TYPE_SMODEL;
        itemStructList->append(itemStruct);
    }
    if(ui->volumeStrataModel->checkState())
    {
        itemList->append(ui->volumeStrataModel);
        itemStruct = new PROJECTITEM;
        itemStruct->name=ui->volumeStrataModel->objectName();
        itemStruct->text=ui->volumeStrataModel->text();
        itemStruct->type=MARK_TYPE_VMODEL;
        itemStructList->append(itemStruct);
    }
    if(ui->explorationResult->checkState())
    {
        itemList->append(ui->explorationResult);
        itemStruct = new PROJECTITEM;
        itemStruct->name=ui->explorationResult->objectName();
        itemStruct->text=ui->explorationResult->text();
        itemStruct->type=MARK_TYPE_EXPLORATIONRESULT;
        itemStructList->append(itemStruct);
    }
    if(ui->profile->checkState())
    {
        itemList->append(ui->profile);
        itemStruct = new PROJECTITEM;
        itemStruct->name=ui->profile->objectName();
        itemStruct->text=ui->profile->text();
        itemStruct->type=MARK_TYPE_PROFILE;
        itemStructList->append(itemStruct);
    }
    if(ui->compositeColumn->checkState())
    {
        itemList->append(ui->compositeColumn);
        itemStruct = new PROJECTITEM;
        itemStruct->name=ui->compositeColumn->objectName();
        itemStruct->text=ui->compositeColumn->text();
        itemStruct->type=MARK_TYPE_CCOLUMN;
        itemStructList->append(itemStruct);
    }



    //创建工程目录
    if(!ProjectOperation::createFolder(this,ui->projectPath->text()+"/"+ui->projectName->text()))
        return;

    //建立工程资源目录
    this->createResourceFolder();

    //创建工程文件
    if(!ProjectOperation::createProjectFile(ui->projectPath->text()+"/"+ui->projectName->text()+"/"+ui->projectName->text()+".vod"))
        return;
    //emit sendData(ui->projectPath->text()+"/"+ui->projectName->text(),itemList);
    emit sendData(ui->projectPath->text()+"/"+ui->projectName->text(),itemStructList);
    //emit sendData(ui->projectName->text(),ui->projectPath->text(),itemStructList);

    this->close();

}

void ProjectDialog::on_concelBtn_clicked()
{
    this->close();
}
//方便此类重用
void ProjectDialog::setTypeName(QString typeName)
{

    ui->label->setText(typeName+"名称：");
}




void ProjectDialog::on_browseBtn_clicked()
{
    ui->projectPath->setText(QFileDialog::getExistingDirectory(this,"选择目录",QDir::currentPath(),QFileDialog::ShowDirsOnly));
}

void ProjectDialog::createResourceFolder()
{
    for(int i=0;i<itemList->size();i++)
    {
        if(itemList->at(i)->checkState())
            ProjectOperation::createFolder(this,ui->projectPath->text()+"/"+ui->projectName->text()+"/"+itemList->at(i)->text());
    }
}
