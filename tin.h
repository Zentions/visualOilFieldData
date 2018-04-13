#ifndef TIN_H
#define TIN_H
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
#include <osgUtil/DelaunayTriangulator>
class Tin
{
public:
    Tin();

    //获得数据
    osg::ref_ptr<osg::Geometry> getGeometry(){drawGeometry(); return this->geometry;}
    osg::ref_ptr<osg::Vec3Array> getVertexArray(){ return this->vertexarray;}
    osg::ref_ptr<osgText::Text> getText(){ drawText(); return this->text;}
    osg::ref_ptr<osg::Vec2Array> getTexCoordArray(){ return this->texcoordarray;}
    osg::ref_ptr<osg::Vec4Array> getColorArray(){ return this->colorarray;}

    //设置数据
    void setVertexArray(osg::ref_ptr<osg::Vec3Array> ver){this->vertexarray = ver;}
    void setVertexArraybyURL(QString filename);

    //设置地层颜色
    void setColorArray(osg::ref_ptr<osg::Vec4Array> col){this->colorarray = col;}

    //设置地层顶点 ONE BY ONE
    void setVertexOBO(float x,float y,float z);

    //设置地层纹理
    void setTexCoordArray(osg::Vec2Array *ta){this->texcoordarray = ta;}
    void setTexCoordArrayOBO(float x,float y);

    //设置地层透明性
    void setTransparency(bool isTransparent);
    //得到地层透明性
    bool getTransparency();

    //按点设颜色
    void setPointColor();
    //按面设颜色
    void setFaceClolor();

    QString getName();

private:

    osg::ref_ptr<osg::Vec3Array> vertexarray;
    osg::ref_ptr<osg::Vec4Array> colorarray;
    osg::ref_ptr<osg::Geometry> geometry;
    osg::ref_ptr<osgText::Text> text;
    osg::ref_ptr<osg::Vec2Array> texcoordarray;

    //存取TIN面三角形索引号
    int * a[3];
    //索引数组长度
    int size;
    QString name;
    bool isTransparent;

    void drawGeometry();
    void drawText();
    void setTexCoordArray();
};

#endif // TIN_H
