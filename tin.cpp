#include "tin.h"
//#include "tex.h"

Tin::Tin()
{
    this->geometry    = NULL;
    this->vertexarray = NULL;
}
//一次添加一个顶点，使用此函数是要注意添加顺序，按照三角带图元顺序添加
void Tin::setVertexOBO(float x, float y, float z){
    if(this->vertexarray==NULL)
        this->vertexarray = new osg::Vec3Array;
    this->vertexarray->push_back(osg::Vec3(x,y,z));
}
//按照路径读取坐标
void Tin::setVertexArraybyURL(QString filename){
    if(filename.isEmpty())
    {
        return ;
    }
    //读取文件属性
    int m,n,linecounter;
    //读取坐标值
    double x,y,z;

    //读文件获得坐标
    QFile *file = new QFile(filename);

    QFileInfo fileInfo = QFileInfo(filename);
    this->name = fileInfo.baseName();

    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
    linecounter = 0;
    while(!file->atEnd())
    {
        linecounter++;

        QByteArray line = file->readLine();
        QString str(line);
        QStringList list=str.split(" ");

        //跳过文件中的空行
        if(list.size()==1)
            continue;

        if(linecounter==2){
            m = list[0].toInt();
            n = list[1].toInt();
            this->size = n;
            this->a[0] = new int[n];
            this->a[1] = new int[n];
            this->a[2] = new int[n];
        }
        else if(linecounter>2&&linecounter<=2+m){
                  x = list[1].toDouble();
                  y = list[2].toDouble();
                  z = list[3].toDouble();

                  Tin::setVertexOBO(x,y,z);
    }
        else if(linecounter>2+m&&linecounter<=2+m+n){

            int i = list[0].toInt();
            this->a[0][i] = list[1].toInt();
            this->a[1][i] = list[2].toInt();
            this->a[2][i] = list[3].toInt();
    }

    }
    file->close();

}

void Tin::setTexCoordArrayOBO(float x, float y){
    if(this->texcoordarray==NULL)
        this->texcoordarray = new osg::Vec2Array;
    this->texcoordarray->push_back(osg::Vec2(x,y));
}
//按照已有的顶点、图片数据画出来几何体
void Tin::drawGeometry(){
    //创建几何体
    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
    //设置顶点数组
    geometry->setVertexArray(this->vertexarray);


    for(int i=0;i<this->size;i++){
        //创建三角形顶点索引数组，指定绘图基元为三角形，注意添加顺序
        osg::ref_ptr<osg::DrawElementsUInt> triangle3 = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES,0);


        //添加数据
        triangle3->push_back(a[0][i]);
        triangle3->push_back(a[1][i]);
        triangle3->push_back(a[2][i]);

        //添加到几何体
        geometry->addPrimitiveSet(triangle3.get());
    }

     this->geometry = geometry;
}
//按照已有的顶点、图片数据画出来文字
void Tin::drawText(){
    if(this->geometry==NULL)
        this->drawGeometry();
    //添加Text
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    const osg::BoundingBox &box = this->getGeometry()->getBoundingBox();//获取包围盒
    float size=(box.xMax()-box.xMin())/30;
    QString pixname =this->name;
    text->setFontResolution( 1280, 1280 );
    text->setCharacterSize( size );

    text->setPosition( osg::Vec3(box.xMin()+(box.xMax()-box.xMin())/2,box.yMin()+(box.yMax()-
box.yMin())/2,box.zMax()+size)  );

    text->setAxisAlignment( osgText::Text::XZ_PLANE );
    text->setAlignment( osgText::Text::CENTER_TOP );
    text->setText(pixname.toStdString());

    this->text = text;
}
//给几何体设定纹理坐标
void Tin::setTexCoordArray(){
    //设置纹理之前要先有几何体
    osg::ref_ptr<osg::Geometry> geo = this->geometry;
    //归一化数组处理
    osg::Vec3Array* v3a = dynamic_cast<osg::Vec3Array*>(geo->getVertexArray());
    osg::ref_ptr<osg::Vec3Array> nor_vertex = new osg::Vec3Array;
        //获取包围盒
    const osg::BoundingBox &bbox = geo->getBoundingBox();

    osg::Vec3 min,max;

    if (v3a) min.set(bbox.xMin(), bbox.yMin(), bbox.zMin());
    if (v3a) max.set(bbox.xMax(), bbox.yMax(), bbox.zMax());
   for (unsigned i=0; i<geo->getVertexArray()->getNumElements(); ++i) {

        osg::Vec3 P;
        if (v3a) P.set(((*v3a)[i].x()-min.x())/(max.x()-min.x()), ((*v3a)[i].y()-min.y())/(max.y
()-min.y()), ((*v3a)[i].z()-min.z())/(max.z()-min.z()));

        nor_vertex->push_back(P);

    }

    //计算纹理坐标，把归一化的顶点数组给几何体
    v3a = nor_vertex;

    osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
    for (unsigned i=0; i<geo->getVertexArray()->getNumElements(); ++i) {

        osg::Vec3 P;

       if (v3a) P.set((*v3a)[i].x(), (*v3a)[i].y(), (*v3a)[i].z());

         osg::Vec2 uv;
       uv.set(P.x(), P.y());

        tc->push_back(uv);


        }

    geo->setTexCoordArray(0, tc);

}
void Tin::setPointColor(){
    //归一化数组处理
    osg::ref_ptr<osg::Geometry> geo = this->geometry;
    osg::Vec3Array* v3a = dynamic_cast<osg::Vec3Array*>(geo->getVertexArray());
        //获取包围盒
    const osg::BoundingBox &bbox = geo->getBoundingBox();

    float min,max,c;

   min = bbox.zMin();
   max = bbox.zMax();

    //计算纹理坐标，把归一化的顶点数组给几何体

    osg::ref_ptr<osg::Vec4Array> tc = new osg::Vec4Array;
    for (unsigned i=0; i<geo->getVertexArray()->getNumElements(); ++i) {


        //这个顶点的颜色 由高度决定
       c = ((*v3a)[i].z() - min)/(max-min);

       osg::Vec4 uv;

      //uv.set(c, 1-c,0,0.5f);
        uv.set(1.0f, 1.0f,1.0f,0.5f);

        tc->push_back(uv);


        }

    geo->setColorArray(tc);
    geo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
     qDebug()<<geometry->getColorArray();
}
void Tin::setFaceClolor(){

    osg::Vec4Array * colorarray = new osg::Vec4Array;

    for(int i=0;i<this->size;i++){

        //设置颜色
        float c = ((float)(i%4))/3.0;
        colorarray->push_back(osg::Vec4(c,0,1-c,0.5));

    }

     geometry->setColorArray(colorarray);
     geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);

     this->geometry = geometry;

}
QString Tin::getName()
{
    return name;
}
//设置地层透明
void Tin::setTransparency(bool isTransparent){


    qDebug()<<geometry->getColorArray();
        //创建颜色数组
        osg::ref_ptr<osg::Vec4Array> vc = dynamic_cast<osg::Vec4Array*>(geometry->getColorArray());
        for(int i=0;i<vc->getElementSize();i++)
        {
            (*vc)[i].set((*vc)[i].x(),(*vc)[i].y(),(*vc)[i].z(),isTransparent?0.5f:1.0f);
        }
        //设置颜色数组
        geometry->setColorArray(vc.get());
        //设置颜色数组
        geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
        this->isTransparent=isTransparent;


}
bool Tin::getTransparency()
{
    return this->isTransparent;
}
