#include "projectOperation.h"

ProjectOperation::ProjectOperation()
{
}

bool ProjectOperation::createFolder(QWidget *parent,QString route)
{
    QDir *folder = new QDir;
    bool exist = folder->exists(route);

    if(exist)
    {
        QMessageBox::warning(parent,"创建工程目录","工程已经存在！");
        return false;
    }
    else
    {
        folder->mkdir(route);

        return true;
    }
}

bool ProjectOperation::createProjectFile(QString route)
{
    QFile file(route);
    if ( file.exists())
    {
        file.close();
            return true;

    }
    file.open( QIODevice::ReadWrite | QIODevice::Text );
    file.close();
    return true;
}

bool ProjectOperation::saveProject(QString projectPath,QList<ExplorationResult*> *explorationResultList,QList<Well*> *wellList
                                   ,QList<Profile*> *profileList,QList<StrataSurface*>*tinList)
{

    QFileInfo fileInfo = QFileInfo(projectPath);
    //osg::ref_ptr<osg::Group> secondNode;
    QFile file(projectPath+"/"+fileInfo.baseName()+".vod");
    QTextStream stream(&file);

//    if(!file.open(QIODevice::WriteOnly))
//    {
//        return false;
//    }



//    stream<<"ExplorationResult"<<endl;

//    for(int i=0;i<explorationResultList->size();i++)
//    {
//        ExplorationResult *explorationResult = explorationResultList->at(i);
//        //写入勘探成果图图片信息
//        osg::ref_ptr<osg::Geometry> geom = explorationResult->getGeometry();
//        osg::Vec3Array* vertexArray = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());

//        //索引
//        stream<<QObject::trUtf8("Exploratory/")<<explorationResult->getName()<<".exp"<<endl;
//        QFile itemFile(projectPath+"/Exploratory/"+explorationResult->getName()+".exp");
//        QTextStream itemStream(&itemFile);

//        if(!itemFile.open(QIODevice::WriteOnly))
//        {
//            return false;
//        }
//        //图片
//        itemStream<<explorationResult->getName()<<".bmp"<<endl;
//        //半透明状态
//        itemStream<<explorationResult->getTransparency()<<endl;
//        //坐标
//        itemStream<<vertexArray->getNumElements()<<endl;
//        for(int j=0;j<vertexArray->getNumElements();j++)
//        {
//            itemStream<<QString::number((*vertexArray)[j].x(),'f')<<","<<QString::number((*vertexArray)[j].y(),'f')<<","<<QString::number((*vertexArray)[j].z(),'f')<<endl;
//        }

//        itemFile.close();

//    }

//    stream<<"Well"<<endl;


//    for(int i=0;i<wellList->size();i++)
//    {
//        Well *well = wellList->at(i);
//        osg::ref_ptr<osg::Geometry> geom = well->getGeometry()->asGeometry();
//       // osg::Vec4Array* colorArray = dynamic_cast<osg::Vec4Array*>(geom->getColorArray());
//        osg::Vec3Array* vertexArray = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());

//        stream<<QObject::trUtf8("Well/")<<well->getWellName()<<".well"<<endl;
//        QFile itemFile(projectPath+"/Well/"+well->getWellName()+".well");
//        QTextStream itemStream(&itemFile);

//        if(!itemFile.open(QIODevice::WriteOnly))
//        {
//            return false;
//        }
//        //井名
//        itemStream<<well->getWellName()<<endl;
//        //井别名
//        itemStream<<well->getWellTypeName()<<endl;
//        //井色坐标
//       /* itemStream<<colorArray->getElementSize()<<endl;
//        for(int j=0;j<colorArray->getElementSize();j++)
//        {
//            itemStream<<QString::number((*colorArray)[j].x(),'f')<<","<<QString::number((*colorArray)[j].y(),'f')<<","
//                     <<QString::number((*colorArray)[j].z(),'f')<<","<<QString::number((*colorArray)[j].w(),'f')<<endl;

//        }*/
//        //井际坐标
//        itemStream<<vertexArray->getNumElements()<<endl;
//        for(int j=0;j<vertexArray->getNumElements();j++)
//        {
//            itemStream<<QString::number((*vertexArray)[j].x(),'f')<<","<<QString::number((*vertexArray)[j].y(),'f')<<","
//                     <<QString::number((*vertexArray)[j].z(),'f')<<endl;
//        }
//        itemFile.close();

//    }
//    stream<<"Profile"<<endl;

//    for(int i=0;i<profileList->size();i++)
//    {
//        Profile *profile = profileList->at(i);
//        osg::ref_ptr<osg::Geometry> geom = profile->getGeometry()->asGeometry();
//        osg::Vec3Array* vertexArray = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
//        osg::Vec2Array* texcoordArray = dynamic_cast<osg::Vec2Array*>(geom->getTexCoordArray(0));

//        //索引
//        stream<<QObject::trUtf8("Profile/")<<profile->getName()<<".prof"<<endl;
//        QFile itemFile(projectPath+"/Profile/"+profile->getName()+".prof");
//        QTextStream itemStream(&itemFile);
//        if(!itemFile.open(QIODevice::WriteOnly))
//        {
//            return false;
//        }
//        //图片
//        itemStream<<profile->getName()<<".bmp"<<endl;
//        itemStream<<vertexArray->getNumElements()<<endl;
//        //坐标
//        for(int j=0;j<vertexArray->getNumElements();j++)
//        {
//            itemStream<<QString::number((*vertexArray)[j].x(),'f')<<","<<QString::number((*vertexArray)[j].y(),'f')<<","<<QString::number((*vertexArray)[j].z(),'f')<<endl;
//        }
//        //纹理
//        itemStream<<texcoordArray->getNumElements()<<endl;
//        for(int j=0;j<texcoordArray->getNumElements();j++)
//        {
//            itemStream<<QString::number((*texcoordArray)[j].x(),'f')<<","<<QString::number((*texcoordArray)[j].y(),'f')<<endl;
//        }
//        itemFile.close();
//    }
//    stream<<"Tin"<<endl;
//    for(int i=0;i<tinList->size();i++)
//    {
//        Tin *tin = tinList->at(i);
//        stream<<QObject::trUtf8("Tin/")<<tin->getName()<<".tins"<<endl;
//    }
//    //索引

//    file.close();
}

