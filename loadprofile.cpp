#include "loadprofile.h"

LoadProfile::LoadProfile()
{

}

Profile *LoadProfile::loadPicAndText(QString filename){
    Profile * profile = new Profile();

    if(filename.isEmpty())
    {
        return NULL;
    }


    QFileInfo fileInfo = QFileInfo(filename);

    //读取图片
    profile->setImage (osgDB::readImageFile(filename.toLocal8Bit().toStdString()));
    profile->setFileName ( fileInfo.fileName());
    profile->setName( fileInfo.baseName());


    //读取顶点
    filename = fileInfo.path()+"/"+fileInfo.baseName()+"1.txt";

    QFile *file = new QFile(filename);

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return NULL;
    }


    double x,y,zl,zh;
    int flag = 0;
    osg::Vec2Array* temp = new  osg::Vec2Array;

    while(!file->atEnd())
    {

        QByteArray line = file->readLine();
        QString str(line);
        QStringList list=str.split(" ");
        //第一次读出来的是图片的两个Z值，有且只有两个Z值
        if(flag==0){
                   flag=1;
                   zh=list[0].toDouble();
                   zl=list[1].toDouble();
                   continue;
        }

        if(list.size()>=2){
        x=list[0].toDouble();
        y=list[1].toDouble();

        profile->setVertexOBO(x,y,zl);
        profile->setVertexOBO(x,y,zh);
        }
        else{
            temp->push_back(osg::Vec2(list[0].toDouble(),0));
            temp->push_back(osg::Vec2(list[0].toDouble(),1));
        }
    }
    int n = temp->getNumElements();
    for(int i=0;i<n;i=i+2){
        profile->setTexCoordArrayOBO((*temp)[i].x()/(*temp)[n-1].x(),0);
        profile->setTexCoordArrayOBO((*temp)[i].x()/(*temp)[n-1].x(),1);
    }
    file->close();

    profile->initProfile();
    return profile;
}

Profile *LoadProfile::loadPro(QString fileName){
    Profile * profile = new Profile();

    //读取图片
    profile->setImage (osgDB::readImageFile(fileName.toLocal8Bit().toStdString()));


    //打开文件

    if(fileName.isEmpty()){return NULL;}
    QFileInfo fileInfo = QFileInfo(fileName);
    fileName = fileInfo.baseName();
    QFile *file = new QFile(fileInfo.path()+"/"+fileName);
    if(!file->open(QIODevice::ReadOnly|QIODevice::Text)){return NULL;}

    QTextStream stream(file);

    QString line;
    QStringList qList;

    QString picname;

    while(!stream.atEnd())
    {
        line = stream.readLine().trimmed();
        qList = line.split(" ",QString::KeepEmptyParts);
        if(line.contains("picname"))
        {

            profile->setFileName(qList[1]);
            picname = qList[1];
        }
        else if(line.contains("name"))
        {
            profile->setName(qList[1]);
        }
        else if(line.contains("transparency"))
        {
            profile->setTransparency(qList[1].toInt());
        }

        else if(line.contains("point")&& line.contains("begin"))
        {
            int pNum = qList[1].toInt();
            QStringList pList;
            QString qs;
            for(int i=0;i<pNum;i++)
            {
                qs = stream.readLine();
                pList = qs.split(" ",QString::KeepEmptyParts);
                profile->setVertexOBO(pList[1].toDouble(),pList[2].toDouble(),pList[3].toDouble());
            }
        }
        else if(line.contains("texcoord")&& line.contains("begin"))
        {
            int pNum = qList[1].toInt();
            QStringList pList;
            QString qs;
            for(int i=0;i<pNum;i++)
            {
                qs = stream.readLine();
                pList = qs.split(" ",QString::KeepEmptyParts);
                profile->setTexCoordArrayOBO(pList[1].toDouble(),pList[2].toDouble());
            }
        }
    }

    file->close();

    profile->initProfile();
    return profile;
}
Profile *LoadProfile::loadProCal(QString filename) {
    Profile * profile = new Profile();

    if(filename.isEmpty())
    {
        return NULL;
    }


    QFileInfo fileInfo = QFileInfo(filename);

    //读取图片
    profile->setImage (osgDB::readImageFile(filename.toLocal8Bit().toStdString()));
    profile->setFileName ( fileInfo.fileName());
    profile->setName( fileInfo.baseName());


    //读取顶点
    filename = fileInfo.path()+"/"+fileInfo.baseName()+"1.txt";

    QFile *file = new QFile(filename);

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return NULL;
    }


    double x,y,zl,zh;
    int flag = 0;

    while(!file->atEnd())
    {

        QByteArray line = file->readLine();
        QString str(line);
        QStringList list=str.split(" ");
        //第一次读出来的是图片的两个Z值，有且只有两个Z值
        if(flag==0){
           flag=1;
           zh=list[0].toDouble();
           zl=list[1].toDouble();
           profile->setVertexOBO(0,0,zl);
           profile->setVertexOBO(0,0,zh);
           continue;
        }

        x=list[0].toDouble();
        y=list[1].toDouble();
        profile->setVertexOBO(x,y,zl);
        profile->setVertexOBO(x,y,zh);

    }

     profile->setVertexOBO(0,0,zl);
     profile->setVertexOBO(0,0,zh);

    file->close();

    profile->setTexCoordArray();

    profile->initProfile();
    return profile;
}
