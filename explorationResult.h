#ifndef EXPLORATONRESULT_H
#define EXPLORATONRESULT_H
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
#include <osgUtil/DelaunayTriangulator>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/StateSetManipulator>
#include <osg/BlendFunc>
#include <osg/Material>
#include "common.h"

class ExplorationResult
{
public:
    ExplorationResult();

    //设置图片半透明
    void setTransparency(bool);
    //设置图片透明度[0,100]
    void setTransparency(int);

    bool isTransparency();
    int getTransparency();

    //获得数据
    osg::ref_ptr<osg::Image> getImage(){return this->image;}
    osg::ref_ptr<osg::Geometry> getGeometry(){return this->geometry;}
    osg::ref_ptr<osg::Vec3Array> getVertexArray(){ return this->vertexarray;}
    osg::ref_ptr<osgText::Text> getText(){
                   return this->text;}
    int getMode(){return mode;}

    //设置数据
    void setVertexArray(osg::ref_ptr<osg::Vec3Array> ver){this->vertexarray = ver;}

    void getDatabyURL(QString filename);

    void setData(QList<double *> *data){this->position = data;}

    //按照模式从原始数据中计算顶点数据
    //模式0，不折 模式1，单向折 模式2，TIN面折
    void setMode(int mode){this->mode = mode;}
    void setVertexArrayByMode(int mode);
    void changeMode(int mode);

    //设置顶点数据 ONE BY ONE
    void setVertexOBO(float x,float y,float z);

    void setImage(osg::ref_ptr<osg::Image> ima){ this->image = ima;}
    void setImagebyURL(QString filename);
    void setName(QString);
    void setFileName(QString);

    QString getName();
    QString getFileName();

    void initExplorationResult();

    //保存工程
    void saveTo(QString);

    //测试用法保存为二进制
    void saveInByte(QString);



private:
    osg::ref_ptr<osg::Vec3Array> vertexarray;
    osg::ref_ptr<osg::Geometry> geometry;
    osg::ref_ptr<osg::Image> image;
    osg::ref_ptr<osgText::Text> text;
    QString name; //不包含文件后缀名
    QString fileName;//包含文件后缀名

    //记录读取到的数据 包括井数据和四角数据 全部保存便于变换
    QList <double *> *position;
    //记录成果图变换模式
    //模式0，不折 模式1，单向折 模式2，TIN面折
    int mode;

    bool isTransparent;
    int transparency;

    void createGeometry();
    void createText();
    void setTexCoordArray(osg::ref_ptr<osg::Geometry> geo);

    void setVertexArrayMode0();
    void setVertexArrayMode1();
    void setVertexArrayMode2();
};

#endif // EXPLORATONRESULT_H
