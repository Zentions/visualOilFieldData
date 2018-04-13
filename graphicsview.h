#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H


#include "eventadapter.h"

class GraphicsView : public EventAdapter,osgGA::GUIEventHandler
{
    Q_OBJECT

public:
    GraphicsView(QWidget* parent = 0);
    ~GraphicsView();

    osg::Vec3 cam;
       osg::Vec3d eye,center,up;
       float xmin,xmax,ymin,ymax,zmin,zmax,mainbian;
    osg::Geode* getgeode();
    osgText::Text* createText( osg::Vec3 pos,float a);
    osgViewer::Viewer* getOSGViewer(){ return m_pViewer; }
    osg::Group* getRoot(){ return m_pSceneData; }
    void setNode(osg::ref_ptr<osg::Group> group);
    void adjustCamera();
    void settextnode(osg::ref_ptr<osg::Geode> gro);
    void setnode(osg::ref_ptr<osg::Group> node, float shuju);
    void getnum(float x ,float y  ,float z ,float xm, float ym ,float zm);
    void setSwitch(osg::ref_ptr<osg::Switch> switchxyz);
    bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

protected:
    virtual void drawBackground(QPainter *painter, const QRectF& rect);
    virtual void timerEvent(QTimerEvent *event);

private:
    void init();

private:

    osg::ref_ptr<osg::Switch> switchmain;
    osg::ref_ptr<osg::Geode> textgroup;
    osg::ref_ptr<osg::Group> groupnode;
    osg::ref_ptr<osg::Group> m_pSceneData;
    osg::StateSet* m_pStateSet;
    osgViewer::Viewer* m_pViewer;

};

#endif // GRAPHICSVIEW_H
