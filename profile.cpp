#include "profile.h"
Profile::Profile()
{
    this->geometry    = new osg::Geometry;
    this->image       = new osg::Image;
    this->vertexarray = new osg::Vec3Array ;
    this->texcoordarray = new osg::Vec2Array;
    isTransparent = false;
    this->transparency = 0;
}
void Profile::setImagebyURL(QString filename){
    //按照路径读图，并把图片名赋值给name

    this->image = osgDB::readImageFile(filename.toLocal8Bit().toStdString());
    QFileInfo fileInfo = QFileInfo(filename);
    this->fileName = fileInfo.fileName();
    this->name = fileInfo.baseName();
}
//一次添加一个顶点，使用此函数是要注意添加顺序，按照三角带图元顺序添加
void Profile::setVertexOBO(float x, float y, float z){
    if(this->vertexarray==NULL)
        this->vertexarray = new osg::Vec3Array;
    this->vertexarray->push_back(osg::Vec3(x,y,z));
}
//按照路径读取坐标
void Profile::setVertexArraybyURL(QString filename){
    if(filename.isEmpty())
    {
        return ;
    }
    double x,y,zl,zh;
    int flag = 0;
    osg::Vec2Array* temp = new  osg::Vec2Array;

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
        QStringList list=str.split(",");
        //第一次读出来的是图片的两个Z值，有且只有两个Z值
        if(flag==0){
                   flag=1;
                   zh=list[0].toDouble();
                   zl=list[1].toDouble();
                   continue;
        }

        if(list.size()==2){
        x=list[0].toDouble();
        y=list[1].toDouble();

        Profile::setVertexOBO(x,y,zl);
        Profile::setVertexOBO(x,y,zh);
        }
        else{
            temp->push_back(osg::Vec2(list[0].toDouble(),0));
            temp->push_back(osg::Vec2(list[0].toDouble(),1));
        }
    }
    int n = temp->getNumElements();
    for(int i=0;i<n;i=i+2){
        this->setTexCoordArrayOBO((*temp)[i].x()/(*temp)[n-1].x(),0);
        this->setTexCoordArrayOBO((*temp)[i].x()/(*temp)[n-1].x(),1);
    }
    file->close();


}
void Profile::setTexCoordArrayOBO(float x, float y){
    if(this->texcoordarray==NULL)
        this->texcoordarray = new osg::Vec2Array;
    this->texcoordarray->push_back(osg::Vec2(x,y));
}
void Profile::setTexCoordArray(){
    long double sum = 0;
    int size = this->vertexarray->size();
    for (int i = 4;i <=size-4;i+=2) {
        long double a = fabs((*vertexarray)[i].x() - (*vertexarray)[i-2].x());
        long double b = fabs((*vertexarray)[i].y() - (*vertexarray)[i-2].y());
            sum = sum + sqrt(a*a+b*b);
    }
    double averLen = sum/(size/2-3);
    //为图片添加两边上的点
    if((*vertexarray)[2].x()<(*vertexarray)[size-3].x())
    {
        (*vertexarray)[0].x() = (*vertexarray)[2].x() - averLen;
        (*vertexarray)[0].y() = (*vertexarray)[2].y();
        (*vertexarray)[1].x() = (*vertexarray)[2].x() - averLen;
        (*vertexarray)[1].y() = (*vertexarray)[2].y();
        (*vertexarray)[size-2].x() = (*vertexarray)[size-3].x() + averLen;
        (*vertexarray)[size-2].y() = (*vertexarray)[size-3].y();
        (*vertexarray)[size-1].x() = (*vertexarray)[size-3].x() + averLen;
        (*vertexarray)[size-1].y() = (*vertexarray)[size-3].y();
    }
    else
    {
        (*vertexarray)[0].x() = (*vertexarray)[2].x() + averLen;
        (*vertexarray)[0].y() = (*vertexarray)[2].y();
        (*vertexarray)[1].x() = (*vertexarray)[2].x() + averLen;
        (*vertexarray)[1].y() = (*vertexarray)[2].y();
        (*vertexarray)[size-2].x() = (*vertexarray)[size-3].x() - averLen;
        (*vertexarray)[size-2].y() = (*vertexarray)[size-3].y();
        (*vertexarray)[size-1].x() = (*vertexarray)[size-3].x() - averLen;
        (*vertexarray)[size-1].y() = (*vertexarray)[size-3].y();
    }
    sum += (averLen*2);
   // qDebug()<<(double)sum;

    texcoordarray->push_back(osg::Vec2(0,0));
    texcoordarray->push_back(osg::Vec2(0,1));
    long double temp = 0;
    for (unsigned i=2; i<=size-4; i+=2) {

        long double a = fabs((*vertexarray)[i].x() - (*vertexarray)[i-2].x());
        long double b = fabs((*vertexarray)[i].y() - (*vertexarray)[i-2].y());
        temp = temp + sqrt(a*a+b*b);

      //  qDebug()<<(double)temp;
        texcoordarray->push_back(osg::Vec2(temp/sum,0));
        texcoordarray->push_back(osg::Vec2(temp/sum,1));
     }

    texcoordarray->push_back(osg::Vec2(1,0));
    texcoordarray->push_back(osg::Vec2(1,1));

}
//按照已有的顶点、图片数据画出来几何体
void Profile::createGeometry(){


    //设置顶点数据
    geometry->setVertexArray(this->vertexarray.get());

    //添加图元，绘图基元为多边形
    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,0,this->vertexarray->getNumElements()));

    geometry->setTexCoordArray(0,this->texcoordarray);


    osg::StateSet* stateset =  geometry->getOrCreateStateSet();


   osg::ref_ptr<osg::Texture2D> Texture = new osg::Texture2D;
   Texture->setDataVariance(osg::Object::DYNAMIC);


   Texture->setImage(image.get());

   stateset->setTextureAttributeAndModes(0,Texture.get(),osg::StateAttribute::ON);


   osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();  // blend func
   blendFunc->setSource(osg::BlendFunc::SRC_ALPHA);
   blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_SRC_ALPHA);

   stateset->setAttributeAndModes( blendFunc );

