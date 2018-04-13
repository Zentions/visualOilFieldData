#ifndef PROFILECALDIALOG_H
#define PROFILECALDIALOG_H

#include <QDialog>
#include "layerscene.h"
using namespace std;

namespace Ui {
class ProfileCalDialog;
}

class ProfileCalDialog : public QDialog
{
    Q_OBJECT


public:
    explicit ProfileCalDialog(QWidget *parent = 0);
    ~ProfileCalDialog();

private slots:

    void on_savedata_clicked();

    void on_openfile_clicked();

    void on_calculate_clicked();

private:
    Ui::ProfileCalDialog *ui;

    LayerScene *scene;

    QList<DTwo> PixelList;

    //posList用于记录计算过后的点数据
   // 数据格式 list[0]存入深度x y List[1]及之后存图片井 及图片四角水平坐标
    QList<DThree> PosList;
    QString fileName;
    DThree first;
    DThree second;
    double rateX,rateY,rateZ;


    void calculate();
};

#endif // PROFILECALDIALOG_H
