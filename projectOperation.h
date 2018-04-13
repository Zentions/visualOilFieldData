#ifndef PROJECTOPERATION_H
#define PROJECTOPERATION_H
#include <iomanip>
#include <QDir>
#include <QMessageBox>
#include <QWidget>
#include <QDebug>
#include <QDataStream>
#include <QTextStream>
#include <QFileInfo>

#include <osg/ref_ptr>
#include <osg/Group>
#include <osg/Switch>
#include <osgText/Text>

#include "explorationResult.h"
#include "well.h"
#include "profile.h"
#include "tin.h"

#include "switchNodeFactory.h"



class ProjectOperation
{
public:
    ProjectOperation();
    static bool createFolder(QWidget*parent,QString route);
    static bool createProjectFile(QString route);
    static bool saveProject(QString projectPath,QList<ExplorationResult*>*,QList<Well*>*,QList<Profile*>*,QList<StrataSurface*>*);
    static osg::ref_ptr<osg::Group> openProject(QString projectPath,QList<ExplorationResult*>*,QList<Well*>*,QList<Profile*>*,QList<StrataSurface*>*);
    static bool copyProject(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
};

#endif // PROJECTOPERATION_H
