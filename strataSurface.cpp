#include "strataSurface.h"
//#include "tex.h"

StrataSurface::StrataSurface()
{
    this->geometry    = NULL;
    this->vertexarray = NULL;
    this->transparency= 0;
    this->position = -1;

    this->colorSetList = new QList<QColor*>;
    this->propertylist  = new QList<int *>;
    this->propertynamelist = new QStringList;

//    this->deepcolor = Qt::magenta;
//    this->lightcolor = Qt::red;

    //初始化tin面的颜色数组
    this->default_color = new osg::Vec4Array();
    //TIN面初始色为彩虹七色 从上到下分别为 红 橙 黄 绿 青 蓝 紫
    this->default_color->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
    this->default_color->push_back(osg::Vec4(1.0f,0.5f,0.0f,1.0f));
    this->default_color->push_back(osg::Vec4(1.0f,1.0f,0.0f,1.0f));
    this->default_color->push_back(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
    this->default_color->push_back(osg::Vec4(0.0f,1.0f,1.0f,1.0f));
    this->default_color->push_back(osg::Vec4(0.0f,0.0f,1.0f,1.0f));
    this->default_color->push_back(osg::Vec4(0.5f,0.0f,1.0f,1.0f));
}

void StrataSurface::setProData(int *p,QString name){
    this->propertylist->append(p);
    this->propertynamelist->append(name);

    //添加属性的同时生成一种配色方案
    QColor *colorSet = new QColor[2];
    colorSet[0] = Qt::magenta;
    colorSet[1] = Qt::red;
    this->colorSetList->append(colorSet);

}
//一次添加一个顶点，使用此函数是要注意添加顺序，按照三角带图元顺序添加
void StrataSurface::setVertexOBO(float x, float y, float z){
    if(this->vertexarray==NULL)
        this->vertexarray = new osg::Vec3Array;
    this->vertexarray->push_back(osg::Vec3(x,y,z));
}
//按照路径读取坐标
//void StrataSurface::setVertexArraybyURL(QString filename){
//    if(filename.isEmpty())
//    {
//        return ;
//    }
//    //读取文件属性
//    int m,n,linecounter;
//    //读取坐标值
//    double x,y,z;

//    //读文件获得坐标
//    QFile *file = new QFile(filename);

//    QFileInfo fileInfo = QFileInfo(filename);
//    this->name = fileInfo.baseName();

//    if(!file->open(QIODevice::ReadOnly|QIODevice::Text))
//    {
//        return;
//    }
//    linecounter = 0;
//    while(!file->atEnd())
//    {
//        linecounter++;

//        QByteArray line = file->readLine();
//        QString str(line);
//        QStringList list=str.split(" ");

//        //跳过文件中的空行
//        if(list.size()==1)
//            continue;

//        if(linecounter==2){
//            m = list[0].toInt();
//            n = list[1].toInt();
//            this->size = n;
//            this->a[0] = new int[n];
//            this->a[1] = new int[n];
//            this->a[2] = new int[n];
//        }
//        else if(linecounter>2&&linecounter<=2+m){
//                  x = list[1].toDouble();
//                  y = list[2].toDouble();
//                  z = list[3].toDouble();

//                  Tin::setVertexOBO(x,y,z);
//    }
//        else if(linecounter>2+m&&linecounter<=2+m+n){

//            int i = list[0].toInt();
//            this->a[0][i] = list[1].toInt();
//            this->a[1][i] = list[2].toInt();
//            this->a[2][i] = list[3].toInt();
//    }

//    }
//    file->close();

//}
void StrataSurface::setTrianglePoint(int* a[3])
{
    this->trianglePoint[0] = a[0];
    this->trianglePoint[1] = a[1];
    this->trianglePoint[2] = a[2];
}

void StrataSurface::setTexCoordArrayOBO(float x, float y){
    if(this->texcoordarray==NULL)
        this->texcoordarray = new osg::Vec2Array;
    this->texcoordarray->push_back(osg::Vec2(x,y));
}
//按照已有的顶点、图片数据画出来几何体
void StrataSurface::createGeometry(){
    //创建几何体
    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
    //设置顶点数组
    geometry->setVertexArray(this->vertexarray);


    for(int i=0;i<this->triangleNum;i++){
        //创建三角形顶点索引数组，指定绘图基元为三角形，注意添加顺序
        osg::ref_ptr<osg::DrawElementsUInt> triangle3 = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES,0);


        //添加数据
        triangle3->push_back(trianglePoint[0][i]);
        triangle3->push_back(trianglePoint[1][i]);
        triangle3->push_back(trianglePoint[2][i]);

        //添加到几何体
        geometry->addPrimitiveSet(triangle3.get());
    }


    // sial for the surface
    osg::ref_ptr<osg::StateSet> stateset = geometry->getOrCreateStateSet();

  stateset->setRenderBinDetails(MARK_TYPE_STRATASURFACE, "RenderBin");
//    stateset->setRenderBinDetails(-3, "RenderBin");

    this->geometry = geometry;
}
//设置材质
void StrataSurface::setMaterial()
{
    // set material for the surface
    osg::ref_ptr<osg::StateSet> astateset = this->geometry->getOrCreateStateSet();

    //设置材质 在光照条件下 使得地层面显示出起伏的感觉

    osg::Vec4 color = osg::Vec4(1.0,1.0,1.0,1.0);

    //自动生成法线
    osgUtil::SmoothingVisitor::smooth(*geometry);

    osg::ref_ptr<osg::Material> aMaterial = new osg::Material();

    //设置环境光
    aMaterial->setAmbient(osg::Material::FRONT_AND_BACK, color);
    //设置漫反射光
    aMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, color);
    //设置镜面反射光
    aMaterial->setSpecular(osg::Material::FRONT_AND_BACK, color);
    //设置光泽度
    aMaterial->setShininess(osg::Material::FRONT_AND_BACK, 10.0f);

    //设置颜色显示模式 此模式下顶点的颜色会以设定的环境光的颜色展示出来
    aMaterial->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);


    astateset->setAttribute(aMaterial);


}
//按照已有的顶点、图片数据画出来文字
void StrataSurface::createText(){
    if(this->geometry==NULL)
        this->createGeometry();
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
    text->setText(pixname.toStdString(), osgText::String::ENCODING_UTF8);
    text->setFont("simkai.ttf");//设置中文字体
    text->setColor(osg::Vec4(0.f,0.f,0.f,1.0f));

    this->text = text;
}
//给几何体设定纹理坐标
void StrataSurface::setTexCoordArray(){
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
void  StrataSurface::setSingleColor(osg::Vec4 color){
    this->singleColor = color;

}

//设置地层颜色（渐变示例）
void StrataSurface::setPointSampleColor(){
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

       uv.set(c, 0.f,0.f,0.5f);
        tc->push_back(uv);
    }

    geo->setColorArray(tc);
    geo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
}
//设置地层颜色（单色）
void StrataSurface::setPointSingleColor(int count){
    //归一化数组处理
    osg::ref_ptr<osg::Geometry> geo = this->geometry;

    osg::Vec4 uv = this->default_color->operator [](count%7);

    //计算纹理坐标，把归一化的顶点数组给几何体
    osg::ref_ptr<osg::Vec4Array> tc = new osg::Vec4Array;
        tc->push_back(uv);

    this->colorarray = tc;

    geo->setColorArray(tc);

    geo->setColorBinding(osg::Geometry::BIND_OVERALL);

    this->singleColor = uv;
}
//按属性的位置赋色
void StrataSurface::setByProPosition(int position){
    if(position>=0){
    int *pro = this->propertylist->at(position);

    this->position = position;

    //赋色类型 0为点赋色 1为面赋色
    if(pro[1]==0)
    setPointGradientColor(pro);
    else
     setFaceColor(pro);
    }
    //position 为-1 地层面为单色
    else{

        //归一化数组处理
        osg::ref_ptr<osg::Geometry> geo = this->geometry;

        //计算纹理坐标，把归一化的顶点数组给几何体
        osg::ref_ptr<osg::Vec4Array> tc = new osg::Vec4Array;
            tc->push_back(this->singleColor);

        this->colorarray = tc;

        geo->setColorArray(tc);

        geo->setColorBinding(osg::Geometry::BIND_OVERALL);
    }

}
//设置地层颜色（渐变）
void StrataSurface::setPointGradientColor(int *pro){
    //按属性计算出颜色
    osg::ref_ptr<osg::Vec4Array> colorarray = getColorarrayByPro(pro);

    this->colorarray = colorarray;

    geometry->setColorArray(colorarray);
    geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

}

