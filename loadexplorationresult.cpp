#include "loadexplorationresult.h"

LoadExplorationResult::LoadExplorationResult()
{

}
ExplorationResult *LoadExplorationResult::loadPicAndText(QString filename){
    ExplorationResult * explorationresult = new ExplorationResult();

    if(filename.isEmpty())
    {
        return NULL;
    }

    QFileInfo fileInfo = QFileInfo(filename);

    //读取图片
    explorationresult->setImage (osgDB::readImageFile(filename.toLocal8Bit().toStdString()));
    explorationresult->setFileName ( fileInfo.fileName());
    explorationresult->setName( fileInfo.baseName());

    //读取顶点

    filename = fileInfo.path()+"/"+fileInfo.baseName()+"1.txt";

    QFile *file = new QFile(filename);

//    double x,y,z;
    QList<double *>* data = new QList<double *>;


    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return NULL;
    }
    while(!file->atEnd())
    {

        QByteArray line = file->readLine();
        QString str(line);
        QStringList list=str.split(" ");
//        if(list.size()==1)
//        {
//            //第一次读出来的是一个Z值
//            z=list[0].toDouble();
//            continue;
//        }

//        x=list[0].toDouble();
//        y=list[1].toDouble();
        double *p = new double[3];
        p[0]   = list[0].toDouble();
        p[1]   = list[1].toDouble();
        p[2]   = list[2].toDouble();
        data->append(p);
//        explorationresult->setVertexOBO(x,y,z);
    }

    file->close();
    explorationresult->setData(data);

    explorationresult->initExplorationResult();
    return explorationresult;

}
ExplorationResult *LoadExplorationResult::loadExp(QString fileName){
    ExplorationResult * explorationresult = new ExplorationResult();

    //读取图片
    explorationresult->setImage (osgDB::readImageFile(fileName.toLocal8Bit().toStdString()));


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
    int mode;
    QList<double *>* data = new QList<double *>;


    while(!stream.atEnd())
    {
        line = stream.readLine().trimmed();
        qList = line.split(" ",QString::KeepEmptyParts);
        if(line.contains("picname"))
        {

            explorationresult->setFileName(qList[1]);
            picname = qList[1];
        }
        else if(line.contains("name"))
        {
            explorationresult->setName(qList[1]);
        }
        else if(line.contains("transparency"))
        {
            explorationresult->setTransparency(qList[1].toInt());
        }
        else if(line.contains("mode"))
        {
             explorationresult->setMode(qList[1].toInt());
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


                double *p = new double[3];
                p[0]   = pList[1].toDouble();
                p[1]   = pList[2].toDouble();
                p[2]   = pList[3].toDouble();
                data->append(p);

            }
        }
    }

    file->close();

    explorationresult->setData(data);

    explorationresult->initExplorationResult();

    return explorationresult;
}
ExplorationResult *LoadExplorationResult::loadByteExp(QString fileName){
    ExplorationResult * explorationresult = new ExplorationResult();

    //读取图片
    explorationresult->setImage (osgDB::readImageFile(fileName.toLocal8Bit().toStdString()));


    //打开文件

    if(fileName.isEmpty()){return NULL;}
    QFileInfo fileInfo = QFileInfo(fileName);
    fileName = fileInfo.baseName();
    QFile *file = new QFile(fileInfo.path()+"/"+fileName+".test");



    if(!file->open(QIODevice::ReadOnly)){return NULL;}

    QDataStream stream(file);

    QString picname;
    QString name;
    int transparency;



    stream>>picname;

    stream>>name;

    stream>>transparency;



            explorationresult->setFileName(picname);

            explorationresult->setName(name);


            explorationresult->setTransparency(transparency);


            int pNum;
            stream>>pNum;


            for(int i=0;i<pNum;i++)
            {
                double x,y,z;
                stream>>x>>y>>z;
                explorationresult->setVertexOBO(x,y,z);
            }


    file->close();

    explorationresult->initExplorationResult();
    return explorationresult;
}
