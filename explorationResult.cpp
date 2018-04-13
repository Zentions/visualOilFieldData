#include "explorationResult.h"
ExplorationResult::ExplorationResult()
{
    this->geometry    = new osg::Geometry;
    this->image       = new osg::Image;
    this->vertexarray = new osg::Vec3Array;
    this->isTransparent = false;
    this->transparency = 0;
    this->position = new QList<double *>;
    this->mode  =0;
}
//按照路径读图，并把图片名赋值给name
void ExplorationResult::setImagebyURL(QString filename){

    //setlocale(LC_ALL, "");


    this->image = osgDB::readImageFile(filename.toLocal8Bit().toStdString());


    QFileInfo fileInfo = QFileInfo(filename);
    this->fileName = fileInfo.fileName();
    this->name = fileInfo.baseName();
}
//一次添加一个顶点，使用此函数是要注意添加顺序，按照三角带图元顺序添加
void ExplorationResult::setVertexOBO(float x, float y, float z){
    if(this->vertexarray==NULL)
        this->vertexarray = new osg::Vec3Array;
    this->vertexarray->push_back(osg::Vec3(x,y,z));
}
//按照路径读取坐标
void ExplorationResult::getDatabyURL(QString filename){
    if(filename.isEmpty())
    {
        return ;
    }
//    double x,y,z;


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
//        if(list.size()==1)
//        {
//            //第一次读出来的是一个Z值
//            z=list[0].toDouble();
//            continue;
//        }

//        x=list[0].toDouble();
//        y=list[1].toDouble();

//        ExplorationResult::setVertexOBO(x,y,z);
        double *p = new double[3];
        p[0]   = list[0].toDouble();
        p[1]   = list[1].toDouble();
        p[2]   = list[2].toDouble();
        this->position->append(p);
    }

    file->close();

}
void ExplorationResult::changeMode(int mode){
    this->vertexarray = new osg::Vec3Array;
    //移除原先的图元，不然会产生错误的几何体
    this->geometry->removePrimitiveSet(0);
    setVertexArrayByMode(mode);
    createGeometry();
    createText();
    setTransparency(this->transparency);
}
void ExplorationResult::setVertexArrayByMode(int mode){
    //模式0，不折 模式1，单向折 模式2，TIN面折
    switch (mode){
    case 0:
        setVertexArrayMode0();
        break;
    case 1:
        setVertexArrayMode1();
        break;
    case 2:
        setVertexArrayMode2();
        break;
    default:
        return;

    }
    this->mode =  mode;
}
//模式0 不折 设置顶点坐标
void ExplorationResult::setVertexArrayMode0(){
    double z=0;
    int i=0;
    for(i=4;i<this->position->size();i++){
        double *p = this->position->at(i);
        z = z+p[2];
    }
    z =  z/(this->position->size()-4);

    for(i=0;i<4;i++){
        double *p = this->position->at(i);
        double x = p[0];
        double y = p[1];
        setVertexOBO(x,y,z);
    }
    this->mode = 0;
}
//模式1 单向折 设置顶点坐标
void ExplorationResult::setVertexArrayMode1(){
    double *x,*y;
    x = new double[4];
    y = new double[4];
    int i;
    //x1 y1 左上
    //x2 y2 左下
    //x3 y3 右上
    //x4 y4 右下
    for(i=0;i<4;i++){
        double *p = this->position->at(i);
        x[i] = p[0];
        y[i] = p[1];
    }
    //边界深度最近的一口井深度相同
    double *p = this->position->at(i);
    int z1 = p[2];

    setVertexOBO(x[0],y[0],z1);
    setVertexOBO(x[1],y[1],z1);

    for(i=4;i<this->position->size();i++){
        double *p = this->position->at(i);
        double xt = p[0];
        double zt = p[2];

        setVertexOBO(xt,y[0],zt);
        setVertexOBO(xt,y[1],zt);
    }

    double *p2 = this->position->at(this->position->size()-1);
    double z2 = p2[2];

    setVertexOBO(x[2],y[2],z2);
    setVertexOBO(x[3],y[3],z2);

    this->mode = 1;
}
//模式3 TIN面折
void ExplorationResult::setVertexArrayMode2(){
    double z=0;
    int i=0;
    for(i=4;i<this->position->size();i++){
        double *p = this->position->at(i);
        z = z+p[2];
    }
    z =  z/(this->position->size()-4);

    for(i=0;i<4;i++){
        double *p = this->position->at(i);
        double x = p[0];
        double y = p[1];
        setVertexOBO(x,y,z);
    }

    for(i=4;i<this->position->size();i++){
        double *p = this->position->at(i);
        double x  = p[0];
        double y  = p[1];
        double zt = p[2];

        setVertexOBO(x,y,zt);
    }
    this->mode  = 2;

}
//按照已有的顶点、图片数据画出来几何体
void ExplorationResult::createGeometry(){

    //设置顶点数据
    geometry->setVertexArray(this->vertexarray.get());

    if(this->mode!=2)
    //添加图元，绘图基元为多边形
    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,0,this->vertexarray->getNumElements()));
    else
    {
        osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = new osgUtil::DelaunayTriangulator(this->vertexarray.get());
        dt->triangulate();
        geometry->addPrimitiveSet(dt->getTriangles());

    }

    ExplorationResult::setTexCoordArray(geometry);

    //创建颜色数组
    osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();

    //添加数据
    vc->push_back(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
   //设置颜色数组
    geometry->setColorArray(vc.get());
    //设置颜色数组
    geometry->setColorBinding(osg::Geometry::BIND_OVERALL);


     osg::StateSet* stateset =  geometry->getOrCreateStateSet();

    //load image from the file
    osg::ref_ptr<osg::Texture2D> Texture = new osg::Texture2D;
    Texture->setDataVariance(osg::Object::DYNAMIC);

    //assign the texture from the image file
    Texture->setImage(image.get());

    stateset->setTextureAttributeAndModes(0,Texture.get(),osg::StateAttribute::ON);


    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();  // blend func
    blendFunc->setSource(osg::BlendFunc::SRC_ALPHA);
    blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
//  设置目标颜色的alpha值和源颜色的 alpha值 的取值
//    blendFunc->setSource(osg::BlendFunc::DST_ALPHA);
//    blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_DST_ALPHA);

    stateset->setAttributeAndModes( blendFunc );
//  stateset->setRenderingHint(osg::StateSet::OPAQUE_BIN);



//    stateset->setRenderBinDetails(-1, "RenderBin");
//采用根据深度值绘制
  stateset->setRenderBinDetails(10, "DepthSortedBin");
}
//按照已有的顶点、图片数据画出来文字
void ExplorationResult::createText(){
    if(this->geometry==NULL)
        this->createGeometry();
    //添加Text
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    const osg::BoundingBox &box = this->getGeometry()->getBoundingBox();//获取包围盒
    float size=(box.xMax()-box.xMin())/25;
    QString pixname =this->name;
    //text->setFontResolution( 100, 100 );
    text->setCharacterSize( size );

    text->setColor(osg::Vec4f(0.0f, 0.0f, 0.0f, 1.0f));

   // text->setPosition( osg::Vec3( (cor[4]-X)/proH+0.5*(cor[2]-cor[0])/proH,(cor[5]-Y)/proW+(cor[1]-cor[5])/proW+size,counter)  );//暂时写死
    text->setPosition( osg::Vec3(box.xMin()+(box.xMax()-box.xMin())/2,box.yMax()+size,box.zMin() )  );//暂时写死

    text->setAxisAlignment( osgText::Text::XY_PLANE );
    text->setAlignment( osgText::Text::CENTER_TOP );

    text->setFont("simkai.ttf");//设置中文字体


    text->setText(pixname.toStdString(), osgText::String::ENCODING_UTF8);

    text->getOrCreateStateSet()->setRenderBinDetails(10, "RenderBin");

    this->text = text;
}
//给几何体设定纹理坐标
void ExplorationResult::setTexCoordArray(osg::ref_ptr<osg::Geometry> geo){


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
        if (v3a) P.set(((*v3a)[i].x()-min.x())/(max.x()-min.x()), ((*v3a)[i].y()-min.y())/(max.y()-min.y()), ((*v3a)[i].z()-min.z())/(max.z()-min.z()));

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
//设置图片半透明
void ExplorationResult::setTransparency(bool isTransparent){

        this->transparency = isTransparent?50:0;
        //创建颜色数组
        osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();

        //添加数据
        vc->push_back(osg::Vec4(1.0f,1.0f,1.0f,(isTransparent?0.5f:1.0f)));
       //设置颜色数组
        geometry->setColorArray(vc.get());
        //设置颜色数组
        geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
        this->isTransparent=isTransparent;

//        osg::StateSet* stateset =  geometry->getOrCreateStateSet();
//        if(isTransparent){
////            stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
//            stateset->setRenderBinDetails(10, "DepthSortedBin");
//        }
//        else{
////            stateset->setRenderingHint(osg::StateSet::OPAQUE_BIN);
//            stateset->setRenderBinDetails(-1, "RenderBin");
//        }
}
//设置图片透明度
void ExplorationResult::setTransparency(int transparency){

    this->transparency = transparency;
    //创建颜色数组
        osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();

        //添加数据
        vc->push_back(osg::Vec4(1.0f,1.0f,1.0f,(100-transparency)/100.0f));
       //设置颜色数组
        geometry->setColorArray(vc.get());
        //设置颜色数组
        geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
 }
void ExplorationResult::initExplorationResult(){
    //初始化勘探成果图
    setVertexArrayByMode(mode);
    createGeometry();
    createText();
    setTransparency(this->transparency);
}
void ExplorationResult::saveTo(QString path){


       QFile file(path+"/"+this->getName());
       QTextStream stream(&file);

       if(!file.open(QIODevice::WriteOnly))
       {
           return ;
       }

       stream<<"name "<<this->name<<endl;

       stream<<"picname "<<this->fileName<<endl;

       stream<<"transparency "<<this->transparency<<endl;

       stream<<"mode "<<this->mode<<endl;


       //存储点
       stream<<"point "<<this->position->size()<<" begin"<<endl;
       double *p;
       for(int i=0;i<this->position->size();i++)
       {
            p = this->position->at(i);

           stream<<i<<" "<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
       }
       stream<<"point "<<" end"<<endl;


       file.close();
}
void ExplorationResult::saveInByte(QString path){
    QFile file(path+"/"+this->getName()+".test");
    QDataStream stream(&file);

    if(!file.open(QIODevice::WriteOnly))
    {
        return ;
    }

    stream<<this->name;

    stream<<this->fileName;

    stream<<this->transparency;


    //存储点
    stream<<this->vertexarray->size();
    osg::Vec3 point;
    for(int i=0;i<this->vertexarray->size();i++)
    {
        point = this->vertexarray->at(i);
        stream<<point.x()<<point.y()<<point.z();
    }


    file.close();

}
QString ExplorationResult::getName()
{
    return this->name;
}
QString ExplorationResult::getFileName()
{
    return fileName;
}

void ExplorationResult::setName(QString name)
{
    this->name=name;
}
void ExplorationResult::setFileName(QString filename)
{
    this->fileName=filename;
}
bool ExplorationResult::isTransparency()
{
    return isTransparent;
}
int ExplorationResult::getTransparency()
{
    return transparency;
}
