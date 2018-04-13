#include "loadWell.h"

LoadWell::LoadWell()
{
}

//按照路径读取DEV文件，返回Well对象
Well *LoadWell::loadDEV(QString path)
{
    Well *well = new Well;
    double x,y,z;
    double headx,heady,headz;
    QFileInfo fileInfo;
    QString fileName = path;
    QString wellName,wellType;

    //打开文件

    if(fileName.isEmpty()){return NULL;}
    fileInfo = QFileInfo(fileName);
    fileName = fileInfo.baseName();
    QFile *file = new QFile(fileInfo.path()+"/"+fileName+".dev");
    if(!file->open(QIODevice::ReadOnly|QIODevice::Text)){return NULL;}
    //跳过第一行
    QByteArray linedata = file->readLine();
    //获取井名
    linedata = file->readLine();
    wellName = QString(linedata).simplified().trimmed().split(" ",QString::KeepEmptyParts).at(3);


    well->setWellName(wellName);
    //获得井头x坐标
    linedata = file->readLine();
    headx=QString(linedata).simplified().trimmed().split(" ",QString::KeepEmptyParts).at(4).toDouble();
    //获得井头y坐标
    linedata = file->readLine();
    heady=QString(linedata).simplified().trimmed().split(" ",QString::KeepEmptyParts).at(4).toDouble();
    //获得井头z坐标
    linedata = file->readLine();
    headz=QString(linedata).simplified().trimmed().split(" ",QString::KeepEmptyParts).at(3).toDouble();

    well->setWellHeadXYZ(osg::Vec3(headx,heady,headz));
     //获取井别
    linedata = file->readLine();
    wellType = QString(linedata).simplified().trimmed().split(" ",QString::KeepEmptyParts).at(3);

    if(wellType.toLower().contains("oil"))
        well->setWellType(0);
    else if (wellType.toLower().contains("gas"))
        well->setWellType(1);
    else if(wellType.toLower().contains("water"))
        well->setWellType(2);
    else
        well->setWellType(3);

    //跳过无关信息
    while(!file->atEnd())
    {
        linedata = file->readLine();
        QStringList list=QString(linedata).simplified().trimmed().split(" ",QString::KeepEmptyParts);
        if(list[0]=="MD")
            break;

    }
    linedata = file->readLine();

    //读取井数据
    int num=0;
    while(!file->atEnd())
    {
        linedata = file->readLine();
        QStringList list=QString(linedata).simplified().trimmed().split(" ",QString::KeepEmptyParts);
        if(list.size()<=0)continue;
        x=list[1].toDouble();
        y=list[2].toDouble();
        z=list[3].toDouble();
        num++;
        well->getWellTrace_dataXYZ()->push_back(osg::Vec3(x,y,z));
    }
    file->close();
    well->setWellTrace_dataNum(num);
    well->setWellFileName(path);
//    qDebug()<<num;

    return well;
}
//按照路径读取WELL文件，返回Well对象
Well *LoadWell::loadWELL(QString path)
{
    Well *well = new Well;
    well->setWellFileName(path);
    well->readWellData();
    return well;
}


