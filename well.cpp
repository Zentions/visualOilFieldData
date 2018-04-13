#include "mainwindow.h"
#include "ui_mainwindow.h"
#define PI 3.14159
#define DIVNUM 72
#define FloutDIV  72.0
#include <QTextCodec>

Well::Well()
{
    line = new osg::Geometry;
    v=new osg::Vec3Array;
    c=new osg::Vec4Array;

    h = new osg::Vec3Array;
    text = new osgText::Text;


    //实例化各属性
    //_wellHead_XYZ=new osg::Vec3;//井头坐标
    _wellTrace_dataXYZ=new osg::Vec3Array;//井迹数据
    _wellTrace_color=new osg::Vec4Array;//井迹颜色

   _wellPipeConduit_textureImage = NULL;
   _wellPipeConduit_dataNum = 0;
   osg::Texture2D *_WellPipeTexture = new osg::Texture2D;

    _WellPipeTexture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
    _WellPipeTexture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR);
    _WellPipeTexture->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT);
    _WellPipeTexture->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT);
    _WellPipeTextureList.append(_WellPipeTexture);
}


//start  set() and get()

/**
 * @brief Well::setWellFileName
 * @param fileName
 */
void Well::setWellFileName(QString fileName){

    _wellFileName=fileName;
}
/**
 * @brief Well::getWellFileName
 * @return
 */
QString Well::getWellFileName(){
    return _wellFileName;
}

/**
 * @brief Well::setWellName
 * @param name
 */
void Well::setWellName(QString name){
    _wellName=name;
}
/**
 * @brief Well::getWellName
 * @return
 */
QString Well::getWellName(){
    return _wellName;
}

void Well::setWellType(int type){
    _wellType=type;
}
int  Well::getWellType(){
    return _wellType;
}

void Well::setWellHeadXYZ(osg::Vec3 HeadXYZ){

    _wellHead_XYZ=HeadXYZ;
}

osg::Vec3 Well::getWellHeadXYZ(){
    return _wellHead_XYZ;
}

void Well::setWellTrace_dataNum(int num){

    _wellTrace_dataNum=num;
}
int Well::getWellTrace_dataNum(){
    return _wellTrace_dataNum;
}

void Well::setWellTrace_dataXYZ(osg::ref_ptr<osg::Vec3Array> dataXYZ){
    _wellTrace_dataXYZ=dataXYZ;
}
osg::ref_ptr<osg::Vec3Array>  Well::getWellTrace_dataXYZ(){
    return _wellTrace_dataXYZ;
}


void Well::setWellPipe(osg::ref_ptr<osg::Geode> WellPipe){
    _WellPipe = WellPipe;
}
osg::ref_ptr<osg::Geode>  Well::getWellPipe(){
    return _WellPipe;
}
void Well::setWellTraceColor(osg::ref_ptr<osg::Vec4Array> traceColor){
    _wellTrace_color=traceColor;
}

osg::ref_ptr<osg::Vec4Array> Well::getWellTraceColor(){
    return _wellTrace_color;
}
//导管

void Well::setWellPipeConduit_dataNum(int num){
    _wellPipeConduit_dataNum=num;
}
int Well::getWellPipeConduit_dataNum(){
    return _wellPipeConduit_dataNum;
}

void Well::setWellPipeConduit_dataXYZ(QVector<osg::Vec3> dataXYZ){
    _wellPipeConduit_dataXYZ=dataXYZ;
}
QVector<osg::Vec3>  Well::getWellPipeConduit_dataXYZ(){
    return _wellPipeConduit_dataXYZ;
}

void Well::setWellPipeConduit_textureImage(osg::ref_ptr<osg::Image> image){
    _wellPipeConduit_textureImage=image;
}
osg::ref_ptr<osg::Image>  Well::getWellPipeConduit_textureImage(){
    return _wellPipeConduit_textureImage;
}



//end set() and get()



