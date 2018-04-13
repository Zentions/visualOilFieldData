#include "treeview.h"

TreeView::TreeView(QWidget *parent)
{
    init();
    this->setParent(parent);



}
TreeView::~TreeView()
{

}
void TreeView::init()
{
    //设置图标
    m_publicIconMap[QStringLiteral("treeItem_Text")] =QIcon(QStringLiteral("Text.png"));
    m_publicIconMap[QStringLiteral("treeItem_Pix")] =QIcon(QStringLiteral("Pix.png"));
    m_publicIconMap[QStringLiteral("treeItem_Osg")] =QIcon(QStringLiteral("Osg.png"));
    //添加表头
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("工程列表"));

    connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(treeItemChanged(QStandardItem*)));
    this->setModel(model);


}

//添加工程文件夹
void TreeView::addChild(QString name, QString path, QList<PROJECTITEM *> * itemList)
{


    //将上一项目的树信息清空
    model->clear();
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("工程列表"));
    //创建根目录
    root = new QStandardItem(name);
    root->setData(MARK_PROJECT,ROLE_MARK);
    //root->setData(MARK_FOLDER,ROLE_MARK_FOLDER);
    root->setEditable(false);
    model->appendRow(root);
    for(int i=0;i<itemList->size();i++)
    {
        QStandardItem *tempItem = new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_Pix")],itemList->at(i)->text);
        tempItem->setEditable(false);

        switch(itemList->at(i)->type)
        {
        case MARK_TYPE_EXPLORATIONRESULT:
            tempItem->setData(MARK_FOLDER_EXPLORATIONRESULT,ROLE_MARK_FOLDER);//它属于勘探成果图文件文件夹
            itemExplorationResultChild = tempItem;
            break;
        case MARK_TYPE_WELL:
            tempItem->setData(MARK_FOLDER_WELL,ROLE_MARK_FOLDER);//它属于井文件文件夹
            itemWellChild = tempItem;
            break;
        case MARK_TYPE_PROFILE:
            tempItem->setData(MARK_FOLDER_PROFILE,ROLE_MARK_FOLDER);//它属于连井剖面图文件文件夹
            itemProfileChild=tempItem;
            break;
        case MARK_TYPE_STRATASURFACE:
            tempItem->setData(MARK_FOLDER_STRATASURFACE,ROLE_MARK_FOLDER);//它属于地层面文件文件夹
            itemStrataSurfaceChild=tempItem;
            break;
        case MARK_TYPE_FAULT:
            tempItem->setData(MARK_FOLDER_FAULT,ROLE_MARK_FOLDER);//它属于断层面文件文件夹
            break;
        case MARK_TYPE_SMODEL:
            tempItem->setData(MARK_FOLDER_SMODEL,ROLE_MARK_FOLDER);//它属于表面模型文件文件夹
            break;
        case MARK_TYPE_VMODEL:
            tempItem->setData(MARK_FOLDER_VMODEL,ROLE_MARK_FOLDER);//它属于体元模型文件文件夹
            break;
        case MARK_TYPE_CCOLUMN:
            tempItem->setData(MARK_FOLDER_CCOLUMN,ROLE_MARK_FOLDER);//它属于综合柱状图文件文件夹
            itemSingleWellChartChild = tempItem;
            break;

        }

        root->appendRow(tempItem);
    }

    //保存项目路径
    projectPath = path;

}
//void TreeView::addChild(QString name, QString path)
//{


//    //将上一项目的树信息清空
//    model->clear();
//    maxLength=0;
//    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("工程列表"));
//    //创建根目录
//    root = new QStandardItem(name);
//    root->setData(MARK_PROJECT,ROLE_MARK);
//    root->setData(MARK_FOLDER,ROLE_MARK_FOLDER);
//    model->appendRow(root);
//    //创建勘探成果图文件夹
//    itemExplorationResultChild=new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_Pix")],QStringLiteral("勘探成果图"));
//    itemExplorationResultChild->setEditable(false);
//    itemExplorationResultChild->setData(MARK_FOLDER_EXPLORATIONRESULT,ROLE_MARK_FOLDER);//其次它属于勘探成果图文件夹
//    root->appendRow(itemExplorationResultChild);
//    //创建井文件夹
//    itemWellChild=new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_Osg")],QStringLiteral("井"));
//    itemWellChild->setEditable(false);
//    itemWellChild->setData(MARK_FOLDER_WELL,ROLE_MARK_FOLDER);//其次它属于井文件文件夹
//    root->appendRow(itemWellChild);

