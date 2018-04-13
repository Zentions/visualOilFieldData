#ifndef SINGLEWELLCHART_H
#define SINGLEWELLCHART_H
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


class SingleWellChart
{
public:
    SingleWellChart();
    //获得数据
    osg::ref_ptr<osg::Image> getImage(){return this->image;}
    osg::ref_ptr<osg::Geode> getGeode(){drawGeode(); return this->geode;}
    osg::ref_ptr<osg::Vec3Array> getVertexArray(){ return this->vertexarray;}
    osg::ref_ptr<osg::Vec2Array> getTexCoordArray(){ return this->texcoordarray;}
    QString getName(){return this->name;}
    //设置数据
    void setVertexArray(osg::ref_ptr<osg::Vec3Array> ver){this->vertexarray = ver;}
    void setVertexArraybyURL(QString filename,double TotalLength);

    //设置顶点数据 ONE BY ONE
    void setVertexOBO(float x,float y,float z);

    void setImage(osg::ref_ptr<osg::Image> ima){ this->image = ima;}
    void setImagebyURL(QString filename);
    void setTotallength(int totallength){this->totallength = totallength;}
    void setName(QString name){this->name = name;}
    void setLength(int length){this->length = length;}
    void setHeight(int height){this->height = height;}
    void setProportion(int proportion){this->proportion = proportion;}

    void setTexCoordArray(osg::Vec2Array *ta){this->texcoordarray = ta;}
    void setTexCoordArrayOBO(float x,float y);
    void drawGeode();
    void setPos(osg::Vec3 pos){this->pos = pos;}
    void saveTo(QString);
private:
    osg::ref_ptr<osg::Vec3Array> vertexarray;
    osg::ref_ptr<osg::Geode> geode;
    osg::ref_ptr<osg::Image> image;
    osg::ref_ptr<osgText::Text> text;
    osg::ref_ptr<osg::Vec2Array> texcoordarray;
    QString name;
    int length;
    int height;
    int totallength;
    double proportion;
    osg::Vec3 pos;
};

#endif // SINGLEWELLCHART_H
