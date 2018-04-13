#ifndef CHECKDIALOG_H
#define CHECKDIALOG_H
#include<QTreeWidgetItem>
#include <QDialog>
#include "layerdialog.h"
namespace Ui {
class CheckDialog;
}

class CheckDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckDialog(QWidget *parent = 0);
    ~CheckDialog();
    void init();  //申明初始化函数
    void updateParentItem(QTreeWidgetItem* item);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
     //申明信号与槽,当树形控件的子选项被改变时执行
    void treeItemChanged(QTreeWidgetItem* item , int column);
    void on_pushButton_4_clicked();

private:
    Ui::CheckDialog *ui;
    QList<DThree> layerList;
    QList<DThree> profileList;
    QString layerFileName;//地层文件名
    QString profileFileName;//连井剖面文件名
    QTreeWidgetItem* group1,*group2;
    bool layerFlag,proFlag;//记录是否被打开过
    void readData(QString fileName,bool LOrP);
    void saveData(QString fileName,int num);
};

#endif // CHECKDIALOG_H