//    //创建连井剖面文件夹
//    itemProfileChild=new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_Osg")],"连井剖面图");
//    itemProfileChild->setEditable(false);
//    itemProfileChild->setData(MARK_FOLDER_PROFILE,ROLE_MARK_FOLDER);//其次它属于连井剖面文件文件夹
//    root->appendRow(itemProfileChild);
//    //创建地层面文件夹
//    itemStrataSurfaceChild=new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_Osg")],"地层");
//    itemStrataSurfaceChild->setEditable(false);
//    itemStrataSurfaceChild->setData(MARK_FOLDER_STRATASURFACE,ROLE_MARK_FOLDER);
//    root->appendRow(itemStrataSurfaceChild);
//    //保存项目路径
//    projectPath = path;

//}

//添加文件
void TreeView::addFile(int type,QString name)
{
    switch (type) {
    case MARK_TYPE_EXPLORATIONRESULT:
        addExplorationResultFile(name);
        break;
    case MARK_TYPE_WELL:
        addWellFile(name);
        break;
    case MARK_TYPE_PROFILE:
        addProfileFile(name);
        break;
    case MARK_TYPE_STRATASURFACE:
        addStrataSurfaceFile(name);
        break;

    case MARK_TYPE_FAULT:
        addFaultFile(name);
        break;
    case MARK_TYPE_SMODEL:
        addSModelFile(name);
        break;
    case MARK_TYPE_VMODEL:
        addVModelFile(name);
        break;
    case MARK_TYPE_CCOLUMN:
        addCColumnFile(name);
        break;
    }
}
//添加勘探成果图文件
void TreeView::addExplorationResultFile(QString name)
{

    itemExplorationResultFileChild=new QStandardItem(name);
    itemExplorationResultFileChild->setEditable(false);
    itemExplorationResultFileChild->setCheckable(true);
    itemExplorationResultFileChild->setTristate(true);
    itemExplorationResultFileChild->setCheckState(Qt::Checked);
    itemExplorationResultFileChild->setData(MARK_ITEM,ROLE_MARK);
    itemExplorationResultFileChild->setData(MARK_ITEM_EXPLORATIONRESULT,ROLE_MARK_ITEM);
    itemExplorationResultChild->appendRow(itemExplorationResultFileChild);

    //创建子节点
    itemChild=new QStandardItem("名称");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemExplorationResultFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("图件");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemExplorationResultFileChild->appendRow(itemChild);


}
//添加井文件
void TreeView::addWellFile(QString name)
{
    itemWellFileChild=new QStandardItem(name);
    itemWellFileChild->setEditable(false);
    itemWellFileChild->setCheckable(true);
    itemWellFileChild->setTristate(true);
    itemWellFileChild->setCheckState(Qt::Checked);

  //  itemWellFileChild->setData(MARK_ITEM,ROLE_MARK);
    itemWellFileChild->setData(MARK_ITEM_WELL,ROLE_MARK_ITEM);
    itemWellChild->appendRow(itemWellFileChild);

    //创建子节点
    itemChild=new QStandardItem("井名");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemWellFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("井筒");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemWellFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("井迹");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemWellFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("井筒贴图");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemWellFileChild->appendRow(itemChild);
}
//添加连井剖面文件
void TreeView::addProfileFile(QString name)
{

    itemProfileFileChild=new QStandardItem(name);
    itemProfileFileChild->setEditable(false);
    itemProfileFileChild->setCheckable(true);
    itemProfileFileChild->setTristate(true);
    itemProfileFileChild->setCheckState(Qt::Checked);
    itemProfileFileChild->setData(MARK_ITEM,ROLE_MARK);
    itemProfileFileChild->setData(MARK_ITEM_PROFILE,ROLE_MARK_ITEM);
    itemProfileChild->appendRow(itemProfileFileChild);

    this->resizeColumnToContents(0);
    //创建子节点
    itemChild=new QStandardItem("名称");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemProfileFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("剖面图");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemProfileFileChild->appendRow(itemChild);

}
//添加地层面文件
void TreeView::addStrataSurfaceFile(QString name)
{

    itemTinFileChild = new QStandardItem(name);
    itemTinFileChild->setEditable(false);
    itemTinFileChild->setCheckable(true);
    itemTinFileChild->setTristate(true);
    itemTinFileChild->setCheckState(Qt::Checked);
    itemTinFileChild->setData(MARK_ITEM_STRATASURFACE,ROLE_MARK_ITEM);
    itemStrataSurfaceChild->appendRow(itemTinFileChild);



    //创建子节点
    itemChild = new QStandardItem("名称");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemTinFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("地层面");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemTinFileChild->appendRow(itemChild);

}
//添加断层面文件
void TreeView::addFaultFile(QString name){}
//添加表面模型文件
void TreeView::addSModelFile(QString name){}
//添加体元模型文件
void TreeView::addVModelFile(QString name){}
//添加综合柱状图文件
void TreeView::addCColumnFile(QString name){
    itemSingleWellChartFileChild=new QStandardItem(name);
    itemSingleWellChartFileChild->setEditable(false);
    itemSingleWellChartFileChild->setCheckable(true);
    itemSingleWellChartFileChild->setTristate(true);
    itemSingleWellChartFileChild->setCheckState(Qt::Checked);
    itemSingleWellChartFileChild->setData(MARK_ITEM,ROLE_MARK);
    itemSingleWellChartFileChild->setData(MARK_ITEM_CCOLUMN,ROLE_MARK_ITEM);
    itemSingleWellChartChild->appendRow(itemSingleWellChartFileChild);

    //创建子节点
    itemChild=new QStandardItem("名称");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemSingleWellChartFileChild->appendRow(itemChild);

    itemChild=new QStandardItem("图件");
    itemChild->setEditable(false);
    itemChild->setCheckable(true);
    itemChild->setCheckState(Qt::Checked);
    itemSingleWellChartFileChild->appendRow(itemChild);
}
/*当treeview中有item的复选框发生改变时，将发生改变的item所在的组
及所在行以信号的形式发送出去*/
void TreeView::treeItemChanged (QStandardItem *item)
{
    if(item==NULL)
        return;
    if(item->isCheckable())
    {
        //如果条目是存在复选框的，那么就进行下面的操作
               Qt::CheckState state = item -> checkState (); //获取当前的选择状态
               if (item->isTristate())
               {
                    //如果条目是三态的，说明可以对子目录进行全选和全不选的设置
                   if (state!= Qt::PartiallyChecked)
                   {
                       //当前是选中状态，需要对其子项目进行全选
                       treeItem_checkAllChild(item,state == Qt::Checked ? true : false );
                   }

               }
               else
               {
                //说明是两态的，两态会对父级的三态有影响
                //判断兄弟节点的情况

                 treeItem_CheckChildChanged ( item );

               }

    }
}
//
// \brief 递归设置所有的子项目为全选或全不选状态
// \param item 当前项目
// \param check true时为全选，false时全不选
//
void TreeView::treeItem_checkAllChild(QStandardItem * item, bool check)
{
    if(item == NULL)
        return;
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}

