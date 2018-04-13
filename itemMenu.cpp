#include "itemMenu.h"

ItemMenu::ItemMenu()
{

}
ItemMenu::~ItemMenu()
{

}

void ItemMenu::addStrataSurfaceItemAction(bool transparent)
{
    action  = new QAction(QStringLiteral("删除"),this);
    action->setCheckable(false);
    action->setChecked(true);
    action->setData(MARK_STRATASURFACE_DEL);
    this->addAction(action);

    action  = new QAction(QStringLiteral("半透明"),this);
    action->setCheckable(true);
    action->setChecked(transparent);
    action->setData(MARK_STRATASURFACE_TRANSPARENT);
    this->addAction(action);

    action  = new QAction(QStringLiteral("选择属性"),this);
    action->setCheckable(false);
    action->setChecked(true);
    action->setData(MARK_STRATASURFACE_PROPERTY);
    this->addAction(action);

    action  = new QAction(QStringLiteral("属性配色"),this);
    action->setCheckable(false);
    action->setChecked(true);
    action->setData(MARK_STRATASURFACE_COLORSET);
    this->addAction(action);

}

void ItemMenu::addWellItemAction()
{
    action  = new QAction(QStringLiteral("删除"),this);
    action->setCheckable(false);
    action->setChecked(true);
    action->setData(MARK_WELL_DEL);
    this->addAction(action);
    action  = new QAction(QStringLiteral("改变贴图方式"),this);
    action->setCheckable(true);
    action->setChecked(false);
    action->setData(MARK_WELL_CHANGEPIC);
    this->addAction(action);
    action  = new QAction(QStringLiteral("选择贴图"),this);
    action->setCheckable(true);
    action->setChecked(false);
    action->setData(MARK_WELL_SELECTPIC);
    this->addAction(action);

}
void ItemMenu::addExplorationResultItemAction()
{
    action  = new QAction(QStringLiteral("删除"),this);
    action->setCheckable(false);
    action->setChecked(true);
    action->setData(MARK_EXPLORATIONRESULT_DEL);
    this->addAction(action);
    action  = new QAction(QStringLiteral("半透明"),this);
    action->setCheckable(true);
    action->setChecked(false);
    action->setData(MARK_EXPLORATIONRESULT_TRANSPARENT);
    this->addAction(action);
    action  = new QAction(QStringLiteral("变换模式"),this);
    action->setCheckable(true);
    action->setChecked(false);
    action->setData(MARK_EXPLORATIONRESULT_CHANGEMODE);
    this->addAction(action);
}
void ItemMenu::addProfileItemAction()
{
    action  = new QAction(QStringLiteral("删除"),this);
    action->setCheckable(false);
    action->setChecked(true);
    action->setData(MARK_PROFILE_DEL);
    this->addAction(action);

    action  = new QAction(QStringLiteral("半透明"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_PROFILE_TRANSPARENT);
    this->addAction(action);
}
void ItemMenu::addSingleWellChartItemAction()
{
    action  = new QAction(QStringLiteral("删除"),this);
    action->setCheckable(false);
    action->setChecked(true);
    action->setData(MARK_SINGLEWELLCHART_DEL);
    this->addAction(action);

}



