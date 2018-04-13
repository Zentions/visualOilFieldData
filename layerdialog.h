#ifndef LAYERDIALOG_H
#define LAYERDIALOG_H
#include <iostream>
#include <QImage>
#include <string>
#include <QDialog>
#include "layerscene.h"
using namespace std;

namespace Ui {
class LayerDialog;
}
class LayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LayerDialog(QWidget *parent = 0);
    ~LayerDialog();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

private:
    Ui::LayerDialog *ui;
    LayerScene *scene;
    QList<DTwo> PixelList;
    QList<DThree> PosList;
    QString fileName;
    DThree first;
    DThree second;
    double rateX,rateY,rateZ;
    bool isLayerOrPro;//记录当前打开的是勘探成果图（false）还是连井剖面图（true）

    //记录连井剖面图井点的像素横坐标
    int *pixel;

    void calculate();
};

#endif // LAYERDIALOG_H