void StrataSurface::setFaceColor(int *pro){
    //按属性计算出颜色
     osg::ref_ptr<osg::Vec4Array> colorarray = getColorarrayByPro(pro);

     this->colorarray = colorarray;

     geometry->setColorArray(colorarray);
     geometry->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);


}
//按属性计算颜色
osg::ref_ptr<osg::Vec4Array> StrataSurface::getColorarrayByPro(int *pro){

    QColor * colorset = this->colorSetList->at(position);

    QColor deepColor = colorset[0];
    QColor lightColor= colorset[1];


    osg::ref_ptr<osg::Vec4Array> colorarray = new osg::Vec4Array();

    //获取颜色 HSV 值 利用HSV值渐变实现颜色渐变

    int sh = deepColor.hue();
    int ss = deepColor.saturation();
    int sv = deepColor.value();

    int dh = lightColor.hue() - sh;
    int ds = lightColor.saturation() - ss;
    int dv = lightColor.value() - sv;

    QColor temp;

//归一化属性  将归一化的值赋给颜色数组
    for(int i=4;i<pro[0];i++){

        float c = ((float)(pro[i]-pro[2]))/(pro[3]-pro[2]);

        temp.setHsv(sh+dh*c,ss+ds*c,sv+dv*c);

        temp.convertTo(QColor::Rgb);

        colorarray->push_back(osg::Vec4(temp.redF(),temp.greenF(),temp.blueF(),1.0f));
    }
    return colorarray;

}

