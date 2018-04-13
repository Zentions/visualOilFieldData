#include "folderMenu.h"

FolderMenu::FolderMenu()
{
}
FolderMenu::~FolderMenu()
{
}
void FolderMenu::addStrataSurfaceFolderAction()
{

    action  = new QAction(QStringLiteral("名称"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_STRATASURFACE_NAME);
    this->addAction(action);

    action  = new QAction(QStringLiteral("地层面"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_STRATASURFACE_TIN);
    this->addAction(action);
}
void FolderMenu::addWellFolderAction()
{
    action  = new QAction(QStringLiteral("井名"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_WELL_NAME);
    this->addAction(action);

    action  = new QAction(QStringLiteral("井筒"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_WELL_WELL);
    this->addAction(action);

    action  = new QAction(QStringLiteral("井迹"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_WELL_HEAD);
    this->addAction(action);

    action  = new QAction(QStringLiteral("井筒贴图"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_WELL_HEAD);
    this->addAction(action);
}
void FolderMenu::addExplorationResultFolderAction()
{
    action  = new QAction(QStringLiteral("名称"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_EXPLORATIONRESULT_NAME);
    this->addAction(action);

    action  = new QAction(QStringLiteral("成果图"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_EXPLORATIONRESULT_PIX);
    this->addAction(action);
}
void FolderMenu::addProfileFolderAction()
{
    action  = new QAction(QStringLiteral("名称"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_PROFILE_NAME);
    this->addAction(action);

    action  = new QAction(QStringLiteral("剖面图"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_PROFILE_PIX);
    this->addAction(action);
}
void FolderMenu::addSingleWellChartFolderAction()
{
    action  = new QAction(QStringLiteral("名称"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_SINGLEWELLCHART_NAME);
    this->addAction(action);

    action  = new QAction(QStringLiteral("图件"),this);
    action->setCheckable(true);
    action->setChecked(true);
    action->setData(MARK_SINGLEWELLCHART_PIX);
    this->addAction(action);
}