bool Well::readWellData(){
    QString fileName;
    fileName=_wellFileName;
    if(fileName.isEmpty())
    {
        return false;
    }

    QFile file(fileName);
    QString line;//读取一行的字符型数据
    QStringList strList;//一行拆分后的数据串集合
    bool headflag = false;
    double x1;
    double x2;
    double y1;
    double y2;
    double z1;
    double z2;

    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){

        //打开失败的消息提示
       // QMessageBox("打开文件失败");
    }else{

        QTextStream in(&file);

        //判断是否是标准well文件
        line=in.readLine();
        line=line.simplified();
        strList=line.split(" ");
      if(!strList.startsWith("#WELLDATA")) {
            return false;
      }

      line=in.readLine();
      line=line.simplified();
      strList=line.split(" ");
     if(strList.startsWith("#WELLNAME")){
         _wellName=strList[1];
      }
     line=in.readLine();
     line=line.simplified();
     strList=line.split(" ");
     if(strList.startsWith("#PICNAME")){
         if(strList[1]!="null")
         {
             int i = _wellFileName.lastIndexOf("/");
             QString picName = _wellFileName.mid(0,i+1)+strList[1];
             setWellPipeConduit_textureImage(osgDB::readImageFile(picName.toStdString()));
         }
      }
        while(!in.atEnd()){


            line=in.readLine();
            line=line.simplified();
            strList=line.split(" ");
           if(strList.startsWith("#WELLTRACEDATA")){
               _wellTrace_dataNum=strList[1].toInt();

                int i=0;
                while(i<_wellTrace_dataNum){
                    line=in.readLine();
                    line=line.simplified();
                    strList=line.split(" ");
                    x1=strList[0].toDouble();
                    y1=strList[1].toDouble();
                    z1=strList[2].toDouble();
                    _wellTrace_dataXYZ->push_back(osg::Vec3(x1,y1,z1));
                    if(i==0)_wellHead_XYZ = osg::Vec3(x1,y1,z1);
                    i++;
                }

           }else if(strList.startsWith("#WELLPIPEDATA")){
               _wellPipeConduit_dataNum=strList[1].toInt();

               int j=0;
               while(j<_wellPipeConduit_dataNum){

                   line=in.readLine();
                   line=line.simplified();
                   strList=line.split(" ");
                   x2=strList[0].toDouble();
                   y2=strList[1].toDouble();
                   z2=strList[2].toDouble();
                   _wellPipeConduit_dataXYZ.append(osg::Vec3(x2,y2,z2));
                   j++;
               }


           }

        }

    }
    qDebug()<<_wellHead_XYZ.z();
             return true;
}


osg::ref_ptr<osg::Geode> Well::drawWellTrace(){

    //创建一个叶节点对象
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    //创建颜色数组
    osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
    //添加数据
    vc->push_back(osg::Vec4(0.5f,0.5f,0.5f,0.5f));

             //创建一个几何体对象
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
         //设置顶点数据
    geom->setVertexArray(_wellTrace_dataXYZ.get());

         //设置颜色数组
    geom->setColorArray(vc.get());
         //设置颜色的绑定方式为单个顶点
    geom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
    geom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(2));

         //添加图元，绘图基元为三角形带
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP,0,_wellTrace_dataNum));
         //添加到叶节点
    geode->addDrawable(geom.get());
    const osg::BoundingBox &box = geode->getBoundingBox();
    size =  box.zMax()-box.zMin();
    if(_wellPipeConduit_dataNum==0)
        WellTraceToWellPipe(size/5.0);
    return geode;
}