void StrataSurface::setColorSet(){
    if(!this->colorSetList->isEmpty()){
    //通过自定义的对话框选择颜色
    ColorSetDialog colorsetdialog;
    QColor * colorset = new QColor [2];

    colorsetdialog.exec();

    colorset = colorsetdialog.getColorset();

    this->colorSetList->operator [](this->position) = colorset;

//    this->deepcolor = colorset[0];
//    this->lightcolor = colorset[1];

    setByProPosition(this->position);
    }


}
//自定义对话框设置属性
void StrataSurface::choseProperty(){
    if(!this->propertynamelist->isEmpty()){
    PropertySetDialog dlg;
    dlg.getPropertyData(*this->propertynamelist);
    dlg.exec();
    int choice = dlg.getchoice();
    if(choice!=-1)
    setByProPosition(choice);
    }
}

QString StrataSurface::getName()
{
    return name;
}
//设置地层半透明
void StrataSurface::setHalfTransparency(bool isTransparent){

        osg::ref_ptr<osg::StateSet> aStateSet = this->geometry->getOrCreateStateSet();
        osg::Material* mat = dynamic_cast<osg::Material*>(aStateSet->getAttribute(osg::StateAttribute::MATERIAL));

//        //漫发射光
//        mat->setDiffuse(osg::Material::FRONT_AND_BACK,osg::Vec4(1.0,0.0,0.0,isTransparent?0.5f:0.8f));
//        //环境光
//        mat->setAmbient(osg::Material::FRONT_AND_BACK,osg::Vec4(1.0,0.0,0.0,isTransparent?0.5f:0.8f));
//        //设置镜面反射光
//        mat->setSpecular(osg::Material::FRONT_AND_BACK,osg::Vec4(1.0,0.0,0.0,isTransparent?0.5f:0.8f));

//        //设置材质的混合光颜色
//        mat->setTransparency(osg::Material::FRONT_AND_BACK,isTransparent?0.5f:0.8f);

//        aStateSet->setAttributeAndModes(mat,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
//        aStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

        if(isTransparent)
        {
            mat->setAlpha(osg::Material::FRONT_AND_BACK,0.5f);
            //融合
            aStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
            aStateSet->setMode(GL_BLEND,osg::StateAttribute::ON);
            //融合函数
            osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();
            blendFunc->setSource(osg::BlendFunc::SRC_ALPHA);
            blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
//            blendFunc->setSource(osg::BlendFunc::DST_ALPHA);
//            blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_DST_ALPHA);
            aStateSet->setAttributeAndModes(blendFunc, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);

            aStateSet->setAttributeAndModes(mat,osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);
        setTransparency(50);
        }
        else
        {
            mat->setAlpha(osg::Material::FRONT_AND_BACK,0.0f);
            //融合
            aStateSet->setRenderingHint(osg::StateSet::DEFAULT_BIN);
            aStateSet->setMode(GL_BLEND,osg::StateAttribute::OFF);
            aStateSet->setAttributeAndModes(mat,osg::StateAttribute::OFF);
            setTransparency(0);
        }



}
//设置地层透明度 0~100
void StrataSurface::setTransparency(float transparency){
        this->transparency=transparency;

    osg::ref_ptr<osg::Vec4Array> colorarray = new osg::Vec4Array();
    osg::ref_ptr<osg::Vec4Array> cla =  this->colorarray;
    for(int i=0;i<cla->size();i++){
    osg::Vec4 &tem =  cla->operator [](i);

    colorarray->push_back(osg::Vec4(tem.x(),tem.y(),tem.z(),(100.0-(float)transparency)/100.0));

    }
    osg::Geometry::AttributeBinding colorbinding  = this->geometry->getColorBinding();

    this->geometry->setColorArray(colorarray);
    this->geometry->setColorBinding(colorbinding);

    this->colorarray = colorarray;
}
//设置地层透明
void StrataSurface::setTransparent(){
    osg::ref_ptr<osg::StateSet> aStateSet = this->geometry->getOrCreateStateSet();
    osg::Material* mat = dynamic_cast<osg::Material*>(aStateSet->getAttribute(osg::StateAttribute::MATERIAL));

    mat->setAlpha(osg::Material::FRONT_AND_BACK,1-this->transparency);
    //融合
    aStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    aStateSet->setMode(GL_BLEND,osg::StateAttribute::ON);
    //融合函数
    osg::ref_ptr<osg::BlendFunc> blendFunc = new osg::BlendFunc();
    blendFunc->setSource(osg::BlendFunc::SRC_ALPHA);
    blendFunc->setDestination(osg::BlendFunc::ONE_MINUS_SRC_ALPHA);
    aStateSet->setAttributeAndModes(blendFunc, osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);

    aStateSet->setAttributeAndModes(mat,osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE);
    //取消深度测试
    aStateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
}
float StrataSurface::getTransparency()
{
    return this->transparency;
}

