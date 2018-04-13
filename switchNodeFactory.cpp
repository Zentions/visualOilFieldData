#include "switchNodeFactory.h"

SwitchNodeFactory::SwitchNodeFactory()
{

}

osg::ref_ptr<osg::Switch> SwitchNodeFactory::createStrataSurfaceSwitchNode(StrataSurface* strataSurface)
{
    osg::ref_ptr<osg::Switch> tinSwitch = new osg::Switch;
    tinSwitch->addChild(strataSurface->getText());
    tinSwitch->addChild(strataSurface->getGeometry());
    return tinSwitch;
}
osg::ref_ptr<osg::Switch> SwitchNodeFactory::createWellSwitchNode(Well *well)
{
    osg::ref_ptr<osg::Switch> wellSwitch = new osg::Switch;
//    wellSwitch->addChild(well->getText());
//    wellSwitch->addChild(well->getGeometry());
//    wellSwitch->addChild(well->getWellHead());

    wellSwitch->addChild(well->drawWellTrace());
    wellSwitch->addChild(well->drawWellPipe());
    wellSwitch->addChild(well->drawWellName());
    return wellSwitch;

}osg::ref_ptr<osg::Switch> SwitchNodeFactory::createExplorationResultSwitchNode(ExplorationResult* explorationResult)
{
    osg::ref_ptr<osg::Switch>  explorationResultSwitch = new osg::Switch;
     explorationResultSwitch->addChild( explorationResult->getText());
     explorationResultSwitch->addChild( explorationResult->getGeometry());
    return  explorationResultSwitch;
}

osg::ref_ptr<osg::Switch> SwitchNodeFactory::createProfileSwitchNode(Profile * profile)
{
    osg::ref_ptr<osg::Switch> profileSwitch = new osg::Switch;
    profileSwitch->addChild(profile->getText());
    profileSwitch->addChild(profile->getGeometry());
    return profileSwitch;
}
osg::ref_ptr<osg::Switch> SwitchNodeFactory::createSingleWellChartSwitchNode(SingleWellChart *singlewellchart)
{
    osg::ref_ptr<osg::Switch> singlewellchartswitch = new osg::Switch;
//    singlewellchartswitch->addChild(singlewellchart->getText());
    singlewellchartswitch->addChild(singlewellchart->getGeode());
    return singlewellchartswitch;
}