//采用根据深度值绘制
   stateset->setRenderBinDetails(10, "DepthSortedBin");


   geometry->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::ON);


}
//按照已有的顶点、图片数据画出来文字
void Profile::createText(){
    if(this->geometry==NULL)
        this->createGeometry();
    //添加Text
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    const osg::BoundingBox &box = this->getGeometry()->getBoundingBox();//获取包围盒
    float size=(box.xMax()-box.xMin())/25;
    QString pixname =this->name;
//    text->setFontResolution( 1280, 1280 );
    text->setCharacterSize( size );
    text->setColor(osg::Vec4f(0.0f, 0.0f, 0.0f, 1.0f));

    text->setPosition( osg::Vec3(box.xMin()+(box.xMax()-box.xMin())/2,box.yMin()+(box.yMax()-box.yMin())/2,box.zMax()+size)  );//暂时写死

    text->setAxisAlignment( osgText::Text::XZ_PLANE );
    text->setAlignment( osgText::Text::CENTER_TOP );
//    text->setText(pixname.toStdString());
    text->setFont("STSONG.ttf");//设置中文字体

    text->setText(pixname.toStdString(), osgText::String::ENCODING_UTF8);

//    text->getOrCreateStateSet()->setRenderBinDetails(-2, "RenderBin");

    this->text = text;
}
//给几何体设定纹理坐标
void Profile::setTexCoordArray(osg::ref_ptr<osg::Geometry> geo){


    //从顶点数组分段获得纹理分段
    osg::Vec3Array* v3a = dynamic_cast<osg::Vec3Array*>(geo->getVertexArray());

    //存储纹理分段长度 和 总长度

    long double sum=0.0,temp=0.0;

    int n = geo->getVertexArray()->getNumElements();


    for (unsigned i=1; i<n; ++i) {
        long double a = fabs((*v3a)[i].x() - (*v3a)[i-1].x());
        long double b = fabs((*v3a)[i].y() - (*v3a)[i-1].y());
            sum = sum + sqrt(a*a+b*b);
    }


    //计算纹理坐标

    osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;

    tc->push_back(osg::Vec2(0,0));

    for (unsigned i=1; i<n; ++i) {

        long double a = fabs((*v3a)[i].x() - (*v3a)[i-1].x());
        long double b = fabs((*v3a)[i].y() - (*v3a)[i-1].y());
            temp = temp + sqrt(a*a+b*b);



        osg::Vec2 uv;

        uv.set(temp/sum, i%2);

        tc->push_back(uv);

        }

    geo->setTexCoordArray(0, tc);

    }
QString Profile::getName()
{
    return name;
}
QString Profile::getFileName()
{
    return fileName;
}

void Profile::setName(QString name)
{
    this->name=name;
}
void Profile::setFileName(QString filename)
{
    this->fileName=filename;
}
//设置图片透明度
void Profile::setTransparency(int transparency){

        //创建颜色数组
        osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();

        //添加数据
        vc->push_back(osg::Vec4(1.0f,1.0f,1.0f,(100-transparency)/100.0f));
       //设置颜色数组
        geometry->setColorArray(vc.get());
        //设置颜色数组
        geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

        this->transparency = transparency;

        this->isTransparent = this->transparency>0?true:false;
 }
//设置图片半透明
void Profile::setTransparency(bool isTransparent)
{

    if(isTransparent==true)
    {
        this->transparency = 50;
        //创建颜色数组
        osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();

        //添加数据
        vc->push_back(osg::Vec4(1.0f,1.0f,1.0f,0.5f));
        //设置颜色数组
        geometry->setColorArray(vc.get());
        //设置颜色数组
        geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
        this->isTransparent=true;

    }
    else
    {
        this->transparency = 0;
        //创建颜色数组
        osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
        //添加数据
        vc->push_back(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
        //设置颜色数组
        geometry->setColorArray(vc.get());
        //设置颜色数组
        geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
        this->isTransparent=false;
    }
}
void Profile::initProfile(){
    createGeometry();
    createText();
    setTransparency(this->transparency);
}
void Profile::saveTo(QString path){
    QFile file(path+"/"+this->getName());
    QTextStream stream(&file);

    if(!file.open(QIODevice::WriteOnly))
    {
        return ;
    }

    stream<<"name "<<this->name<<endl;

    stream<<"picname "<<this->fileName<<endl;

    stream<<"transparency "<<this->transparency<<endl;


    //存储点
    stream<<"point "<<this->vertexarray->size()<<" begin"<<endl;
    osg::Vec3 point;
    for(int i=0;i<this->vertexarray->size();i++)
    {
        point = this->vertexarray->at(i);
        stream<<i<<" "<<point.x()<<" "<<point.y()<<" "<<point.z()<<endl;
    }
    stream<<"point "<<" end"<<endl;

    //存储纹理数组
    stream<<"texcoord "<<this->texcoordarray->size()<<" begin"<<endl;
    osg::Vec2 texcoord;
    for(int i=0;i<this->texcoordarray->size();i++)
    {
        texcoord = this->texcoordarray->at(i);
        stream<<i<<" "<<texcoord.x()<<" "<<texcoord.y()<<endl;
    }
    stream<<"texcoord "<<" end"<<endl;


    file.close();
}
bool Profile::isTransparency()
{
    return isTransparent;
}
int Profile::getTransparency()
{
    return transparency;
}
