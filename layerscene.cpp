#include "layerscene.h"

LayerScene::LayerScene(QString fileName)
{
   setClickToFalse();
   this->fileName = fileName;
   ImageItem *item = new ImageItem(this->fileName);
   list.append(DTwo(item->getWidth(),item->getHeight()));
   addItem(item);
}
void LayerScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    double x = event->scenePos().rx();
    double y = event->scenePos().ry();
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(x-2,y-2,4,4);
    addItem(item);
    list.append(DTwo(x,y));
    isClick = true;
}
