#ifndef LAYERSCENE_H
#define LAYERSCENE_H
#include <QGraphicsScene>
#include "imageitem.h"
struct DTwo
{
    double x;
    double y;
    DTwo(double xx,double yy):x(xx),y(yy){}
    DTwo(){}
};
struct DThree
{
    double x;
    double y;
    double z;
    QString name;
    DThree(double xx,double yy,double zz,QString n="\n"):x(xx),y(yy),z(zz),name(n){}
    DThree(){}
};
class LayerScene:public QGraphicsScene
{
public:
    LayerScene(QString fileName);
    int getSize(){return list.size();}
    QList<DTwo> getList(){return list;}
    bool getClick(){return isClick;}
    void setClickToFalse(){isClick = false;}
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QString path;
    QList<DTwo> list;
    bool isClick;
    QString fileName;
};

#endif // LAYERSCENE_H
