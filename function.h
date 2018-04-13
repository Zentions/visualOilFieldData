#ifndef FUNCTION
#define FUNCTION

#endif // FUNCTION
#include <osg/ref_ptr>
#include <osg/DrawPixels>
#include <osgDB/ReadFile>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/TexGen>
#include <osg/TexEnv>
#include <osg/Geometry>
#include <osgText/Text>
#include <osg/LineWidth>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
//二维贴图
void createTexture2D(osg::StateSet &s,osg::ref_ptr<osg::Image> image);
//添加连井剖面
osg::ref_ptr<osg::Geode> getProfileGeode(QString filename);
osg::Vec2 coordinateTrans(osg::ref_ptr<osg::Image> image,double realX,double realY);