osg::ref_ptr<osg::Geode> Well::drawWellPipe(){
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
   // _wellPipeConduit_dataXYZ.clear();
   // WellTraceToWellPipe(100.0);
    int n = _wellPipeConduit_dataXYZ.size()/72;

    for(int i=0;i<n-1;i++)
    {
        osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

        osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
        osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
        osg::Vec3 a = _wellPipeConduit_dataXYZ[72*(i+1)];
        osg::Vec3 b = _wellPipeConduit_dataXYZ[72*i];
        for(int j=0;j<72;j++)
        {
             v->push_back(_wellPipeConduit_dataXYZ[72*(i+1)+j]);
             v->push_back(_wellPipeConduit_dataXYZ[72*i+j]);
        }
         v->push_back(a);
         v->push_back(b);
         vt->push_back(osg::Vec2(0.0f,0.0f));

         geom->setVertexArray(v.get());

         osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();

         nc->push_back(osg::Vec3(0.0f,1.0f,0.0f));

         geom->setNormalArray(nc.get());
         geom->setTexCoordArray(0,vt.get());
         geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

         geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP ,0,146));
         //VBO动态修改
         geom->setUseDisplayList(false);
         geom->setUseVertexBufferObjects(true);

         geode->addDrawable(geom.get());

     }
     _WellPipe = geode;
     return geode.get();

}
osg::ref_ptr<osg::Geode> Well::drawWellName(){
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();

    osg::ref_ptr<osgText::Text> wellNameGeom = new osgText::Text();
    wellNameGeom->setCharacterSize(size/25);

    //    wellName->setPosition(osg::Vec3( (*this->wellpoint)[0] ));
      wellNameGeom->setPosition(_wellHead_XYZ);
        wellNameGeom->setAxisAlignment( osgText::Text::SCREEN );
        wellNameGeom->setAlignment( osgText::Text::CENTER_TOP );
        wellNameGeom->setText(_wellName.toStdString(), osgText::String::ENCODING_UTF8);
        wellNameGeom->setFont("simkai.ttf");//设置中文字体

        wellNameGeom->setColor(osg::Vec4(1.0f,0.0f,0.0f,1.0f));

//        osg::ref_ptr<osg::AutoTransform> at=new osg::AutoTransform();
//        //文字显示朝向
//        at->addChild(wellNameGeom.get());
//        //自动朝向屏幕
//        at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
//        at->setAutoScaleToScreen(true);
//        at->setAutoScaleTransitionWidthRatio(0.01f);
//        at->setPosition(osg::Vec3( _wellHeadX,_wellHeadY,_wellHeadZ+size+25 ));

        geode->addChild(wellNameGeom);

        return geode.get();
}
void Well::setAllTexture(osg::ref_ptr<osg::Geode> geode)
{
    _WellPipeTextureList[0]->setImage(_wellPipeConduit_textureImage);
    int n = _wellPipeConduit_dataXYZ.size()/72;
    float r = 0,rr = 0;
    for(int i =0;i<n-1;i++)//计算纹理坐标
    {
        osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
        osg::Vec2Array *vt = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
        r+=1.0/n;
        float t1 = 0;
        vt->clear();
        for(int j=0;j<73;j++)
        {

             vt->push_back(osg::Vec2(t1,r));
             vt->push_back(osg::Vec2(t1,rr));
             t1+=1.0f/73;
         }
         rr = r;

         geom->getOrCreateStateSet()->setTextureAttributeAndModes(0, _WellPipeTextureList[0]);//加载纹理

         vt->dirty();

    }
    mode++;
    if(mode==5)mode=0;

}
void Well::setRepeatTexture(osg::ref_ptr<osg::Geode> geode,int m)
{
    _WellPipeTextureList[0]->setImage(_wellPipeConduit_textureImage);
    int n = _wellPipeConduit_dataXYZ.size()/72;
    float r = 0,rr = 0;
    for(int i =0;i<n-1;i++)//计算纹理坐标
    {
        osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
        osg::Vec2Array *vt = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
        r+=m*1.0/n;
        float t1 = 0;
        vt->clear();
      //  std::cout<<vt->getElementSize()<<std::endl;
        for(int j=0;j<73;j++)
        {

             vt->push_back(osg::Vec2(t1,r));
             vt->push_back(osg::Vec2(t1,rr));
             t1+=1.0f/73;
         }
         rr = r;

         geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,_WellPipeTextureList[0] );//加载纹理

         vt->dirty();

    }
    mode++;
    if(mode==5)mode=0;
}
int Well::Find(float X)//计算深度
{
    int i = 0,j = _wellTrace_dataNum -1;
    if((X>(*_wellTrace_dataXYZ)[i].z()) ||(X<(*_wellTrace_dataXYZ)[j].z())){
         return -1;
    }
    int mid;
    while(i<j)
    {
        mid = (i+j)/2;
        osg::Vec3 ve1 = (*_wellTrace_dataXYZ)[mid];
        if(X>ve1.z()) j = mid-1;
        else if(X<ve1.z())i = mid+1;
        else if(X==ve1.z()) return mid;
        if(j-i==1) return mid;
    }

}
int Well::setPartTexture(osg::ref_ptr<osg::Geode> geode,float start,float end)
{
    _WellPipeTextureList[0]->setImage(_wellPipeConduit_textureImage);
    int n = Find(start);
    int m = Find(end);
    if(n==-1 || m==-1){//计算出错返回-1
        return -1;
    }else {//计算正确返回0
        float r = 0,rr = 0;
        for(int i =0;i<_wellTrace_dataNum-1;i++)//计算纹理坐标
        {
            osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
            osg::Vec2Array *vt = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
            vt->clear();
            if(i>=n && i<=m){
                r+=1.0/(m-n);
                float t1 = 0;

                for(int j=0;j<73;j++)
                {

                   vt->push_back(osg::Vec2(t1,r));
                   vt->push_back(osg::Vec2(t1,rr));
                   t1+=1.0f/73;
                 }
                 rr = r;
                 geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,_WellPipeTextureList[0]);//加载纹理

            }else{
                 geom->getOrCreateStateSet()->removeTextureAttribute(0,_WellPipeTextureList[0]);//去掉纹理
            }
            vt->dirty();
        }
        mode++;
        if(mode==5)mode=0;
        return 0;
    }

}
int Well::setPartRepeatTexture(osg::ref_ptr<osg::Geode> geode,int num,float start,float end)
{
    _WellPipeTextureList[0]->setImage(_wellPipeConduit_textureImage);
    int n = Find(start);
    int m = Find(end);
    if(n==-1 || m==-1){//计算出错返回-1
        return -1;
    }else {//计算正确返回0
        float r = 0,rr = 0;
        for(int i =0;i<_wellTrace_dataNum-1;i++)//计算纹理坐标
        {
            osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
            osg::Vec2Array *vt = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
            vt->clear();
            if(i>=n && i<=m){
                r+=num*1.0/(m-n);
                float t1 = 0;

                for(int j=0;j<73;j++)
                {

                   vt->push_back(osg::Vec2(t1,r));
                   vt->push_back(osg::Vec2(t1,rr));
                   t1+=1.0f/73;
                 }
                 rr = r;
                 geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,_WellPipeTextureList[0]);//加载纹理

            }else{
               geom->getOrCreateStateSet()->removeTextureAttribute(0,_WellPipeTextureList[0]);//去掉纹理
            }
            vt->dirty();
        }
        mode++;
        if(mode==5)mode=0;
        return 0;
    }
}
int Well::setPartsTexture(osg::ref_ptr<osg::Geode> geode,float start,float end,osg::ref_ptr<osg::Image> image)
{
    osg::Texture2D *_WellPipeTexture = new osg::Texture2D;
    _WellPipeTexture->setImage(image);
    _WellPipeTexture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
    _WellPipeTexture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR);
    _WellPipeTexture->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT);
    _WellPipeTexture->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT);
    _WellPipeTextureList.append(_WellPipeTexture);
    int n = Find(start);
    int m = Find(end);
    if(n==-1 || m==-1){//计算出错返回-1
        return -1;
    }else {//计算正确返回0
        float r = 0,rr = 0;
        for(int i =n;i<m;i++)//计算纹理坐标
        {
            osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
            osg::Vec2Array *vt = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));
            vt->clear();
            r+=1.0/(m-n);
            float t1 = 0;

            for(int j=0;j<73;j++)
            {

                 vt->push_back(osg::Vec2(t1,r));
                 vt->push_back(osg::Vec2(t1,rr));
                 t1+=1.0f/73;
            }
            rr = r;
            geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,_WellPipeTexture);//加载纹理
            vt->dirty();
        }
        mode++;
        if(mode==5)mode=0;
        return 0;
    }

}
bool Well::CancelTexture(osg::ref_ptr<osg::Geode> geode){
    if(geode==NULL) return false;
    for(int i =0;i<_wellTrace_dataNum-1;i++)//计算纹理坐标
    {
        osg::Geometry* geom = dynamic_cast<osg::Geometry*>(geode->getDrawable(i));
        for(int j=0;j<_WellPipeTextureList.size();j++){
            geom->getOrCreateStateSet()->removeTextureAttribute(0,_WellPipeTextureList[j]);//去掉纹理
        }

    }
    return true;
}
void Well::WellTraceToWellPipe(double diameter)
{
   if(_wellTrace_dataXYZ->size()<=0) return;
   else
   {
       for(int i=0;i<_wellTrace_dataNum;i++)
       {
           for(int j=0;j<72;j++)
           {
               osg::Vec3 temp;
               temp.x() = (*_wellTrace_dataXYZ)[i].x()+diameter*cos(2*PI/72.0*j);
               temp.y() = (*_wellTrace_dataXYZ)[i].y()+diameter*sin(2*PI/72.0*j);
               temp.z() = (*_wellTrace_dataXYZ)[i].z();
               _wellPipeConduit_dataXYZ.append(temp);
           }
       }
   }
   _wellPipeConduit_dataNum = _wellTrace_dataNum*72;

}

