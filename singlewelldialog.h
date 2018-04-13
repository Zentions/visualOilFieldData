#ifndef SINGLEWELLDIALOG_H
#define SINGLEWELLDIALOG_H
#include "layerscene.h"
#include <QDialog>
#include <QRegExp>
namespace Ui {
class SingleWellDialog;
}

class SingleWellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SingleWellDialog(QWidget *parent = 0);
    ~SingleWellDialog();

private slots:
    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();

private:
    Ui::SingleWellDialog *ui;
    LayerScene *scene;
    QString fileName;

};

#endif // SINGLEWELLDIALOG_H
