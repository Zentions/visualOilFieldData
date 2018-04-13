#ifndef STRATASURFACE_H
#define STRATASURFACE_H
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

#include <osgUtil/SmoothingVisitor>
#include <osg/Material>

#include "common.h"
#include "colorsetdialog.h"
#include "propertysetdialog.h"

class StrataSurface
{
public:
    StrataSurface();

    //获得数据
    osg::ref_ptr<osg::Geometry> getGeometry(){return this->geometry;}
    osg::ref_ptr<osg::Vec3Array> getVertexArray(){ return this->vertexarray;}
    osg::ref_ptr<osgText::Text> getText(){return this->text;}
    osg::ref_ptr<osg::Vec2Array> getTexCoordArray(){ return this->texcoordarray;}
    osg::ref_ptr<osg::Vec4Array> getColorArray(){ return this->colorarray;}

    //是否透明
    bool isTransparency(){return this->transparency>0?true:false;}

    //设置数据
    void setVertexArray(osg::ref_ptr<osg::Vec3Array> ver){this->vertexarray = ver;}
    void setVertexArraybyURL(QString filename);

    //设置地层三角形数目
    void setTriangleNum(int num){this->triangleNum = num;}

    //设置地层三角形顶点
    void setTrianglePoint(int* a[3]);

    //设置地层名称
    void setName(QString name){this->name = name;}


    //获得当前属性
    int getposition(){return this->position;}

    //添加地层属性数据
    void setProData(int *p,QString name);
//    void setPro1(int *p){this->pro1=p;}
//    void setPro2(int *p){this->pro2=p;}

    //获得地层属性
    QList <int*> *getpropertylist(){return this->propertylist;}
//    int *getPro1(){return this->pro1;}
//    int *getPro2(){return this->pro2;}
    QStringList  *getpropertynamelist(){return this->propertynamelist;}

//    //获得当前属性
//    int *getCurrentpro(){return this->currentpro;}

    //按照属性设置颜色
    void setByProPosition(int position);

//    //使用选择属性对话框选择属性
    void choseProperty();



    //设置地层颜色
    void setColorArray(osg::ref_ptr<osg::Vec4Array> col){this->colorarray = col;}

    //设置配色方案 使用对话框
    void setColorSet();

    //设置配色方案 改变第pos个配色方案
    void setColorSet(QColor * colorset,int pos){this->colorSetList->operator [](pos) = colorset;}

    //设置地层顶点 ONE BY ONE
    void setVertexOBO(float x,float y,float z);

    //设置地层纹理
    void setTexCoordArray(osg::Vec2Array *ta){this->texcoordarray = ta;}
    void setTexCoordArrayOBO(float x,float y);

    //设置地层半透明
    void setHalfTransparency(bool isTransparent);

    //设置地层透明度
    void setTransparency(float transparency);
    //设置地层透明
    void setTransparent();
    //获得地层透明度
    float getTransparency();

    //按点设颜色
    void setPointSampleColor();
    void setPointSingleColor(int);

    //按点设颜色 按属性渐变
    void setPointGradientColor(int *pro);
    //按面设颜色 按属性渐变
    void setFaceColor(int *pro);

    //设置地层颜色
    void setSingleColor(osg::Vec4);
    //获得地层颜色
    osg::Vec4 getSingleColor();

    //设置材质
    void setMaterial();

    QString getName();

    void initStrataSurface();
    //保存对象到工程
    void saveTo(QString);


private:

    osg::ref_ptr<osg::Vec3Array> vertexarray;
    osg::ref_ptr<osg::Vec4Array> colorarray;
    osg::ref_ptr<osg::Geometry> geometry;
    osg::ref_ptr<osgText::Text> text;
    osg::ref_ptr<osg::Vec2Array> texcoordarray;

    //给TIN面赋单色的初始颜色数组
    osg::ref_ptr<osg::Vec4Array> default_color;

    //存取TIN面三角形索引号
    int* trianglePoint[3];
    //索引数组长度,三角形个数
    int triangleNum;

    QString name;
    float transparency;

    osg::Vec4 singleColor;

    //属性数组list
    //属性数组为 数组长度 属性类型 属性下限 属性上限 属性值1 属性值2 ···
    QList <int*> *propertylist;
    //记录属性名
    QStringList  *propertynamelist;
 //   int **propety;
//    int * pro1,* pro2;

    //记录当前属性在属性列表的位置
    int position;

//    //颜色 最冷色 和 最暖色
//    QColor deepcolor,lightcolor;

    //配色方案数组 记录每个属性下的颜色值 是二维数组的表 二维数组中是两个值 冷色 暖色
    QList <QColor*> *colorSetList;


    //把属性转换成颜色数组
    osg::ref_ptr<osg::Vec4Array> getColorarrayByPro(int *pro);

    void createGeometry();
    void createText();
    void setTexCoordArray();
};

#endif // STRATASURFACE_H
