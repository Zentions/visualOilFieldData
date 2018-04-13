#include "loadsinglewellchart.h"


LoadSingleWellChart::LoadSingleWellChart()
{

}
SingleWellChart *LoadSingleWellChart::loadSin(QString fileName){
    SingleWellChart *singlewellchart = new SingleWellChart;

    //读取图片
    singlewellchart->setImage (osgDB::readImageFile(fileName.toLocal8Bit().toStdString()));


    //打开文件

    if(fileName.isEmpty()){return NULL;}
    QFileInfo fileInfo = QFileInfo(fileName);
    fileName = fileInfo.baseName();
    QFile *file = new QFile(fileInfo.path()+"/"+fileName);
    if(!file->open(QIODevice::ReadOnly|QIODevice::Text)){return NULL;}

    QTextStream stream(file);

    QString line;
    QStringList qList;

    osg::Vec3 pos;
    int length;
    int height;
    int totallength;
    double proportion;


    while(!stream.atEnd())
    {
        line = stream.readLine().trimmed();
        qList = line.split(" ",QString::KeepEmptyParts);
        if(line.contains("name"))
        {

            singlewellchart->setName(qList[1]);
        }
        else if(line.contains("totallength"))
        {
            singlewellchart->setTotallength(qList[1].toDouble());
            totallength = qList[1].toDouble();
        }
        else if(line.contains("length"))
        {
            singlewellchart->setLength(qList[1].toInt());
            length = qList[1].toInt();
        }
        else if(line.contains("height"))
        {
            singlewellchart->setHeight(qList[1].toInt());
            height = qList[1].toInt();
        }
        else if(line.contains("proportion"))
        {
            singlewellchart->setProportion(qList[1].toDouble());
            proportion = qList[1].toDouble();
        }

        else if(line.contains("postion"))
        {

            pos.set(qList[1].toDouble(),qList[2].toDouble(),qList[3].toDouble());
            singlewellchart->setPos(pos);
        }
    }


    double realLength = totallength*1.0/proportion;
    double realHeight = height*1.0*realLength/length;
    singlewellchart->setVertexOBO(pos.x()-realLength/2.0,pos.y(),pos.z());
    singlewellchart->setVertexOBO(pos.x()-realLength/2.0,pos.y(),pos.z()+realHeight);
    singlewellchart->setVertexOBO(pos.x()+realLength/2.0,pos.y(),pos.z());
    singlewellchart->setVertexOBO(pos.x()+realLength/2.0,pos.y(),pos.z()+realHeight);
    //设置纹理坐标
    singlewellchart->setTexCoordArrayOBO(0,0);
    singlewellchart->setTexCoordArrayOBO(0,1);
    singlewellchart->setTexCoordArrayOBO(1,0);
    singlewellchart->setTexCoordArrayOBO(1,1);

    singlewellchart->drawGeode();

    return singlewellchart;
}
