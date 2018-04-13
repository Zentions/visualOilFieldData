#ifndef PROFILE_H
#define PROFILE_H
#include <QtWidgets/QGraphicsScene>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtGui/QPaintEngine>
#include <QtOpenGL/QGLWidget>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/AnimationPath>
#include <osg/ClipNode>
#include <osg/MatrixTransform>
#include <osg/PolygonMode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/TexGen>
#include <osg/TextureCubeMap>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/StateSetManipulator>
#include <osg/BlendFunc>

#include "common.h"

class Profile
{
public:
    Profile();

    //获得数据
    osg::ref_ptr<osg::Image> getImage(){return this->image;}
    osg::ref_ptr<osg::Geometry> getGeometry(){createGeometry(); return this->geometry;}
    osg::ref_ptr<osg::Vec3Array> getVertexArray(){ return this->vertexarray;}
    osg::ref_ptr<osgText::Text> getText(){ createText(); return this->text;}
    osg::ref_ptr<osg::Vec2Array> getTexCoordArray(){ return this->texcoordarray;}

    //设置数据
    void setVertexArray(osg::ref_ptr<osg::Vec3Array> ver){this->vertexarray = ver;}
    void setVertexArraybyURL(QString filename);

    //设置顶点数据 ONE BY ONE
    void setVertexOBO(float x,float y,float z);

    void setImage(osg::ref_ptr<osg::Image> ima){ this->image = ima;}
    void setImagebyURL(QString filename);

    void setTexCoordArray(osg::Vec2Array *ta){this->texcoordarray = ta;}
    void setTexCoordArrayOBO(float x,float y);

    //测试用函数 可删除
    void setTexCoordArray();

    void setName(QString);
    void setFileName(QString);
    QString getName();
    QString getFileName();

    void setTransparency(bool);
    bool isTransparency();
    void setTransparency(int);
    int getTransparency();

    void initProfile();

    //保存工程
    void saveTo(QString);

private:
    osg::ref_ptr<osg::Vec3Array> vertexarray;
    osg::ref_ptr<osg::Geometry> geometry;
    osg::ref_ptr<osg::Image> image;
    osg::ref_ptr<osgText::Text> text;
    osg::ref_ptr<osg::Vec2Array> texcoordarray;
    QString name; //不包含文件后缀名
    QString fileName;//包含文件后缀名
    bool isTransparent;
    int transparency;

    void createGeometry();
    void createText();
    void setTexCoordArray(osg::ref_ptr<osg::Geometry> geo);
};

#endif // PROFILE_H