void Well::setWellData(QString name)
{

}
void Well::saveWell(QString path)
{
   QString picName = "null";
   QTextCodec *code = QTextCodec::codecForName("GB2312");
   if(_wellPipeConduit_textureImage!=NULL)
   {
       QString picPath = QString::fromStdString(_wellPipeConduit_textureImage->getFileName());
       int i = picPath.lastIndexOf("/");
       picName = picPath.mid(i+1);
       std::string name = code->fromUnicode(path+"//"+picName).data();
       osgDB::writeImageFile(*_wellPipeConduit_textureImage,name);
   }
   qDebug()<<picName;
   string absolutePath = code->fromUnicode(path+"//"+_wellName+".wells").data();
   cout<<absolutePath<<endl;
   ofstream stream;
   stream.open(absolutePath.c_str());
   if(!stream.is_open())
   {
       qDebug()<<"wrong";
       return ;
   }
   qDebug()<<"success";
   stream<<"#WELLDATA"<<endl;
   stream<<"#WELLNAME "<<_wellName.toStdString()<<endl;
   stream<<"#PICNAME "<<picName.toStdString()<<endl;
   stream<<"#WELLTRACEDATA "<<_wellTrace_dataNum<<endl;
   for(int i=0;i<_wellTrace_dataNum;i++)
   {
       double x,y,z;
       x = (*_wellTrace_dataXYZ)[i].x();
       y = (*_wellTrace_dataXYZ)[i].y();
       z = (*_wellTrace_dataXYZ)[i].z();
       QString sx = QString::number(x,'f',2);
       QString sy = QString::number(y,'f',2);
       QString sz = QString::number(z,'f',2);
       stream<<sx.toStdString()<<"     "<<sy.toStdString()<<"     "<<sz.toStdString()<<endl;
   }
   stream<<"#WELLPIPEDATA " <<_wellPipeConduit_dataNum<<endl;
   for(int i=0;i<_wellPipeConduit_dataNum;i++)
   {
       osg::Vec3 temp = _wellPipeConduit_dataXYZ.at(i);

       QString sx = QString::number(temp.x(),'f',2);
       QString sy = QString::number(temp.y(),'f',2);
       QString sz = QString::number(temp.z(),'f',2);
       stream<<sx.toStdString()<<"     "<<sy.toStdString()<<"     "<<sz.toStdString()<<endl;
   }
   qDebug()<<"end";
   stream.close();
}

