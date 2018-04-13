#include "loadStrataSurface.h"
#include "strataSurface.h"
LoadStrataSurface::LoadStrataSurface()
{

}
//按照路径读取Tin文件，返回StrataSurface对象
StrataSurface* LoadStrataSurface::loadTin(QString filePath)
{
    StrataSurface* strataSurface = new StrataSurface();

    if(filePath.isEmpty())
    {
        return NULL;
    }
    //读取文件属性

    int m,n,linecounter;
    int markline;
    //读取坐标值
    double x,y,z;


    //三角形顶点序号
    int* a[3];

    //读文件获得坐标
    QFile *file = new QFile(filePath);

    QFileInfo fileInfo = QFileInfo(filePath);
    strataSurface->setName( fileInfo.baseName());

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return NULL;
    }
    linecounter = 0;
    while(!file->atEnd())
    {
        linecounter++;

        QByteArray line = file->readLine();
        QString str(line);
        QStringList list=str.split(" ",QString::KeepEmptyParts);



        //跳过文件中的空行
        if(list.size()<=0)
            continue;

        if(linecounter==2){
            m = list[0].toInt();
            n = list[1].toInt();
            strataSurface->setTriangleNum( n);
            a[0] = new int[n];
            a[1] = new int[n];
            a[2] = new int[n];
        }
        else if(linecounter>2&&linecounter<=2+m){
            x = list[1].toDouble();
            y = list[2].toDouble();
            z = list[3].toDouble();

            strataSurface->setVertexOBO(x,y,z);
        }
        else if(linecounter>2+m&&linecounter<=2+m+n){

            int i = list[0].toInt();

            //注意这读取的时候注意三角形点的顺序 ，使得自动计算法向量的方向合适
            a[0][i] = list[3].toInt();
            a[1][i] = list[2].toInt();
            a[2][i] = list[1].toInt();
        }

        //读取属性
        else if(linecounter>=3+m+n){
            if(list.size()==5){
                markline = linecounter;

                QString name1;
                int *pro1;

            //初始化属性数组 结构为 数组大小 属性类型 属性下限 属性上限
                pro1 = new int[list[1].toInt()+4];
                name1 = list[0];
                pro1[0] = list[1].toInt()+4;
                pro1[1] = list[2].toInt();
                pro1[2] = list[3].toInt();
                pro1[3] = list[4].toInt();

                for(;linecounter<markline+list[1].toInt();linecounter++){

                    line = file->readLine();

                    str.clear();
                    str.append(line);
                    int index = linecounter-markline;
                    pro1[index+4] = str.toInt();

                    }
                strataSurface->setProData(pro1,name1);
                }
            }


    }

    file->close();

    strataSurface->setTrianglePoint(a);
    strataSurface->initStrataSurface();

    return strataSurface;
}
//按照路径读取地层面文件，返回StrataSurface对象
StrataSurface* LoadStrataSurface::loadSS(QString fileName)
{
    StrataSurface* strataSurface = new StrataSurface();

    //打开文件

    if(fileName.isEmpty()){return NULL;}
    QFileInfo fileInfo = QFileInfo(fileName);
    fileName = fileInfo.baseName();
    QFile *file = new QFile(fileInfo.path()+"/"+fileName);
    if(!file->open(QIODevice::ReadOnly|QIODevice::Text)){return NULL;}

    int position;
    int transparency;

    QTextStream stream(file);

    QString line;
    QStringList qList;
    while(!stream.atEnd())
    {

        line = stream.readLine().trimmed();
        qList = line.split(" ",QString::KeepEmptyParts);
        if(line.contains("name"))
        {
            strataSurface->setName(qList[1]);
        }
        else if(line.contains("color")&&qList.size()==5)
        {
            strataSurface->setSingleColor(osg::Vec4(qList[1].toFloat(),
                                                    qList[2].toFloat(),
                                                    qList[3].toFloat(),
                                                    qList[4].toFloat())
                                          );
        }
        else if(line.contains("position")){
            position = qList[1].toInt();
        }
        else if(line.contains("transparency"))
        {
            transparency = qList[1].toFloat();

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
                strataSurface->setVertexOBO(pList[1].toDouble(),pList[2].toDouble(),pList[3].toDouble());
            }
        }
        else if(line.contains("triangle")&& line.contains("begin"))
        {
            //三角形顶点序号
            int* a[3];
            QStringList triList;
            QString qs;
            int triNum = qList[1].toInt();
            strataSurface->setTriangleNum(triNum);
            a[0] = new int[triNum];
            a[1] = new int[triNum];
            a[2] = new int[triNum];
            for(int i=0;i<triNum;i++)
            {
                qs = stream.readLine();
                triList = qs.split(" ",QString::KeepEmptyParts);
//              strataSurface->setVertexOBO(QString(qList.at(1)).toDouble(),QString(qList.at(2)).toDouble(),QString(qList.at(3)).toDouble());
                a[0][i] = triList[1].toInt();
                a[1][i] = triList[2].toInt();
                a[2][i] = triList[3].toInt();
            }
            strataSurface->setTrianglePoint(a);
        }
        else if(line.contains("property")&& line.contains("begin"))
        {
            QStringList triList;
            QString qs;
            int size = qList[1].toInt();
            for(int j=0;j<size;j++){
                qs = stream.readLine();
                triList = qs.split(" ",QString::KeepEmptyParts);
                QString proname = triList[0];
                int length = triList[1].toInt();
                int *pro;
                pro = new int[length];
                for(int i=0;i<length;i++){
                    qs = stream.readLine();
                    triList = qs.split(" ",QString::KeepEmptyParts);
                    pro[i] = triList[0].toInt();
                }
                strataSurface->setProData(pro,proname);

            }
        }
        else if(line.contains("colorset")&& line.contains("begin"))
        {
            QStringList triList;
            QString qs;
            int size = qList[1].toInt();
            for(int j=0;j<size;j++){
                QColor * colorset = new QColor[2];
                for(int i=0;i<2;i++){
                    qs = stream.readLine();
                    triList = qs.split(" ",QString::KeepEmptyParts);
                    colorset[i].setRed(triList[0].toInt());
                    colorset[i].setGreen(triList[1].toInt());
                    colorset[i].setBlue(triList[2].toInt());
                    colorset[i].setAlpha(triList[3].toInt());
                }

                strataSurface->setColorSet(colorset,j);

            }
        }
    }
    file->close();


    strataSurface->initStrataSurface();

    strataSurface->setByProPosition(position);

    if(transparency==50)
    strataSurface->setHalfTransparency(true);


    return strataSurface;
}
