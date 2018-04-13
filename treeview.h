#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QPixmap>
#include <QMessageBox>
#include <QAction>
#include <QVariant>
#include "common.h"
#include "projectOperation.h"
class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget* parent = 0);
    ~TreeView();

    void addRoot();
//    void addChild(QString,QString);
    void addChild(QString,QString,QList<PROJECTITEM*>*);
    void addExplorationResultFile(QString name);
    void addWellFile(QString name);
    void addProfileFile(QString name);
    void addStrataSurfaceFile(QString name);
    void addFaultFile(QString name);
    void addSModelFile(QString name);
    void addVModelFile(QString name);
    void addCColumnFile(QString name);

    void addFile(int type,QString name);

    bool isChecked();
    void init();

    void treeItem_checkAllChild(QStandardItem * item, bool check);
    void treeItem_checkAllChild_recursion(QStandardItem * item,bool check);
    void treeItem_CheckChildChanged(QStandardItem * item);

    void deleteWellItem(QModelIndex);
    void deleteExplorationResultItem(QModelIndex);
    void deleteProfileItem(QModelIndex);
    void deleteStrataSurfaceItem(QModelIndex);
    void deleteCColumnItem(QModelIndex);

    Qt::CheckState checkSibling(QStandardItem * item);
    QStandardItemModel *model;

private:


    QStandardItem *root;
    QStandardItem *itemChild;
    QStandardItem *itemProject;

    QStandardItem *itemExplorationResultChild;
    QStandardItem *itemWellChild;
    QStandardItem *itemProfileChild;
    QStandardItem *itemStrataSurfaceChild;
    QStandardItem *itemSingleWellChartChild;

    QStandardItem *itemExplorationResultFileChild;
    QStandardItem *itemWellFileChild;
    QStandardItem *itemProfileFileChild;
    QStandardItem *itemTinFileChild;
    QStandardItem *itemSingleWellChartFileChild;


    QMap<QString,QIcon> m_publicIconMap;
    QString projectPath;
//    int maxLength;//treeview中文本的最大长度
    bool m_state;//判断是否选中
private slots:
    void treeItemChanged (QStandardItem * item );
    void treeItem_CheckActionTriggerd(QAction*);
signals:
    void stateChanged(int,int,int,bool);

};

#endif // TREEVIEW_H
