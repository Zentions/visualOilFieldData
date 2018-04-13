#ifndef ITEMMENU_H
#define ITEMMENU_H

#include <QMenu>
#include <QAction>
#include <QModelIndex>
#include <QVariant>
#include <QCursor>
#include <QtCore>

#include <osg/Group>
#include <osg/ref_ptr>
#include "common.h"

class ItemMenu : public QMenu
{
public:
    ItemMenu();
    ~ItemMenu();

    void addStrataSurfaceItemAction(bool);
    void addWellItemAction();
    void addProfileItemAction();
    void addExplorationResultItemAction();
    void addSingleWellChartItemAction();
protected:

    QAction *action;
};

#endif // ITEMMENU_H
