#ifndef IMAGEITEM_H
#define IMAGEITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QGraphicsLineItem>
#include <QGraphicsSceneContextMenuEvent>
#include <iostream>
#include <QImage>
using namespace std;

class ImageItem: public QGraphicsObject
{
private:
    QImage image;
    double width;
    double height;
public:
    ImageItem(QString path);
    int getWidth(){return width;}
    int getHeight(){return height;}
protected:
    QRectF boundingRect() const;  //包围盒
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // IMAGEITEM_H