void TreeView::treeItem_checkAllChild_recursion(QStandardItem * item,bool check)
{
    if(item == NULL)
        return;
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}
//
// \brief 根据子节点的改变，更改父节点的选择情况
// \param item
//
void TreeView::treeItem_CheckChildChanged(QStandardItem * item)
{
    if(item==NULL)
        return;

    Qt::CheckState state = item->checkState();
    Qt::CheckState siblingState = checkSibling(item);
    QStandardItem * parentItem = item->parent();

    if(NULL == parentItem)
        return;
    emit stateChanged(parentItem->parent()->index().row()
                       ,parentItem->index().row(),item->index().row(),state == Qt::Checked ? true : false);

    if(Qt::PartiallyChecked == siblingState)
    {
        if(parentItem->isCheckable() && parentItem->isTristate())
            parentItem->setCheckState(Qt::PartiallyChecked);
    }
    else if(Qt::Checked == siblingState)
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Checked);
    }
    else
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Unchecked);
    }
}
//
// \brief 测量兄弟节点的情况，如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
// \param item
// \return 如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
//
Qt::CheckState TreeView::checkSibling(QStandardItem * item)
{
    //先通过父节点获取兄弟节点
    QStandardItem * parent = item->parent();
    if(NULL == parent)
        return item->checkState();
    int brotherCount = parent->rowCount();
    int checkedCount(0),unCheckedCount(0);
    Qt::CheckState state;
    for(int i=0;i<brotherCount;++i)
    {
        QStandardItem* siblingItem = parent->child(i);
        state = siblingItem->checkState();
        if(Qt::PartiallyChecked == state)
            return Qt::PartiallyChecked;
        else if(Qt::Unchecked == state)
            ++unCheckedCount;
        else
            ++checkedCount;
        if(checkedCount>0 && unCheckedCount>0)
            return Qt::PartiallyChecked;
    }
    if(unCheckedCount>0)
        return Qt::Unchecked;
    return Qt::Checked;
}

