#ifndef SWITCHNODEFACTORY_H
#define SWITCHNODEFACTORY_H
#include <tin.h>
#include <strataSurface.h>
#include <well.h>
#include <explorationResult.h>
#include <profile.h>
#include <singlewellchart.h>

class SwitchNodeFactory
{
public:
    SwitchNodeFactory();
    static osg::ref_ptr<osg::Switch> createStrataSurfaceSwitchNode(StrataSurface*);
    static osg::ref_ptr<osg::Switch> createWellSwitchNode(Well *well);
    static osg::ref_ptr<osg::Switch> createExplorationResultSwitchNode(ExplorationResult*);
    static osg::ref_ptr<osg::Switch> createProfileSwitchNode(Profile *);
    static osg::ref_ptr<osg::Switch> createSingleWellChartSwitchNode(SingleWellChart*);

};

#endif // SWITCHNODEFACTORY_H

