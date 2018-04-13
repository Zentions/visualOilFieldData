#include "graphicsview.h"
#include "mainwindow.h"
#include <QtWidgets/QGraphicsScene>
#include <QtGui/QPaintEngine>
#include <QtOpenGL/QGLWidget>

GraphicsView::GraphicsView(QWidget *parent)
{

    this->setScene(new QGraphicsScene);

    this->setParent(parent);

    init();
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::init()
{
    QGLWidget* glViewPort = new QGLWidget;
    glViewPort->setMouseTracking(true);
    glViewPort->setMaximumSize(2000, 2000);
    this->setViewport(glViewPort);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    startTimer(10);

    m_pViewer = new osgViewer::Viewer;
    m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
    m_pViewer->addEventHandler(new osgViewer::StatsHandler);
    m_pViewer->addEventHandler(new osgGA::StateSetManipulator(m_pViewer->getCamera()->getOrCreateStateSet()));
    m_pViewer->getCamera()->setNearFarRatio(0.0000002);
    m_pViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
    m_pViewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());

  //  m_pViewer->setSceneData(osgDB::readNodeFile("cow.osg"));

////    //设置默认光源
    // 位置在右上
    m_pViewer->getLight()->setPosition(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    // 环境光
//    m_pViewer->getLight()->setAmbient(osg::Vec4(0.6f, 0.6f, 0.6f, 1.0f));
    m_pViewer->getLight()->setAmbient(osg::Vec4(0.6f, 0.6f, 0.6f, 1.0f));
    // 漫反射光
//    m_pViewer->getLight()->setDiffuse(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
    m_pViewer->getLight()->setDiffuse(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));

//    //设置镜面
    m_pViewer->getLight()->setSpecular(osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));

    m_pGraphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(
        m_pViewer->getCamera()->getGraphicsContext());


}

void GraphicsView::setnode(osg::ref_ptr<osg::Group> node , float shuju)
{
    groupnode=node;
    mainbian=shuju;
   // qDebug()<<groupnode->getNumChildren()<<endl;

}
void GraphicsView::settextnode(osg::ref_ptr<osg::Geode> gro)
{
    textgroup=gro;
}

void GraphicsView::setSwitch(osg::ref_ptr<osg::Switch> switchxyz)
{
    switchmain=switchxyz;
 //   switchmain->asSwitch()->setValue(1,false);
}

bool GraphicsView::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa)
{
    float x,y,z;
    if(switchmain==NULL)
           return false;
     osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
    switch(ea.getEventType())
    {
       case (osgGA::GUIEventAdapter::DRAG):
    {
      groupnode->removeChild(textgroup);


         view->getCamera()->getViewMatrixAsLookAt(eye,center,up);
      //   qDebug()<<"init eye:%f,%f,%f\n"<<eye._v[0]<<eye._v[1]<<eye._v[2]<<endl;

         if(abs(center.x()-xmin)<abs(center.x()-xmax))
         {
             switchmain->asSwitch()->setValue(1,true);
             switchmain->asSwitch()->setValue(0,false);
            x=xmax;
         }
         else
         {
             switchmain->asSwitch()->setValue(0,true);
             switchmain->asSwitch()->setValue(1,false);
            x=xmin;
         }

         if(abs(center.y()-ymin)<abs(center.y()-ymax))
         {
               switchmain->asSwitch()->setValue(3,true);
              switchmain->asSwitch()->setValue(2,false);
            y=ymax;
         }

         else
         {
              switchmain->asSwitch()->setValue(2,true);
             switchmain->asSwitch()->setValue(3,false);
             y=ymin;
         }



         if(abs(center.z()-zmin)<abs(center.z()-zmax))
         {
             switchmain->asSwitch()->setValue(5,true);
             switchmain->asSwitch()->setValue(4,false);
             z=zmax;
         }

         else
         {
             switchmain->asSwitch()->setValue(4,true);
             switchmain->asSwitch()->setValue(5,false);
             z=zmin;
         }
         textgroup =new osg::Geode;
         int i=0;
         while(5*i*mainbian<(xmax-xmin))
           {

             textgroup->addDrawable(createText(osg::Vec3(xmin+100+5*i*mainbian, y, zmax+200),xmin+i*5*mainbian));
            i++;
         }

         i=1;
         while(5*i*mainbian<(ymax-ymin))
         {
               textgroup->addDrawable(createText(osg::Vec3(x, ymin+100+5*i*mainbian, zmax+100),ymin+i*5*mainbian));
                i++;
         }
         i=1;
         while(5*i*mainbian<(zmax-zmin))
         {
               textgroup->addDrawable(createText(osg::Vec3(xmax+100, y, zmin+100+5*i*mainbian),zmin+i*5*mainbian));
            i++;
         }
        groupnode->addChild(textgroup);

      }
    default:
        return false;
}
}
osg::Geode* GraphicsView::getgeode()
{
    return textgroup.release();
}

osgText::Text*  GraphicsView::createText( osg::Vec3 pos,float a)
{

    QString s;
    s=QString::number(a,'f',2);
    string temp=s.toStdString();

     osg::ref_ptr<osgText::Text> text = new osgText::Text;
     text->setDataVariance(osg::Object::UNSPECIFIED);
     text->setText(temp);
     text->setColor(osg::Vec4(0.0,0.0,0.0,1.0));
     text->setAxisAlignment(osgText::Text::SCREEN);
   //  text->setLayout(osgText::Text::RIGHT_TO_LEFT);
   //  text->setAlignment();
     text->setCharacterSize(20);
     text->setPosition( pos);
     text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);//跟随视角不断变化，离物体越远，文字越大
    // text->setAutoRotateToScreen(true);//跟随视角不断变化，但离物体越远，文字越小，和现实当中像类似
     return  text.release();
}
void GraphicsView::getnum(float x ,float y  ,float z ,float xm, float ym ,float zm)
{
    xmin=x;
    ymin=y;
    zmin=z;
    xmax=xm;
    ymax=ym;
    zmax=zm;
}
void GraphicsView::timerEvent(QTimerEvent *event)
{
    this->scene()->update();
}

void GraphicsView::drawBackground(QPainter *painter, const QRectF& rect)
{
    if (painter->paintEngine()->type() != QPaintEngine::OpenGL2)
    {
        return;
    }
    // Save the painter state
    painter->save();
    painter->beginNativePainting();

    m_pViewer->frame();

    painter->endNativePainting();
    painter->restore();
}

void GraphicsView::setNode(osg::ref_ptr<osg::Group> group)
{

    m_pSceneData = group;
    m_pViewer->setSceneData(m_pSceneData);
    m_pViewer->addEventHandler(this);

   // m_pViewer->addEventHandler(new UserEventHandler);
  //  m_pViewer->addEventHandler(new osgGA::StateSetManipulator(m_pViewer->getCamera()->getOrCreateStateSet()));

}
void GraphicsView::adjustCamera()
{
   m_pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
}