void TreeView::treeItem_CheckActionTriggerd(QAction *action)
{

    QVariant var = action->data();
    if(!action->isChecked())
    {
        action->setChecked(false);
        switch(var.toInt())
        {
        case MARK_EXPLORATIONRESULT_NAME:
            for(int i=0;i<itemExplorationResultChild->rowCount();i++)
            {
                itemExplorationResultChild->child(i)->child(0)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_EXPLORATIONRESULT_PIX:
            for(int i=0;i<itemExplorationResultChild->rowCount();i++)
            {
                itemExplorationResultChild->child(i)->child(1)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_WELL_HEAD:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(2)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_WELL_NAME:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(0)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_WELL_WELL:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(1)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_PROFILE_NAME:
            for(int i=0;i<itemProfileChild->rowCount();i++)
            {
                itemProfileChild->child(i)->child(0)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_PROFILE_PIX:
            for(int i=0;i<itemProfileChild->rowCount();i++)
            {
                itemProfileChild->child(i)->child(1)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_STRATASURFACE_NAME:
            for(int i=0;i<itemStrataSurfaceChild->rowCount();i++)
            {
                itemStrataSurfaceChild->child(i)->child(0)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_STRATASURFACE_TIN:
            for(int i=0;i<itemStrataSurfaceChild->rowCount();i++)
            {
                itemStrataSurfaceChild->child(i)->child(1)->setCheckState(Qt::Unchecked);
            }
            break;
        case MARK_SINGLEWELLCHART_PIX:
            for(int i=0;i<itemSingleWellChartChild->rowCount();i++)
            {
                itemSingleWellChartChild->child(i)->child(1)->setCheckState(Qt::Unchecked);
            }
            break;

        }

    }
    else
    {
        action->setChecked(true);
        switch(var.toInt())
        {
        case MARK_EXPLORATIONRESULT_NAME:
            for(int i=0;i<itemExplorationResultChild->rowCount();i++)
            {
                itemExplorationResultChild->child(i)->child(0)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_EXPLORATIONRESULT_PIX:
            for(int i=0;i<itemExplorationResultChild->rowCount();i++)
            {
                itemExplorationResultChild->child(i)->child(1)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_WELL_HEAD:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(2)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_WELL_NAME:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(0)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_WELL_WELL:
            for(int i=0;i<itemWellChild->rowCount();i++)
            {
                itemWellChild->child(i)->child(1)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_PROFILE_NAME:
            for(int i=0;i<itemProfileChild->rowCount();i++)
            {
                itemProfileChild->child(i)->child(0)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_PROFILE_PIX:
            for(int i=0;i<itemProfileChild->rowCount();i++)
            {
                itemProfileChild->child(i)->child(1)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_STRATASURFACE_NAME:
            for(int i=0;i<itemStrataSurfaceChild->rowCount();i++)
            {
                itemStrataSurfaceChild->child(i)->child(0)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_STRATASURFACE_TIN:
            for(int i=0;i<itemStrataSurfaceChild->rowCount();i++)
            {
                itemStrataSurfaceChild->child(i)->child(1)->setCheckState(Qt::Checked);
            }
            break;
        case MARK_SINGLEWELLCHART_PIX:
            for(int i=0;i<itemSingleWellChartChild->rowCount();i++)
            {
                itemSingleWellChartChild->child(i)->child(1)->setCheckState(Qt::Checked);
            }
            break;

        }
    }
}
//树中删除勘探成果图节点
void TreeView::deleteExplorationResultItem(QModelIndex index)
{
    int row = index.row();
    itemExplorationResultChild->removeRow(row);

}
//树中删除井节点
void TreeView::deleteWellItem(QModelIndex index)
{
    int row = index.row();
    itemWellChild->removeRow(row);
}
//树中删除连井剖面图节点
void TreeView::deleteProfileItem(QModelIndex index)
{
    int row = index.row();
    itemProfileChild->removeRow(row);
}
//树中删除地层面节点
void TreeView::deleteStrataSurfaceItem(QModelIndex index)
{
    int row =index.row();
    itemStrataSurfaceChild->removeRow(row);

}
//树中删除综合柱状图节点
void TreeView::deleteCColumnItem(QModelIndex index)
{
    int row =index.row();
    itemSingleWellChartChild->removeRow(row);

}
