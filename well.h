#ifndef WELL_H
#define WELL_H

#include "graphicsview.h"


#include <osg/BoundingBox>

#include<osg/Image>
#include<osg/TexGen>
#include<osg/Texture>
#include<osg/State>

#include <osg/Drawable>
#include <osg/Vec2>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Array>
#include <osg/PrimitiveSet>
#include<osgText/Text>
#include<osgText/String>
#include<osg/Node>
#include <osg/Geometry>
#include <osg/ArrayDispatchers>
#include <osg/Notify>
#include <osg/Drawable>
#include <osg/Vec2>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Array>
#include <osg/PrimitiveSet>

#include <string>
#include <vector>
#include<iostream>
#include<ostream>
#include <iomanip>
#include <fstream>
#include<cstring>
#include<list>
#include<sstream>
using namespace std;
class Well : public osg::Node
{
public:
       Well();
       void setWellData(QString);
       osg::ref_ptr<osg::Geometry> getWell()
       {
           return line;
       }
       osg::ref_ptr<osgText::Text> getText()
       {
           return text;
       }


/** start  Well  get() and set() */

       void setWellFileName(QString fileName);
       QString getWellFileName();

       void setWellName(QString name);
       QString getWellName();

       void setWellType(int type);
       int getWellType();

       void setWellPipe(osg::ref_ptr<osg::Geode>);
       osg::ref_ptr<osg::Geode>  getWellPipe();

       void setWellHeadXYZ(osg::Vec3 HeadXYZ);
       osg::Vec3  getWellHeadXYZ();

       void setWellTrace_dataNum(int num);
       int  getWellTrace_dataNum();


       void setWellTrace_dataXYZ(osg::ref_ptr<osg::Vec3Array> dataXYZ);
       osg::ref_ptr<osg::Vec3Array> getWellTrace_dataXYZ();



       void setWellTraceColor(osg::ref_ptr<osg::Vec4Array> traceColor);
       osg::ref_ptr<osg::Vec4Array>  getWellTraceColor();
//导管

       void setWellPipeConduit_dataNum(int num);
       int  getWellPipeConduit_dataNum();

       void setWellPipeConduit_dataXYZ(QVector<osg::Vec3> dataXYZ);
       QVector<osg::Vec3>  getWellPipeConduit_dataXYZ();


       void setWellPipeConduit_textureImage(osg::ref_ptr<osg::Image> image);
       osg::ref_ptr<osg::Image>  getWellPipeConduit_textureImage();
       void setAllTexture(osg::ref_ptr<osg::Geode> geode);
       int setPartTexture(osg::ref_ptr<osg::Geode> geode,float start,float end);
       void setRepeatTexture(osg::ref_ptr<osg::Geode> geode,int m);
       int setPartRepeatTexture(osg::ref_ptr<osg::Geode> geode,int num,float start,float end);
       int Find(float X);
       int setPartsTexture(osg::ref_ptr<osg::Geode> geode,float start,float end,osg::ref_ptr<osg::Image> image);
       bool CancelTexture(osg::ref_ptr<osg::Geode> geode);
/** start  Well  get() and set() */


//读取井文件数据(井迹数据+井筒数据)
           bool  readWellData();
 //绘制井名 这个要在绘制完井迹之后才能绘制
           osg::ref_ptr<osg::Geode>  drawWellName();
 //绘制井迹
           osg::ref_ptr<osg::Geode>  drawWellTrace();
 //绘制井筒
           osg::ref_ptr<osg::Geode>  drawWellPipe();
 //保存井
           void saveWell(QString path);
//用井迹数据生成对应井筒数据
           void  WellTraceToWellPipe(double);
          // bool changeMode(float start=-400,float end=-600);
           int getMode(){return mode;}
   private:
       osg::ref_ptr<osg::Geometry> line;
       osg::ref_ptr<osg::Vec3Array> v;
       osg::ref_ptr<osg::Vec4Array> c;
       osg::ref_ptr<osg::Vec3Array> h;
       osg::ref_ptr<osgText::Text> text;
       osg::ref_ptr<osg::Switch> wellSwitch;
       int lineCounter=0;
       int wellCounter=0;
       double x,y,z;
       double headx,heady,headz;
       QString wellname;
       QFileInfo fileInfo;

      // std::string                            _wellFileName;//井文件名
       QString _wellFileName;
       QString _wellName;//井名
       int _wellType;//井类型
       osg::Vec3 _wellHead_XYZ;//井头坐标
       double  _wellHeadX;
       double  _wellHeadY;
       double  _wellHeadZ;
       int _wellCount;//井的个数
       int mode = 0;//贴图模式
       float size;
       int _wellTrace_dataNum;//井迹数据点个数
       osg::ref_ptr<osg::Vec3Array> _wellTrace_dataXYZ;//井迹数据
       osg::ref_ptr<osg::Vec4Array> _wellTrace_color;//井迹颜色

       std::string  _wellPipeConduit_name;       //导管名称

       int _wellPipeConduit_dataNum;//井筒导管数据点个数
       osg::ref_ptr<osg::Geode>  _WellPipe;
       QList<osg::Texture2D*> _WellPipeTextureList;
       QVector<osg::Vec3>  _wellPipeConduit_dataXYZ;//井筒导管数据点
       osg::ref_ptr<osg::Image> _wellPipeConduit_textureImage;//井筒导管纹理映射图(.bmp)


};

#endif // WELL_H