void StrataSurface::initStrataSurface()
{
    createGeometry();
    setMaterial();
    createText();
    //setHalfTransparency(false);
//    setTransparent();
    //setPointSingleColor(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
}
osg::Vec4 StrataSurface::getSingleColor()
{
    return this->singleColor;
}
void StrataSurface::saveTo(QString path)
{
    QFile file(path+"/"+this->getName());
    QTextStream stream(&file);

    if(!file.open(QIODevice::WriteOnly))
    {
        return ;
    }

    stream<<"name "<<this->getName()<<endl;
    stream<<"color "<<this->getSingleColor().r()<<" "<<this->getSingleColor().g()<<" "<<this->getSingleColor().b()<<" "<<this->getSingleColor().w()<<endl;
    stream<<"transparency "<<this->getTransparency()<<endl;
    stream<<"position "<<this->getposition()<<endl;

    //存储点
    stream<<"point "<<this->vertexarray->size()<<" begin"<<endl;
    osg::Vec3 point;
    for(int i=0;i<this->vertexarray->size();i++)
    {
        point = this->vertexarray->at(i);
        stream<<i<<" "<<point.x()<<" "<<point.y()<<" "<<point.z()<<endl;
    }
    stream<<"point "<<" end"<<endl;
    osg::ref_ptr<osg::DrawElements> triangle;
    //存储三角形
    stream<<"triangle "<<this->triangleNum<<" begin"<<endl;
    for(int i=0;i<this->triangleNum;i++)
    {
        triangle = this->geometry->getPrimitiveSet(i)->getDrawElements();
        stream<<i<<" "<<triangle->getElement(0)<<" "<<triangle->getElement(1)<<" "<<triangle->getElement(2)<<endl;
    }
    stream<<"triangle "<<" end"<<endl;
    //存储属性
    stream<<"property "<<this->propertylist->size()<<" begin"<<endl;
    for(int i=0;i<this->propertylist->size();i++){
        int *pro = this->propertylist->at(i);
        stream<<this->propertynamelist->at(i)<<" "<<pro[0]<<endl;
        for(int j=0;j<pro[0];j++)
        {
            stream<<pro[j]<<endl;
        }

    }
    stream<<"property "<<" end"<<endl;
    //存储配色
    stream<<"colorset "<<this->colorSetList->size()<<" begin"<<endl;
    for(int i=0;i<this->colorSetList->size();i++){
        QColor * colorset = this->colorSetList->at(i);
        stream<<colorset[0].red()<<" "<<colorset[0].green()<<" "<<colorset[0].blue()<<" "<<colorset[0].alpha()<<endl;
        stream<<colorset[1].red()<<" "<<colorset[1].green()<<" "<<colorset[1].blue()<<" "<<colorset[1].alpha()<<endl;
    }
    stream<<"colorset "<<" end"<<endl;


    file.close();
}
