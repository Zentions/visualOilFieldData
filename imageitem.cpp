#include "imageitem.h"

ImageItem::ImageItem(QString path)
{
   image.load(path);
//   double proportion;
//   if(image.width()>image.height()) proportion = image.width()/450.0f;
//   else proportion = image.height()/450.0f;
//   width = image.width()/proportion;
//   height = image.height()/proportion;
   width = image.width();
   height = image.height();
}
QRectF ImageItem::boundingRect() const
{
    qreal adjust = 0.5;
    //return QRectF(0-adjust,0-adjust,450+adjust,450+adjust);
    return QRectF(0-adjust,0-adjust,width+adjust,height+adjust);
}
void ImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

//    if(image.width()>450 || image.height() >450)
//    {
//        QRectF rect(0,0,width,height);
//        painter->drawImage(rect,image);
//    }else
//    {
//       painter->drawImage(0,0,image);
//    }
     painter->drawImage(0,0,image);
}