osg::ref_ptr<osg::Group> ProjectOperation::openProject(QString projectPath,QList<ExplorationResult*>*explorationResultList,QList<Well*>*wellList
                                                       ,QList<Profile*>*profileList,QList<StrataSurface*>*tinList)
{
    QFileInfo fileInfo = QFileInfo(projectPath);
    QFile file(projectPath+"/"+fileInfo.baseName()+".vod");
    QTextStream stream(&file);
    explorationResultList->clear();
    wellList->clear();
    profileList->clear();
    tinList->clear();

    osg::ref_ptr<osg::Group> root=new osg::Group;
    osg::ref_ptr<osg::Switch> switchExplorationResultNode=new osg::Switch;
    osg::ref_ptr<osg::Switch> switchWellNode=new osg::Switch;
    osg::ref_ptr<osg::Switch> switchProfileNode=new osg::Switch;
    osg::ref_ptr<osg::Switch> switchTinNode = new osg::Switch;
//    float x,y,z;
//    ExplorationResult *explorationResult = new ExplorationResult;
//    Well *well = new Well;
//    Profile *profile = new Profile;
//    Tin *tin = new Tin;
//    root->addChild(switchExplorationResultNode);
//    root->addChild(switchWellNode);
//    root->addChild(switchProfileNode);
//    root->addChild(switchTinNode);


//    if (!file.open(QIODevice::ReadOnly))
//         return NULL;

//    while(!stream.atEnd())
//    {
//        QString str = stream.readLine();

//        if(str=="ExplorationResult")
//        {
//             break;
//        }

//    }
//    //读取勘探成果图
//    while(!stream.atEnd())
//    {
//        QString str = stream.readLine();

//        if(str=="Well")
//            break;

//        QFile explorationResultFile(projectPath+'/'+str);
//        QTextStream explorationResultStream(&explorationResultFile);
//        if (!explorationResultFile.open(QIODevice::ReadOnly))
//             return NULL;
//        QString explorationResultStr = explorationResultStream.readLine();

//        explorationResult = new ExplorationResult;
//        explorationResult->setImagebyURL(projectPath+"/Exploratory/"+explorationResultStr);
//        //读取半透明状态
//        explorationResultStr=explorationResultStream.readLine();
//        explorationResult->setTransparency(explorationResultStr.toInt());
//        //读取坐标信息
//        explorationResultStr = explorationResultStream.readLine();
//        int numberOfVer = explorationResultStr.toInt();
//        for(int i=0;i<numberOfVer;i++)
//        {
//            explorationResultStr = explorationResultStream.readLine();
//            QStringList list=explorationResultStr.split(",");
//            x=list[0].toDouble();
//            y=list[1].toDouble();
//            z=list[2].toDouble();
//            explorationResult->setVertexOBO(x,y,z);
//        }
//        explorationResultList->append(explorationResult);
//        explorationResultFile.close();
//        switchExplorationResultNode->addChild(SwitchNodeFactory::createExplorationResultSwitchNode(explorationResult));
//    }

//    //读取井文件
//    while(!stream.atEnd())
//    {

//        QString str = stream.readLine();

//        if(str=="Profile")
//            break;
//        QFile wellFile(projectPath+'/'+str);
//        QTextStream wellStream(&wellFile);
//        if (!wellFile.open(QIODevice::ReadOnly))
//             return NULL;
//        //读取井名
//        QString wellStr = wellStream.readLine();
//        well = new Well;
//        well->setWellName(wellStr);

//        //读取井别
//        wellStr = wellStream.readLine();
//        well->setWellType(wellStr);

//        //读取井色坐标
//       /* wellStr = wellStream.readLine();
//        int numberOfTex = wellStr.toInt();
//        numberOfTex = wellStr.toInt();
//        for(int i=0;i<numberOfTex;i++)
//        {
//            wellStr = wellStream.readLine();
//            QStringList list=wellStr.split(",");
//            x=list[0].toDouble();
//            y=list[1].toDouble();
//            z=list[2].toDouble();
//            well->setVertexOBO(x,y,z);
//        }*/
//        //读取井点个数坐标
//        wellStr = wellStream.readLine();

//        int numberOfTex = wellStr.toInt();
//        //读取井头坐标
//        wellStr = wellStream.readLine();
//        QStringList list=wellStr.split(",");
//        x=list[0].toDouble();
//        y=list[1].toDouble();
//        z=list[2].toDouble();
//        well->setWellHead(x,y,z);
//        well->setVertexOBO(x,y,z);
//        for(int i=0;i<numberOfTex-1;i++)
//        {
//            wellStr = wellStream.readLine();
//            QStringList list=wellStr.split(",");
//            x=list[0].toDouble();
//            y=list[1].toDouble();
//            z=list[2].toDouble();
//            well->setVertexOBO(x,y,z);
//        }
//        well->drawWell();

//        wellList->append(well);
//        wellFile.close();
//        switchWellNode->addChild(SwitchNodeFactory::createWellSwitchNode(well));

//    }
//    //读取连井剖面图
//    while(!stream.atEnd())
//    {
//        QString str = stream.readLine();

//        if(str=="Tin")
//            break;
//        QFile profileFile(projectPath+'/'+str);
//        QTextStream profileStream(&profileFile);
//        if (!profileFile.open(QIODevice::ReadOnly))
//             return NULL;
//        QString profileStr = profileStream.readLine();
//        profile = new Profile;
//        profile->setImagebyURL(projectPath+"/Profile/"+profileStr);

//        profileStr = profileStream.readLine();
//        int numberOfVer = profileStr.toInt();

//        for(int i=0;i<numberOfVer;i++)
//        {
//            profileStr = profileStream.readLine();
//            QStringList list=profileStr.split(",");
//            x=list[0].toDouble();
//            y=list[1].toDouble();
//            z=list[2].toDouble();
//            profile->setVertexOBO(x,y,z);
//        }
//        profileStr = profileStream.readLine();
//        int numberOfTex = profileStr.toInt();
//        for(int i=0;i<numberOfTex;i++)
//        {
//            profileStr = profileStream.readLine();
//            QStringList list=profileStr.split(",");
//            x=list[0].toDouble();
//            y=list[1].toDouble();
//            profile->setTexCoordArrayOBO(x,y);
//        }
//        profileList->append(profile);
//        profileFile.close();
//        switchProfileNode->addChild(SwitchNodeFactory::createProfileSwitchNode(profile));
//    }
//    //读取地层
//    while(!stream.atEnd())
//    {
//        QString str = stream.readLine();
//        tin=new Tin;
//        tin->setVertexArraybyURL(projectPath+"/"+str);
//        switchTinNode->addChild(SwitchNodeFactory::createTinSwitchNode(tin));
//        tin->setPointColor();
//        tinList->append(tin);
//    }

//    file.close();
    return root;

}
bool ProjectOperation::copyProject(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
       QDir targetDir(toDir);
       if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
           if(!targetDir.mkdir(targetDir.absolutePath()))
               return false;
       }

       QFileInfoList fileInfoList = sourceDir.entryInfoList();
       foreach(QFileInfo fileInfo, fileInfoList){
           if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
               continue;

           if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
               if(!copyProject(fileInfo.filePath(),
                   targetDir.filePath(fileInfo.fileName()),
                   coverFileIfExist))
                   return false;
           }
           else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
               if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                   targetDir.remove(fileInfo.fileName());
               }

               /// 进行文件copy
               if(!QFile::copy(fileInfo.filePath(),
                   targetDir.filePath(fileInfo.fileName()))){
                       return false;
               }
           }
       }
       return true;
}
