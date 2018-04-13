#ifndef FOLDERMENU_H
#define FOLDERMENU_H

#include <QMenu>
#include <QAction>
#include <QModelIndex>
#include <QVariant>
#include <QCursor>
#include <QtCore>

#include <osg/Group>
#include <osg/ref_ptr>
#include "common.h"

class FolderMenu : public QMenu
{
public:
    FolderMenu();
    ~FolderMenu();

    void addStrataSurfaceFolderAction();
    void addWellFolderAction();
    void addProfileFolderAction();
    void addExplorationResultFolderAction();
    void addSingleWellChartFolderAction();
protected:

    QAction *action;

};

#endif // FOLDERMENU_H
