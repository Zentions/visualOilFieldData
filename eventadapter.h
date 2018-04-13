#ifndef EVENTADAPTER_H
#define EVENTADAPTER_H

#include <QtGui/QInputEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtWidgets/QOpenGLWidget>
#include <QMainWindow>
#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QTimer>
#include <QGraphicsView>
#include <osg/Viewport>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <osgQt/GraphicsWindowQt>
#include <osg/Camera>
#include <osg/Node>
#include <osg/Vec4>
#include <osg/DisplaySettings>
#include <QGraphicsItem>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osg/ref_ptr>
class EventAdapter : public QGraphicsView
{
public:

    EventAdapter();

    ~EventAdapter();

protected:
       bool viewportEvent(QEvent* event);
       void setKeyboardModifiers(QInputEvent* event);
    // 处理按键事件
       virtual void keyPressEvent(QKeyEvent* event);
       virtual void keyReleaseEvent(QKeyEvent* event);

       // 处理鼠标单击事件
       virtual void mousePressEvent(QMouseEvent* event);
       virtual void mouseReleaseEvent(QMouseEvent* event);

       // 处理鼠标双击事件
       virtual void mouseDoubleClickEvent(QMouseEvent* event);
       virtual void mouseMoveEvent(QMouseEvent* event);

       // 处理鼠标中轮滑动事件
       virtual void wheelEvent(QWheelEvent* event);

       // 处理窗口大小改变事件
       virtual void resizeEvent(QResizeEvent *event);

       // 处理鼠标移动事件
       virtual void moveEvent(QMoveEvent* event);

       // timerEvent事件
       virtual void timerEvent(QTimerEvent *event);
protected:
    osgViewer::GraphicsWindow* m_pGraphicsWindow;

};
#endif // EVENTADAPTER_H
