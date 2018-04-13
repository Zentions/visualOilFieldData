#include "singlewellchart.h"

SingleWellChart::SingleWellChart()
{
    this->geode    = new osg::Geode();
    this->image       = NULL;
    this->vertexarray = NULL;
}
void SingleWellChart::setImagebyURL(QString filename){
    //按照路径读图，并把图片名赋值给name
    this->image = osgDB::readImageFile(filename.toStdString());
    QFileInfo fileInfo = QFileInfo(filename);
    this->name = fileInfo.baseName();
}
void SingleWellChart::setVertexArraybyURL(QString filename,double TotalLength){
    if(filename.isEmpty())
    {
        return ;
    }

   // osg::Vec2Array* temp = new  osg::Vec2Array;

    //读文件获得坐标
    QFile *file = new QFile(filename);

    QFileInfo fileInfo = QFileInfo(filename);
    this->name = fileInfo.baseName();

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    while(!file->atEnd())
    {

        QByteArray line = file->readLine();
        QString str(line);
        QStringList list=str.split(" ");
        //前三个是坐标，后两个是像素值
        pos.set(list[0].toDouble(),list[1].toDouble(),list[2].toDouble());
        length = list[3].toInt();
        height = list[4].toInt();
        proportion = list[5].toDouble();

    }
    double realLength = TotalLength*1.0/proportion;
    double realHeight = height*1.0*realLength/length;
    this->setVertexOBO(pos.x()-realLength/2.0,pos.y(),pos.z());
    this->setVertexOBO(pos.x()-realLength/2.0,pos.y(),pos.z()+realHeight);
    this->setVertexOBO(pos.x()+realLength/2.0,pos.y(),pos.z());
    this->setVertexOBO(pos.x()+realLength/2.0,pos.y(),pos.z()+realHeight);
    //设置纹理坐标
    this->setTexCoordArrayOBO(0,0);
    this->setTexCoordArrayOBO(0,1);
    this->setTexCoordArrayOBO(1,0);
    this->setTexCoordArrayOBO(1,1);
    this->totallength = TotalLength;

}
void  SingleWellChart::saveTo(QString path){
    QFile file(path+"/"+this->getName());
    QTextStream stream(&file);

    if(!file.open(QIODevice::WriteOnly))
    {
        return ;
    }

    stream<<"name "<<this->name<<endl;

    stream<<"length "<<this->length<<endl;

    stream<<"height "<<this->height<<endl;

    stream<<"proportion "<<this->proportion<<endl;

    stream<<"totallength "<<this->totallength<<endl;

    //存储点
    stream<<"postion "<<pos.x()<<" "<<pos.y()<<" "<<pos.z()<<endl;


    file.close();

}
//一次添加一个顶点，使用此函数是要注意添加顺序，按照三角带图元顺序添加
void SingleWellChart::setVertexOBO(float x, float y, float z){
    if(this->vertexarray==NULL)
        this->vertexarray = new osg::Vec3Array;
    this->vertexarray->push_back(osg::Vec3(x,y,z));
}
void SingleWellChart::setTexCoordArrayOBO(float x, float y){
    if(this->texcoordarray==NULL)
        this->texcoordarray = new osg::Vec2Array;
    this->texcoordarray->push_back(osg::Vec2(x,y));
}
//按照已有的顶点、图片数据画出来几何体
void SingleWellChart::drawGeode(){

    //创建一个几何体对象
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

    //设置顶点数据
    geom->setVertexArray(this->vertexarray.get());

    //添加图元，绘图基元为多边形
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,0,this->vertexarray->getNumElements()));

    geom->setTexCoordArray(0,this->texcoordarray);



    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage(this->getImage());
    texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
    texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);


    geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,texture);

    //设置渲染优先级------级别理论上来讲 比 背景的node 靠前就行，没设置过的是-1.
    //此处设置优先级为了防止剖面图在井后面绘制，被井的颜色覆盖

    geom->getOrCreateStateSet()->setRenderBinDetails(-2, "RenderBin");
    geode->addDrawable(geom.get());
}
