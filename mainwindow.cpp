#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "texturedialog.h"
#include <QInputDialog>
float MainWindow::bian=1000;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化右键菜单
//    explorationResultFolderMenu = new ExplorationResultFolderMenu;
//    wellFolderMenu = new WellFolderMenu;
//    profileFolderMenu = new ProfileFolderMenu;
//    tinFolderMenu = new TinFolderMenu;
    explorationResultFolderMenu = new FolderMenu;
    wellFolderMenu = new FolderMenu;
    profileFolderMenu = new FolderMenu;
    strataSurfaceFolderMenu = new FolderMenu;
    singleWellChartFolderMenu = new FolderMenu;

    explorationResultFolderMenu->addExplorationResultFolderAction();
    wellFolderMenu->addWellFolderAction();
    profileFolderMenu->addProfileFolderAction();
    strataSurfaceFolderMenu->addStrataSurfaceFolderAction();
    singleWellChartFolderMenu->addSingleWellChartFolderAction();

    explorationResultItemMenu = new ItemMenu;
    wellItemMenu = new ItemMenu;
    profileItemMenu = new ItemMenu;
    strataSurfaceItemMenu = new ItemMenu;
    singleWellChartItemMenu = new ItemMenu;

    explorationResultItemMenu->addExplorationResultItemAction();
    wellItemMenu->addWellItemAction();
    profileItemMenu->addProfileItemAction();
    strataSurfaceItemMenu->addStrataSurfaceItemAction(false);
    singleWellChartItemMenu->addSingleWellChartItemAction();

    //初始化工程窗口
    projectDialog = new ProjectDialog;

    groupnext = new osg::Group;

    init();

     //新建项目时对树的操作
    connect(ui->treeView,SIGNAL(stateChanged(int,int,int,bool)),this,SLOT(changeState(int,int,int,bool)));
    //工程命名
    //connect(projectDialog,SIGNAL(sendData(QString,QList<QCheckBox*>*)),this,SLOT(receiveData(QString,QList<QCheckBox*>*)));
    connect(projectDialog,SIGNAL(sendData(QString,QList<PROJECTITEM*>*)),this,SLOT(receiveData(QString,QList<PROJECTITEM*>*)));
    //connect(projectDialog,SIGNAL(sendData(QString,QList<QCheckBox*>*)),this,SLOT(reCreate()));

    //对类别文件夹的操作
    //connect(projectDialog,SIGNAL(sendData(QString,QString,QList<PROJECTITEM*>*)), ui->treeView,SLOT(addChild(QString,QString,QList<PROJECTITEM*>*)));
    connect(explorationResultFolderMenu,SIGNAL(triggered(QAction*)), ui->treeView,SLOT(treeItem_CheckActionTriggerd(QAction*)) );
    connect(wellFolderMenu,SIGNAL(triggered(QAction*)), ui->treeView,SLOT(treeItem_CheckActionTriggerd(QAction*)) );
    connect(profileFolderMenu,SIGNAL(triggered(QAction*)), ui->treeView,SLOT(treeItem_CheckActionTriggerd(QAction*)) );
    connect(strataSurfaceFolderMenu,SIGNAL(triggered(QAction*)), ui->treeView,SLOT(treeItem_CheckActionTriggerd(QAction*)) );
    connect(singleWellChartFolderMenu,SIGNAL(triggered(QAction*)), ui->treeView,SLOT(treeItem_CheckActionTriggerd(QAction*)) );

    //对节点的操作
    connect(explorationResultItemMenu,SIGNAL(triggered(QAction*)),this,SLOT(operateExplorationResultItem(QAction*)));
    connect(wellItemMenu,SIGNAL(triggered(QAction*)),this,SLOT(operateWellItem(QAction*)));
    connect(profileItemMenu,SIGNAL(triggered(QAction*)),this,SLOT(operateProfileItem(QAction*)));
    connect(strataSurfaceItemMenu,SIGNAL(triggered(QAction*)),this,SLOT(operateStrataSurfaceItem(QAction*)));
    connect(singleWellChartItemMenu,SIGNAL(triggered(QAction*)),this,SLOT(operateSingleWellChartItem(QAction*)));

    //对树的宽度调整
    connect(ui->treeView,SIGNAL(clicked(const QModelIndex&)),this,SLOT(adjustTreeWidth(const QModelIndex &)));
    connect(ui->treeView,SIGNAL(collapsed(const QModelIndex&)),this,SLOT(adjustTreeWidth(const QModelIndex &)));
    connect(ui->treeView,SIGNAL(expanded(const QModelIndex&)),this,SLOT(adjustTreeWidth(const QModelIndex &)));


    //设置初始状态的角度
   // setPosition();
}

MainWindow::~MainWindow()
{
    delete ui;
}




//接受treeview中复选框发生变化的item的所在组type以及所在行row以改变节点的可见性
void MainWindow::changeState(int grandParentRow,int parentRow,int row,bool checked)
{
    group->getChild(grandParentRow)->asSwitch()->getChild(parentRow)->asSwitch()->setValue(row,checked);
}

void MainWindow::openFile(QString name)
{
    osg::ref_ptr<osg::DrawPixels> bmp= new osg::DrawPixels;
    bmp->setPosition( osg::Vec3( 0.0, 0.0, 0.0));
    bmp->setImage( osgDB::readImageFile(name.toStdString()));
    osg::ref_ptr< osg::Geode> geode= new osg::Geode;
    geode->addDrawable( bmp.get());
    osgViewer::Viewer viewer;
    viewer.setSceneData(geode.get());
}



void MainWindow::on_Revocation_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\avatar.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Restore_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\bignathan.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_table_of_Contents_triggered()
{  

//    //创建一个节点，读取模型
//    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("E:\\OSGTest\\work.osgb");

//    this->ui->graphicsView->setNode(node->asGroup());


}

void MainWindow::on_Index_triggered()
{

//     osgDB::writeNodeFile(*group->asNode(), "E:\\OSGTest\\work.osgb", new osgDB::Options("WriteImageHint=IncludeData Compressor=zlib"));
}

void MainWindow::on_Online_Help_triggered()
{
    //测试选择配色方案
    StrataSurface * stra = this->strataSurfaceList->at(0);

    stra->setColorSet();
}


void MainWindow::on_Pick_up_triggered()
{
        //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\example.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Drag_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\lz.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_extend_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\morphing.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_merge_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\morphtarget_shape0.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_delete_2_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\morphtarget_shape1.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_copy_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\nathan.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Cutting_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\robot.osg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Property_superposition_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\axes.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Unselected_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\clock.osgt");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}


void MainWindow::on_reduction_triggered()
{
    ui->graphicsView->adjustCamera();
}

void MainWindow::on_whirl_alone_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glsl_julia.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_whirl_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glsl_mandelbrot.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_panoramic_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glsl_simple.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Bottom_view_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\skydome.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Parallel_projection_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\SmokeBox.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Perspective_projection_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\spaceship.osgt");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_enlarge_triggered()
{
    osg::ref_ptr<osg::Node> mModel=new osg::Node();
    osg::ref_ptr<osgViewer::Viewer> m_vViewer=new osgViewer::Viewer();

    //调整相机，使模型居中显示
    double radius = mModel->getBound().radius();
    double viewDistance = radius/5;

    //方向向上
    osg::Vec3d up( 0.0,0.0,1.0 );//osg右x,前y,上z,opengl由osg绕x轴向外旋转90°,

    osg::Vec3d viewDirection( 0.0,-1.0,0.5 );
    //相机盯着的那个点（目标点，相当于靶心），不一定就是包围球的中点，也可以是场景的原点，这个看情况
    osg::Vec3d center = mModel->getBound().center();
    //眼睛的位置=目标点+离目标点的距离
    osg::Vec3d eye = center + viewDirection * viewDistance;
    //相机设置矩阵
    m_vViewer->getCameraManipulator()->setHomePosition(eye,center,up);
    m_vViewer->home();

    //m_vViewer->getCameraManipulator()->computeHomePosition();
    //m_vViewer->getCameraManipulator()->home( 0.0 );
}

void MainWindow::on_Narrow_triggered()
{
    osgViewer::Viewer viewer;
    osg::ref_ptr<osg::Group> root = new osg::Group;
    osg::ref_ptr<osg::Node> osgcool = osgDB::readNodeFile("cow.osg");

    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;//定义变换矩阵
    trans->addChild(osgcool.get());

    osg::ref_ptr<osg::MatrixTransform> scale = new osg::MatrixTransform;
    scale->setMatrix(osg::Matrix::scale(0.5, 0.5, 0.5) * osg::Matrix::translate(0, 0, -2));//实现模型缩放
    scale->addChild(osgcool.get());

    root->addChild(osgcool.get());
    root->addChild(trans.get());
    root->addChild(scale.get());

    viewer.setSceneData(root.get());
    viewer.realize();
    viewer.run();
}



void MainWindow::on_Outsourcing_box_triggered()
{
        //创建Viewer对象，场景浏览器
            osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
            //创建场景组节点
            osg::ref_ptr<osg::Group>root=new osg::Group();
            //创建一个节点，读取模型
            osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\TabWidget.lua");
            //添加到场景
            root->addChild(node.get());
            //优化场景数据
            osgUtil::Optimizer optimizer;
            optimizer.optimize(root.get());
            //设置场景数据
            viewer->setSceneData(root.get());
            //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
            viewer->setUpViewInWindow(50,50,1024,768);
            //开始渲染
            viewer->run();
}

void MainWindow::on_XYZ_triggered()
{
    huatu();
}

void MainWindow::on_Staff_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\VolumeEditor.lua");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_North_view_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\VolumeEditorWidget.lua");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Wellhead_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\VolumeSettings.lua");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();

}

void MainWindow::on_Well_trajectory_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\ui\\WidgetUtils.lua");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Logs_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\SolarSystem\\earth_clouds256128.jpg");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Perforation_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\shaders\\blocky.frag");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Stratified_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\shaders\\blocky.vert");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Reservoir_Simulation_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\osgWidget\\back.png");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Geological_model_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\osgWidget\\border-bottom.tga");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_crack_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\osgWidget\\osgwidgetshader-frag.glsl");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_color_triggered()
{
    /*colorBtn=new QPushButton;
    colorBtn->setText(tr("choose the color"));//pushbutton按钮名称
    colorFrame=new QFrame;
    colorFrame->setFrameShape(QFrame::Box);
    colorFrame->setAutoFillBackground(true);
    mainLayout=new QGridLayout(this);
    mainLayout->addWidget(colorBtn,1,0);//初始化0,0，布局设计
    mainLayout->addWidget(colorFrame,1,1);//初始化0,1
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(showColor()));//事件关联*/
    osg::ref_ptr<osg::Camera>camera=new osg::Camera;

    camera->setClearColor( osg::Vec4(0.0, 0.0, 1.0, 1.0) );

}


void MainWindow::on_Hide_Show_triggered()
{
    osg::ref_ptr<osg::Geometry> geo=new osg::Geometry;
    osg::Vec4Array*colarray=new osg::Vec4Array;//颜色RGB值数组
    osg::UByteArray*colindex=new osg::UByteArray;//颜色索引数组

    colarray->push_back(osg::Vec4(1.0,0.0,0.0,1.0));//Red
    colarray->push_back(osg::Vec4(0.0,1.0,0.0,1.0));//Green
    colarray->push_back(osg::Vec4(0.0,0.0,1.0,1.0));//Blue
    colarray->push_back(osg::Vec4(1.0,1.0,1.0,1.0));//White

    colindex->push_back(3);
    colindex->push_back(2);
    colindex->push_back(1);
    colindex->push_back(0);

    geo->setColorArray(colarray);
    geo->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

}

void MainWindow::on_move_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\Images\\Brick-Norman-Brown.TGA");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_Light_control_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\Images\\continous_smoke.rgb");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_drilling_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\fonts\\arial.ttf");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_profile_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\Configuration\\3DSphericalDisplay.view");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_well_deviation_triggered()
{
    //创建Viewer对象，场景浏览器
        osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
        //创建场景组节点
        osg::ref_ptr<osg::Group>root=new osg::Group();
        //创建一个节点，读取模型
        osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\Configuration\\3DSphericalDisplay.view");
        //添加到场景
        root->addChild(node.get());
        //优化场景数据
        osgUtil::Optimizer optimizer;
        optimizer.optimize(root.get());
        //设置场景数据
        viewer->setSceneData(root.get());
        //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
        viewer->setUpViewInWindow(50,50,1024,768);
        //开始渲染
        viewer->run();
}

void MainWindow::on_straight_line_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\cow.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_text_editor_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Draw_boundary_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Generate_contours_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_layer_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Structural_map_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Thematic_map_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_point_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_line_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_surface_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_body_part_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Sphere_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_cuboid_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Ellipsoid_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Cone_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Cylinder_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Yuantong_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}

void MainWindow::on_Ring_triggered()
{
    //创建Viewer对象，场景浏览器
    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
    //创建场景组节点
    osg::ref_ptr<osg::Group>root=new osg::Group();
    //创建一个节点，读取牛的模型
    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("C:\\OSG\\OSG-Data\\glider.osg");
    //添加到场景
    root->addChild(node.get());
    //优化场景数据
    osgUtil::Optimizer optimizer;
    optimizer.optimize(root.get());
    //设置场景数据
    viewer->setSceneData(root.get());
    //设置窗口的大小，但是只是单线程，打开窗口后，控制面板不能用，需要写成多线程。
    viewer->setUpViewInWindow(50,50,1024,768);
    //开始渲染
    viewer->run();
}
//从osg::NodeCallBack继承一个新类，实现simpleCallBack的回调
class simpleCallBack:public osg::NodeCallback
{
public:
    simpleCallBack():_angle(0){}

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        //创建矩阵转换节点
        osg::ref_ptr<osg::MatrixTransform> mt=dynamic_cast<osg::MatrixTransform*>(node);
        //创建矩阵
        osg::Matrix mx;
        //绕着Z轴旋转
        mx.makeRotate(_angle,osg::Vec3(0.0,0.0,1.0));
        //设置矩阵
        mt->setMatrix(mx);

        _angle+=0.01;

        //继续遍历
        traverse(node,nv);

    }

public:
    //旋转角度
    double _angle;
};
//根据树中item文字的长度调整树的宽度，实际是列宽
void MainWindow::adjustTreeWidth(const QModelIndex &index)
{
    ui->treeView->resizeColumnToContents(0);
}
//根据用户选择的项目，添加对应目录到树
void MainWindow::receiveData(QString path,QList<PROJECTITEM*> *itemList)
{

    //在此创建树
    treeCreated = true;
    projectPath = path;
    fileInfo = QFileInfo(path);
    this->itemTypeList = itemList;
    for(int i=0;i<itemList->size();i++)
    {
        this->addSwitchNode(itemList->at(i)->type);
    }

    ui->treeView->addChild(fileInfo.baseName(), path, itemList);
}

//重新创建场景
void MainWindow::reCreate()
{
  init();
  treeCreated=true;
}

void MainWindow::setPosition()
{
    osg::Quat quat;
    quat.makeRotate(osg::PI_4,osg::Vec3(1.0,0.0,0.0));
    posNode->setAttitude(quat);

}

//获取要进行右键操作的对象
void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{

    QModelIndex index = ui->treeView->indexAt(pos);
    temppos = pos;
    QVariant FolderVar = index.data(ROLE_MARK_FOLDER);
    QVariant ItemVar = index.data(ROLE_MARK_ITEM);

    if(FolderVar.isValid())
    {

        switch(FolderVar.toInt())
        {
        case MARK_FOLDER_EXPLORATIONRESULT:
            explorationResultFolderMenu->exec(QCursor::pos());
            break;
        case MARK_FOLDER_WELL:
            wellFolderMenu->exec(QCursor::pos());
            break;
        case MARK_FOLDER_PROFILE:
            profileFolderMenu->exec(QCursor::pos());
            break;
        case MARK_FOLDER_STRATASURFACE:
            strataSurfaceFolderMenu->exec(QCursor::pos());
            break;
        }

    }
    if(ItemVar.isValid())
    {
        switch(ItemVar.toInt())
        {
        case MARK_ITEM_EXPLORATIONRESULT:
        {
            //修改半透明是否被选中
            QModelIndex index = ui->treeView->indexAt(pos);
            ExplorationResult *explorationResult = explorationResultList->at(index.row());
            QAction *transparencyAction = explorationResultItemMenu->actions().at(1);
            transparencyAction->setChecked(explorationResult->isTransparency());

            explorationResultItemMenu->exec(QCursor::pos());

            break;
        }
        case MARK_ITEM_WELL:
            wellItemMenu->exec(QCursor::pos());
            break;
        case MARK_ITEM_PROFILE:
        {
            //修改半透明是否被选中
            QModelIndex index = ui->treeView->indexAt(pos);
            Profile *profile = profileList->at(index.row());
            QAction *transparencyAction =  profileItemMenu->actions().at(1);
            transparencyAction->setChecked(profile->isTransparency());

            profileItemMenu->exec(QCursor::pos());
            break;
        }

        case MARK_ITEM_STRATASURFACE:
            {
            //修改半透明是否被选中
            QModelIndex index = ui->treeView->indexAt(pos);
            StrataSurface *stratasurface = strataSurfaceList->at(index.row());
            QAction *transparencyAction =  strataSurfaceItemMenu->actions().at(1);
            transparencyAction->setChecked(stratasurface->isTransparency());

            strataSurfaceItemMenu->exec(QCursor::pos());
            break;
            }
        }

    }
}
//操作勘探成果图节点
void MainWindow::operateExplorationResultItem(QAction *action)
{

    QVariant MenuVar = action->data();

    //得到树上对象的index
    QModelIndex index = ui->treeView->indexAt(temppos);



    if(MenuVar.isValid())
    {
        if(MARK_EXPLORATIONRESULT_DEL==MenuVar.toInt())
        {
            switchExplorationResultNode->removeChild(switchExplorationResultNode->getChild(index.row()));
            QFile::remove(projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT)+"/"+explorationResultList->at(index.row())->getFileName());
            QFile::remove(projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT)+"/"+explorationResultList->at(index.row())->getName());

            explorationResultList->removeAt(index.row());
            ui->treeView->deleteExplorationResultItem(index);
            //ProjectOperation::saveProject(projectPath,explorationResultList,wellList,profileList,tinList);

          //  counter--;
        }
        else if(MARK_EXPLORATIONRESULT_TRANSPARENT==MenuVar.toInt())
        {
            //修改半透明
            ExplorationResult *explorationResult = explorationResultList->at(index.row());

             explorationResult->setTransparency(!explorationResult->isTransparency());

        }
        else if(MARK_EXPLORATIONRESULT_CHANGEMODE==MenuVar.toInt())
        {
            //改变成果图显示模式
            ExplorationResult *explorationResult = explorationResultList->at(index.row());
            int mode = explorationResult->getMode();
            explorationResult->changeMode((mode+1)%3);

        }


    }

  //  ui->graphicsView->adjustCamera();
}
//操作综合柱状图节点
void MainWindow::operateSingleWellChartItem(QAction *action)
{

    QVariant MenuVar = action->data();

    //得到树上对象的index
    QModelIndex index = ui->treeView->indexAt(temppos);


    if(MenuVar.isValid())
    {
        if(MARK_SINGLEWELLCHART_DEL==MenuVar.toInt())
        {
            switchCColumnNode->removeChild(switchCColumnNode->getChild(index.row()));

//            QFile::remove(projectPath+"/"+getFolderNameByType(MARK_TYPE_CCOLUMN)+"/"+singleWellChartList->at(index.row())->getFileName());
//            QFile::remove(projectPath+"/"+getFolderNameByType(MARK_TYPE_CCOLUMN)+"/"+singleWellChartList->at(index.row())->getName());

//            explorationResultList->removeAt(index.row());
            ui->treeView->deleteCColumnItem(index);

        }
    }

}
bool isTrue(QString name){
    string t = name.toStdString();
    for(int i = 0;i <t.length();i++){
        if((name[i]>='0'&& name[i]<='9')||name[i]==';'||name[i]=='.' ||name[i]=='-'){
        }else{
            return false;
        }
    }
    return true;
}
//操作井节点
void MainWindow::operateWellItem(QAction *action)
{
    QVariant MenuVar = action->data();
    QModelIndex index = ui->treeView->indexAt(temppos);

    if(MenuVar.isValid())
    {
        if(MARK_WELL_DEL==MenuVar.toInt())
        {
            switchWellNode->removeChild(switchWellNode->getChild(index.row()));
            QFile::remove(projectPath+"/"+getFolderNameByType(MARK_TYPE_WELL)+"/"+QString(wellList->at(index.row())->getWellName()));

            wellList->removeAt(index.row());
            ui->treeView->deleteWellItem(index);
//            ProjectOperation::saveProject(projectPath,explorationResultList,wellList,profileList,strataSurfaceList);

        }
        else if(MARK_WELL_CHANGEPIC==MenuVar.toInt())
        {
            //改变贴图模式
            qDebug()<<"改变贴图模式";
            Well *well =   wellList->at(index.row());



            if(well->getWellPipeConduit_textureImage()==NULL);//return false;
            else
            {
                if(well->getMode()==0) well->setAllTexture(well->getWellPipe());
                else if(well->getMode()==1)
                {
                    bool ok;
                    QString name = QInputDialog::getText(this,
                                                            tr("贴图深度"),
                                                            tr("请输入两个数字，并以英文';'隔开"),
                                                            QLineEdit::Normal,
                                                            "0.0;0.0",
                                                            &ok);
                    if(ok && !name.isEmpty() && isTrue(name)) {
                    QStringList strList;
                    strList= name.split(";");
                    double start = strList[0].toDouble();
                    double end = strList[1].toDouble();
                    std::cout<<start<<" "<<end<<std::endl;
                    if(well->setPartRepeatTexture(well->getWellPipe(),10,start,end)==-1){
                        QMessageBox::information(this,"Error Message","深度不在范围之内");
                    }
                    }else{
                        QMessageBox::information(this,"Error Message","输入数字格式错误");
                        return;
                    }
               }

               else if(well->getMode()==2)well->setRepeatTexture(well->getWellPipe(),10);
               else if(well->getMode()==3)
               {
                    bool ok;
                    QString name = QInputDialog::getText(this,
                                                        tr("贴图深度"),
                                                        tr("请输入两个数字，并以英文';'隔开"),
                                                        QLineEdit::Normal,
                                                        "0.0;0.0",
                                                        &ok);
                     if(ok && !name.isEmpty() && isTrue(name)) {
                          QStringList strList;
                          strList= name.split(";");
                          double start = strList[0].toDouble();
                          double end = strList[1].toDouble();
                          std::cout<<start<<" "<<end<<std::endl;
                          if(well->setPartTexture(well->getWellPipe(),start,end)==-1){
                              QMessageBox::information(this,"Error Message","深度不在范围之内");
                          }
                     }else{
                         QMessageBox::information(this,"Error Message","输入数字格式错误");
                         return;
                     }
                }
                else if(well->getMode()==4)
                {
                    TextureDialog *textureDialog = new TextureDialog(well->getWellTrace_dataXYZ()->begin()->z(),well->getWellTrace_dataXYZ()->end()->z());
                    if (textureDialog->exec() == QDialog::Accepted) {
                        QList<Data> list = textureDialog->getQList();
                        std::cout<<list.size()<<std::endl;
                        for(int i = 0;i<list.size();i++){

                           if(well->setPartsTexture(well->getWellPipe(),list[i].start.toDouble(),list[i].end.toDouble(),osgDB::readImageFile(list[i].path.toStdString()))==-1){
                              //return false;
                           }
                        }
                    }
                    delete textureDialog;
                }

            }



        }
        else if(MARK_WELL_SELECTPIC==MenuVar.toInt())
        {

            qDebug()<<"选择贴图";
             Well *well =   wellList->at(index.row());
            QString fileName = QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath(),"*.bmp");
            if(fileName!=NULL) {
                well->setWellPipeConduit_textureImage(osgDB::readImageFile(fileName.toStdString()));
              //  well->saveWell(projectPath+"//"+getFolderNameByType(MARK_TYPE_WELL));
                QMessageBox::about(this,tr("确认提示框"),tr("图片加载成功!"));
             }else{
                 QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
             }
        }


    }

   // counter--;
   // ui->graphicsView->adjustCamera();
}
//操作连井剖面图节点
void MainWindow::operateProfileItem(QAction *action)
{
    QVariant MenuVar = action->data();

    //得到树上对象的index
    QModelIndex index = ui->treeView->indexAt(temppos);

    if(MenuVar.isValid())
    {
        if(MARK_PROFILE_DEL==MenuVar.toInt())
        {
            QModelIndex index = ui->treeView->indexAt(temppos);

            switchProfileNode->removeChild(switchProfileNode->getChild(index.row()));
            QFile::remove(projectPath+"/"+getFolderNameByType(MARK_TYPE_PROFILE)+"/"+profileList->at(index.row())->getFileName());
            QFile::remove(projectPath+"/"+getFolderNameByType(MARK_TYPE_PROFILE)+"/"+profileList->at(index.row())->getName());

            profileList->removeAt(index.row());
            ui->treeView->deleteProfileItem(index);
            //ProjectOperation::saveProject(projectPath,explorationResultList,wellList,profileList,tinList);

        }
        else if(MARK_PROFILE_TRANSPARENT==MenuVar.toInt())
        {
           // if(Action)
            //修改半透明
            Profile *profile = profileList->at(index.row());

             profile->setTransparency(!profile->isTransparency());

        }
    }
   // ui->graphicsView->adjustCamera();
}

void MainWindow::operateStrataSurfaceItem(QAction *action)
{
    QVariant MenuVar = action->data();
    //得到树上对象的index
    QModelIndex index = ui->treeView->indexAt(temppos);
    if(MenuVar.isValid())
    {
        if(MARK_STRATASURFACE_DEL==MenuVar.toInt())
        {
            switchStrataSurfaceNode->removeChild(switchStrataSurfaceNode->getChild(index.row()));
//            QFile::remove(projectPath+"/"+getFolderNameByType(MARK_TYPE_STRATASURFACE)+"/"+strataSurfaceList->at(index.row())->getName()+".tins");

            strataSurfaceList->removeAt(index.row());

            ui->treeView->deleteStrataSurfaceItem(index);
//            ProjectOperation::saveProject(projectPath,explorationResultList,wellList,profileList,strataSurfaceList);


           // QFile::remove("E:/孤东开发现状/孤东开发现状2/Tin/sand_06049_2010_350.tins");

          //  counter--;
        }
        else if(MARK_STRATASURFACE_TRANSPARENT==MenuVar.toInt())
        {

//             action->setChecked(action->isChecked());
             StrataSurface *strataSurface = strataSurfaceList->at(index.row());
             strataSurface->setHalfTransparency(!strataSurface->isTransparency());

        }
        else if(MARK_STRATASURFACE_PROPERTY==MenuVar.toInt())
        {
            StrataSurface *strataSurface = strataSurfaceList->at(index.row());
            strataSurface->choseProperty();
        }
        else if(MARK_STRATASURFACE_COLORSET==MenuVar.toInt())
        {
            StrataSurface *strataSurface = strataSurfaceList->at(index.row());
            strataSurface->setColorSet();
        }

    }

  //  ui->graphicsView->adjustCamera();
}
void MainWindow::init()
{
    //初始化根节点
    group=new osg::Group;
    //初始化变化节点
    posNode = new osg::PositionAttitudeTransform;

    //树建立与否的标志
    treeCreated=false;

    //记录历史路径，默认为当前路径
    this->historyPath = QDir::currentPath();



    //初始化开关节点
    switchStrataSurfaceNode = new osg::Switch;
    switchFaultNode=new osg::Switch;
    switchWellNode=new osg::Switch;
    switchSModelNode=new osg::Switch;
    switchVModelNode=new osg::Switch;
    switchExplorationResultNode=new osg::Switch;
    switchProfileNode=new osg::Switch;
    switchCColumnNode = new osg::Switch;

    switchStrataSurfaceNode->setName("switchStrataSurfaceNode");
    switchFaultNode->setName("switchFaultNode");
    switchWellNode->setName("switchWellNode");
    switchSModelNode->setName("switchSModelNode");
    switchVModelNode->setName("switchVModelNode");
    switchExplorationResultNode->setName("switchExplorationResultNode");
    switchProfileNode->setName("switchProfileNode");
    switchCColumnNode->setName("switchCColumnNode");
    //添加变换节点
//    group->addChild(switchExplorationResultNode);
//    group->addChild(switchWellNode);
//    group->addChild(switchProfileNode);
//    group->addChild(switchTinNode);
    ui->graphicsView->setNode(group);
    ui->graphicsView->getOSGViewer()->getCamera()->setClearColor(osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
//    //反走样（抗锯齿）
//    osg::ref_ptr< osg::DisplaySettings > displaySettings = new osg::DisplaySettings;
//    displaySettings->setNumMultiSamples(16);
//    ui->graphicsView->getOSGViewer()->setDisplaySettings( displaySettings.get());

    //初始化对象容器
    explorationResultList = new QList<ExplorationResult*>;
    wellList = new QList<Well*>;
    profileList = new QList<Profile*>;
    strataSurfaceList = new QList<StrataSurface*>;
    singleWellChartList = new QList<SingleWellChart*>;

}


void MainWindow::on_AssistantView_triggered()
{

}
void MainWindow::addSwitchNode(int type)
{
    switch(type)
    {
    case MARK_TYPE_STRATASURFACE:
        group->addChild(switchStrataSurfaceNode);
        break;
    case MARK_TYPE_FAULT:
        group->addChild(switchFaultNode);
        break;
    case MARK_TYPE_WELL:
        group->addChild(switchWellNode);
        break;
    case MARK_TYPE_SMODEL:
        group->addChild(switchSModelNode);
        break;
    case MARK_TYPE_VMODEL:
        group->addChild(switchVModelNode);
    case MARK_TYPE_EXPLORATIONRESULT:
        group->addChild(switchExplorationResultNode);
        break;
    case MARK_TYPE_PROFILE:
        group->addChild(switchProfileNode);
        break;
    case MARK_TYPE_CCOLUMN:
        group->addChild(switchCColumnNode);
        break;
    }

}

//新建工程
void MainWindow::on_createProject_triggered()
{
    projectDialog->setTypeName("工程");

    projectDialog->show();

}
//保存工程
void MainWindow::on_saveProject_triggered()
{
    //判断是否有根目录
    if(!treeCreated)
    {
        QMessageBox::information(this,"Error Message","请先添加一个工程");
        return ;
    }
    //ProjectOperation::saveProject(projectPath,explorationResultList,wellList,profileList,tinList);

    QFileInfo fileInfo = QFileInfo(projectPath);


    QFile file(projectPath+"/"+fileInfo.baseName()+".vod");
    QTextStream stream(&file);
    if(!file.open(QIODevice::WriteOnly))
    {
        return ;
    }

    stream<<"TypeNum "<<itemTypeList->size()<<endl;
    for(int i=0;i<itemTypeList->size();i++)
    {
        stream<<itemTypeList->at(i)->name<<" "<<itemTypeList->at(i)->text<<" "<<itemTypeList->at(i)->type<<endl;
    }

    for(int i=0;i<itemTypeList->size();i++)
    {
        switch(itemTypeList->at(i)->type)
        {
        case MARK_TYPE_STRATASURFACE:
            if(strataSurfaceList->size()<=0)
                break;

            stream<<"Type "<<MARK_TYPE_STRATASURFACE<<" begin "<<strataSurfaceList->size()<<endl;
            for(int j=0;j<strataSurfaceList->size();j++)
            {
                stream<<"Object "<<j<<" begin"<<endl;
                stream<<strataSurfaceList->at(j)->getName()<<endl;
                stream<<"Object "<<j<<" end"<<endl;
                strataSurfaceList->at(j)->saveTo(projectPath+"/"+getFolderNameByType(MARK_TYPE_STRATASURFACE));
            }
            stream<<"Type "<<MARK_TYPE_STRATASURFACE<<" end"<<endl;
            break;
        case MARK_TYPE_EXPLORATIONRESULT:
            if(explorationResultList->size()<=0)
                break;

            stream<<"Type "<<MARK_TYPE_EXPLORATIONRESULT<<" begin "<<explorationResultList->size()<<endl;
            for(int j=0;j<explorationResultList->size();j++)
            {
                stream<<"Object "<<j<<" begin"<<endl;
                stream<<explorationResultList->at(j)->getFileName()<<endl;
                stream<<"Object "<<j<<" end"<<endl;
                explorationResultList->at(j)->saveTo(projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT));
//                explorationResultList->at(j)->saveInByte(projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT));
            }
            stream<<"Type "<<MARK_TYPE_EXPLORATIONRESULT<<" end"<<endl;
            break;
        case MARK_TYPE_PROFILE:
            if(explorationResultList->size()<=0)
                break;

            stream<<"Type "<<MARK_TYPE_PROFILE<<" begin "<<profileList->size()<<endl;
            for(int j=0;j<profileList->size();j++)
            {
                stream<<"Object "<<j<<" begin"<<endl;
                stream<<profileList->at(j)->getFileName()<<endl;
                stream<<"Object "<<j<<" end"<<endl;
                profileList->at(j)->saveTo(projectPath+"/"+getFolderNameByType(MARK_TYPE_PROFILE));
            }
            stream<<"Type "<<MARK_TYPE_PROFILE<<" end"<<endl;
            break;
        case MARK_TYPE_CCOLUMN:
            if(singleWellChartList->size()<=0)
                break;

            stream<<"Type "<<MARK_TYPE_CCOLUMN<<" begin "<<singleWellChartList->size()<<endl;
            for(int j=0;j<singleWellChartList->size();j++)
            {
                stream<<"Object "<<j<<" begin"<<endl;
                stream<<singleWellChartList->at(j)->getName()<<endl;
                stream<<"Object "<<j<<" end"<<endl;
                singleWellChartList->at(j)->saveTo(projectPath+"/"+getFolderNameByType(MARK_TYPE_CCOLUMN));
            }
            stream<<"Type "<<MARK_TYPE_CCOLUMN<<" end"<<endl;
            break;
        case MARK_TYPE_WELL:
            if(wellList->size()<=0)
                break;

            stream<<"Type "<<MARK_TYPE_WELL<<" begin "<<wellList->size()<<endl;
            for(int j=0;j<wellList->size();j++)
            {
                stream<<"Object "<<j<<" begin"<<endl;
                stream<<wellList->at(j)->getWellName()+".wells"<<endl;
                stream<<"Object "<<j<<" end"<<endl;
                wellList->at(j)->saveWell(projectPath+"//"+getFolderNameByType(MARK_TYPE_WELL));
            }
            stream<<"Type "<<MARK_TYPE_WELL<<" end"<<endl;
            break;
        }
    }

    file.close();
}
//另存工程
void MainWindow::on_saveProjectAs_triggered()
{

}
//打开工程
void MainWindow::on_openProject_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this,"打开工程",QDir::currentPath(),"*.vod");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    this->on_closeProject_triggered();
    fileInfo = QFileInfo(fileName);
    treeCreated = true;
    projectPath =fileInfo.absolutePath() ;
    QString tempString;
    QList<QString> qList;

//    ui->graphicsView->setNode(group);
//    switchExplorationResultNode = group->getChild(0)->asSwitch();
//    switchWellNode = group->getChild(1)->asSwitch();
//    switchProfileNode = group->getChild(2)->asSwitch();
//    switchTinNode = group->getChild(3)->asSwitch();
   qDebug()<<"start read";
    QTextStream stream(&file);
    this->itemTypeList = new QList<PROJECTITEM*>;

    qList=stream.readLine().split(" ",QString::KeepEmptyParts);
    int typeNum = qList.at(1).toInt();
    for(int i=0;i<typeNum;i++)
    {
        PROJECTITEM* tempItem = new PROJECTITEM;
        qList = stream.readLine().split(" ",QString::KeepEmptyParts);
        tempItem->name = qList.at(0);
        tempItem->text = qList.at(1);
        tempItem->type = qList.at(2).toInt();
        this->itemTypeList->append(tempItem);
        this->addSwitchNode(tempItem->type);
    }
    ui->treeView->addChild(fileInfo.baseName(), projectPath,this->itemTypeList);
    qDebug()<<"1";
    StrataSurface* strataSurface;
    Well* well;
    ExplorationResult* explorationResult;
    Profile* profile;
    SingleWellChart* singlewellchart;
    while(!stream.atEnd())
    {
        tempString = stream.readLine();
        qList = tempString.split(" ",QString::KeepEmptyParts);
        if(tempString.contains("Type")&&tempString.contains("begin"))
        {
            switch(qList.at(1).toInt())
            {
            case MARK_TYPE_STRATASURFACE:
            {
                LoadStrataSurface* loadStrataSurface = new LoadStrataSurface;
                for(int i=0;i<qList.at(3).toInt();i++)
                {
                    QString qs = stream.readLine();
                    if(qs.contains("Object")&&qs.contains("begin"))
                    {
                        QString name = stream.readLine().trimmed();
                        QString path = projectPath+"/"+getFolderNameByType(MARK_TYPE_STRATASURFACE)+"/"+name;
                        strataSurface = loadStrataSurface->loadSS(path);
                        osg::ref_ptr<osg::Geometry> geom = strataSurface->getGeometry();
                        geom->setName(name.toStdString());

                        //添加转换节点
                        switchStrataSurfaceNode->addChild(SwitchNodeFactory::createStrataSurfaceSwitchNode(strataSurface));

                        //添加到treeview中
                        ui->treeView->addStrataSurfaceFile(name);
                    }
                    qs = stream.readLine();
                    if(qs.contains("Object")&&qs.contains("end"))
                    {
                        //添加到容器中
                        strataSurfaceList->append(strataSurface);
                    }
                }
            }
                break;
            case MARK_TYPE_WELL:
            {
                LoadWell* loadWell = new LoadWell;
                for(int i=0;i<qList.at(3).toInt();i++)
                {
                    QString qs = stream.readLine();
                    if(qs.contains("Object")&&qs.contains("begin"))
                    {
                        QString wellName = stream.readLine().trimmed();

                        QString wellPath = projectPath+"//"+getFolderNameByType(MARK_TYPE_WELL)+"//"+wellName;

                        qDebug()<<wellName;

                        well = loadWell->loadWELL(wellPath);


                        //添加转换节点
                        switchWellNode->addChild(SwitchNodeFactory::createWellSwitchNode(well));

                        //添加到treeview中
                        ui->treeView->addWellFile(wellName);
                    }
                    qs = stream.readLine();
                    if(qs.contains("Object")&&qs.contains("end"))
                    {
                        //添加到容器中
                        wellList->append(well);
                    }
                }
            }
                break;
            case MARK_TYPE_EXPLORATIONRESULT:
                for(int i=0;i<qList.at(3).toInt();i++)
                {
                    QString qs = stream.readLine();
                    if(qs.contains("Object")&&qs.contains("begin"))
                    {
                        explorationResult = new ExplorationResult;
                        QString imgName = stream.readLine().trimmed();
                        QString imgBaseName = imgName.split(".",QString::KeepEmptyParts).at(0);

                        LoadExplorationResult *loadexplorationresult = new LoadExplorationResult();

                        explorationResult = loadexplorationresult->loadExp(projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT)+"/"+imgName);
//                        explorationResult = loadexplorationresult->loadByteExp(projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT)+"/"+imgName);

                        //添加转换节点
                        switchExplorationResultNode->addChild(SwitchNodeFactory::createExplorationResultSwitchNode(explorationResult));

                        //添加到treeview中
//                        explorationResult->setName(imgBaseName);
                        ui->treeView->addExplorationResultFile(imgBaseName);


                    }
                    qs = stream.readLine();
                    if(qs.contains("Object")&&qs.contains("end"))
                    {
                        //添加到容器中
                        explorationResultList->append(explorationResult);
                    }
                }
//                while(!stream.atEnd())
//                {
//                    QString qs = stream.readLine();
//                    if(qs.contains("Object")&&tempString.contains("begin"))
//                    {
//                        explorationResult = new ExplorationResult;
//                        QString imgName = stream.readLine().trimmed();
//                        QString imgBaseName = imgName.split(".",QString::KeepEmptyParts).at(0);
//                        explorationResult->setImagebyURL(projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT)+"/"+imgName);
//                        explorationResult->setVertexArraybyURL(projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT)+"/"+imgBaseName+".txt");

//                        osg::ref_ptr<osg::Geometry> geom = explorationResult->getGeometry();

//                        geom->setName(imgBaseName.toStdString());

//                        //添加转换节点
//                        switchExplorationResultNode->addChild(ExplorationResultFactory::createExplorationResultSwitchNode(explorationResult));

//                        //添加到treeview中
//                        explorationResult->setName(imgBaseName);
//                        ui->treeView->addExplorationResultFile(imgBaseName);
//                    }
//                    if(qs.contains("Object")&&tempString.contains("end"))
//                    {
//                        //添加到容器中
//                        explorationResultList->append(explorationResult);
//                    }
//                }
                break;
            case MARK_TYPE_PROFILE:
                for(int i=0;i<qList.at(3).toInt();i++)
                {
                    QString qs = stream.readLine();
                    if(qs.contains("Object")&&qs.contains("begin"))
                    {
                        QString imgName = stream.readLine().trimmed();
                        QString imgBaseName = imgName.split(".",QString::KeepEmptyParts).at(0);
                        QString imgPath = projectPath+"/"+getFolderNameByType(MARK_TYPE_PROFILE)+"/"+imgName;

                        LoadProfile * loadprofile = new LoadProfile();

                        profile = loadprofile->loadPro(imgPath);



                        //添加转换节点
                        switchProfileNode->addChild(SwitchNodeFactory::createProfileSwitchNode(profile));

                        //添加到treeview中
                        ui->treeView->addProfileFile(imgBaseName);
                    }
                    qs = stream.readLine();
                    if(qs.contains("Object")&&qs.contains("end"))
                    {
                        //添加到容器中
                        profileList->append(profile);
                    }
                }
                break;
            case MARK_TYPE_CCOLUMN:
                for(int i=0;i<qList.at(3).toInt();i++)
                {
                    QString qs = stream.readLine();
                    if(qs.contains("Object")&&qs.contains("begin"))
                    {
                        QString imgName = stream.readLine().trimmed();
                        QString imgBaseName = imgName.split(".",QString::KeepEmptyParts).at(0);
                        QString imgPath = projectPath+"/"+getFolderNameByType(MARK_TYPE_CCOLUMN)+"/"+imgName;

                        LoadSingleWellChart * loadsinglewellchart = new LoadSingleWellChart();

                        singlewellchart = loadsinglewellchart->loadSin(imgPath);



                        //添加转换节点
                        switchCColumnNode->addChild(SwitchNodeFactory::createSingleWellChartSwitchNode(singlewellchart));

                        //添加到treeview中

                        ui->treeView->addCColumnFile(imgBaseName);


                    }
                    qs = stream.readLine();
                    if(qs.contains("Object")&&qs.contains("end"))
                    {
                        //添加到容器中
                        singleWellChartList->append(singlewellchart);
                    }
                }
                break;

            }
        }
//        if(tempString.contains("Type")&&tempString.contains("end"))
//        {
//            switch(qList.at(1).toInt())
//            {
//            case MARK_TYPE_EXPLORATIONRESULT:
//                explorationResultList->append(explorationResult);
//                break;
//            case MARK_TYPE_PROFILE:
//                break;
//            }
//        }
    }

   // ui->treeView->addChild(fileInfo.baseName(), projectPath,this->itemTypeList);

    //group = ProjectOperation::openProject(projectPath,explorationResultList,wellList,profileList,tinList);

//    switchExplorationResultNode = group->getChild(0)->asSwitch();
//    switchWellNode = group->getChild(1)->asSwitch();
//    switchProfileNode = group->getChild(2)->asSwitch();
//    switchTinNode = group->getChild(3)->asSwitch();

//    ui->graphicsView->setNode(group);
//    for(int i=0;i<explorationResultList->size();i++)
//    {
//        ui->treeView->addExplorationResultFile(explorationResultList->at(i)->getName());
//    }
//    for(int i=0;i<wellList->size();i++)
//    {
//        ui->treeView->addWellFile(wellList->at(i)->getWellName());

//    }
//    for(int i=0;i<profileList->size();i++)
//    {
//        ui->treeView->addProfileFile(profileList->at(i)->getName());
//    }
//    for(int i=0;i<tinList->size();i++)
//    {
//        ui->treeView->addStrataSurfaceFile(tinList->at(i)->getName());
//    }
    file.close();
    ui->graphicsView->adjustCamera();

}
//关闭工程
void MainWindow::on_closeProject_triggered()
{
    init();

    ui->treeView->init();
}
//根据数据类型获得文件夹
QString MainWindow::getFolderNameByType(int type)
{
    QString folderName="";
    for(int i=0;i<itemTypeList->size();i++)
    {
        if(itemTypeList->at(i)->type==type)
        {
            folderName =itemTypeList->at(i)->text;
            break;
        }
    }
    return folderName;
}
//加载地层面
void MainWindow::on_loadStrataSurface_triggered()
{
    //判断是否有根目录
    if(!treeCreated)
    {
        QMessageBox::information(this,"Error Message","请先添加一个工程");
        return ;
    }
    //打开文件
    QStringList fileNames = QFileDialog::getOpenFileNames(this,"加载地层面",historyPath,"*.tins");
    foreach (QString fileName, fileNames)
    {
        if(fileName.isEmpty())
        {
            continue ;
        }

        fileInfo = QFileInfo(fileName);
        fileName = fileInfo.baseName();
        //记录路径
        historyPath = fileInfo.absoluteDir().absolutePath();
        //创建地层节点
        LoadStrataSurface * loadStrataSurface = new LoadStrataSurface();
        StrataSurface* strataSurface = loadStrataSurface->loadTin(fileInfo.absoluteFilePath());
        strataSurface->setPointSingleColor(strataSurfaceList->size());
//        Tin *tin = new Tin;
//        tin->setVertexArraybyURL(fileInfo.absoluteFilePath());

//        osg::ref_ptr<osg::Geometry> geom = tin->getGeometry();
        osg::ref_ptr<osg::Geometry> geom = strataSurface->getGeometry();
        geom->setName(fileName.toStdString());
        switchStrataSurfaceNode->addChild(SwitchNodeFactory::createStrataSurfaceSwitchNode(strataSurface));
//      strataSurface->setPointSampleColor();
//        //拷贝文件
//        QFile::copy(fileInfo.absoluteFilePath(),projectPath+"/"+getFolderNameByType(MARK_TYPE_STRATASURFACE)+"/"+fileInfo.fileName());
         //添加到treeview中
        //well->setWellName(fileName);
        ui->treeView->addStrataSurfaceFile(fileName);
        //添加到容器中
        strataSurfaceList->append(strataSurface);
     }
    //重新计算包围盒
    ui->graphicsView->adjustCamera();

}
//加载断层面
void MainWindow::on_loadFault_triggered()
{

}
//加载井
void MainWindow::on_loadWell_triggered()
{
    //判断是否有根目录
       if(!treeCreated)
       {
           QMessageBox::information(this,"Error Message","请先添加一个工程");
           return ;
       }
       //打开文件
       QStringList fileNames = QFileDialog::getOpenFileNames(this,"加载井",historyPath,"*.dev");
       foreach (QString fileName, fileNames)
       {
           fileInfo = QFileInfo(fileName);
           fileName = fileInfo.baseName();
           //记录路径
           historyPath = fileInfo.absoluteDir().absolutePath();

//           QFile::copy(fileInfo.absoluteFilePath(),projectPath+"/"+getFolderNameByType(MARK_TYPE_WELL)+"/"+fileInfo.fileName());
           //创建井节点
           Well *well;

//           well->setWellData(fileInfo.absoluteFilePath());

           LoadWell *loadWell = new LoadWell;
           well = loadWell->loadDEV(fileInfo.absoluteFilePath());
      // well->readWellData();
//           osg::ref_ptr<osg::Geometry> geom = well->getGeometry();
//           geom->setName(fileName.toStdString());

           switchWellNode->addChild(SwitchNodeFactory::createWellSwitchNode(well));

            //添加到treeview中
           //well->setWellName(fileName);
           ui->treeView->addWellFile(fileName);
           //添加到容器中
           wellList->append(well);
        }

       //重新计算包围盒
       ui->graphicsView->adjustCamera();

}
//加载表面模型
void MainWindow::on_loadSModel_triggered()
{

}
//加载体元模型
void MainWindow::on_loadVModel_triggered()
{

}
//加载勘探成果图
void MainWindow::on_loadExplorationResult_triggered()
{
    //判断是否有根目录
    if(!treeCreated)
    {
        QMessageBox::information(this,"Error Message","请先添加一个工程");
        return ;
    }
    //打开文件
    QStringList fileNames = QFileDialog::getOpenFileNames(this,"加载勘探成果图",historyPath,"*.jpg *.bmp");
    foreach (QString fileName, fileNames) {
        if(fileName.isEmpty())
        {
            continue ;
        }

        fileInfo = QFileInfo(fileName);

        fileName = fileInfo.baseName();
        //记录路径
        historyPath = fileInfo.absoluteDir().absolutePath();

        //拷贝文件
        QFile::copy(fileInfo.absoluteFilePath(),projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT)+"/"+fileInfo.fileName());
//        QFile::copy(fileInfo.path()+"/"+fileName+".txt",projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT)+"/"+fileName+".txt");

        //创建勘探成果图对象


        LoadExplorationResult *loadexplorationResult = new LoadExplorationResult();

        ExplorationResult *explorationResult = loadexplorationResult->loadPicAndText(fileInfo.absoluteFilePath());

//        explorationResult->setImagebyURL(fileInfo.absoluteFilePath());
//        explorationResult->setVertexArraybyURL(fileInfo.path()+"/"+fileName+".txt");

//        osg::ref_ptr<osg::Geometry> geom = explorationResult->getGeometry();
       // const osg::BoundingBox &box=explorationResult.getGeometry()->getBoundingBox();
      //  float size=(box.xMax()-box.xMin())/10;
//        geom->setName(fileName.toStdString());


        //添加转换节点
        switchExplorationResultNode->addChild(SwitchNodeFactory::createExplorationResultSwitchNode(explorationResult));

        //添加到treeview中
        explorationResult->setName(fileName);
        ui->treeView->addExplorationResultFile(fileName);
        //添加到容器中
        explorationResultList->append(explorationResult);


       // counter++;

    }
    //重新计算包围盒
    ui->graphicsView->adjustCamera();
    //setPosition();

}
//加载连井剖面图
void MainWindow::on_loadProfile_triggered()
{
    //判断是否有根目录
    if(!treeCreated)
    {
        QMessageBox::information(this,"Error Message","请先添加一个工程");
        return ;
    }
    //打开文件
    QStringList fileNames = QFileDialog::getOpenFileNames(this,"加载连井剖面图",historyPath,"*.jpg *.bmp");
    foreach (QString fileName, fileNames) {
        if(fileName.isEmpty())
        {
            continue ;
        }
        fileInfo = QFileInfo(fileName);
        fileName = fileInfo.baseName();
        //记录路径
        historyPath = fileInfo.absoluteDir().absolutePath();

        //创建连井剖面图节点
        LoadProfile *loadprofile = new LoadProfile();



       Profile * pro = loadprofile->loadPicAndText(fileInfo.absoluteFilePath());


//        pro->setImagebyURL(fileInfo.absoluteFilePath());

//        QString txtpath= fileInfo.path()+"/"+fileName+".txt";

//        pro->setVertexArraybyURL(txtpath);
//        osg::ref_ptr<osg::Geometry> geom = pro->getGeometry();
//        geom->setName(fileName.toStdString());

        //添加转换节点
        switchProfileNode->addChild(SwitchNodeFactory::createProfileSwitchNode(pro));

//        pro->setName(fileName);
        ui->treeView->addProfileFile(fileName);

        //拷贝文件
        QFile::copy(fileInfo.absoluteFilePath(),projectPath+"/"+getFolderNameByType(MARK_TYPE_PROFILE)+"/"+fileInfo.fileName());
//        QFile::copy(fileInfo.path()+"/"+fileName+".txt",projectPath+"/"+getFolderNameByType(MARK_TYPE_PROFILE)+"/"+fileName+".txt");

        //添加到容器中
        profileList->append(pro);
    }
    //重新计算包围盒
    ui->graphicsView->adjustCamera();
    //setPosition();

}
//加载单井综合柱状图
void MainWindow::on_loadCompositeColumn_triggered()
{


    //判断是否有根目录
    if(!treeCreated)
    {
        QMessageBox::information(this,"Error Message","请先添加一个工程");
        return ;
    }
    //打开文件
    QStringList fileNames = QFileDialog::getOpenFileNames(this,"加载勘探成果图",historyPath,"*.jpg *.bmp");
    foreach (QString fileName, fileNames) {
        if(fileName.isEmpty())
        {
            continue ;
        }

        fileInfo = QFileInfo(fileName);

        fileName = fileInfo.baseName();
        //记录路径
        historyPath = fileInfo.absoluteDir().absolutePath();

        //拷贝文件
        QFile::copy(fileInfo.absoluteFilePath(),projectPath+"/"+getFolderNameByType(MARK_TYPE_CCOLUMN)+"/"+fileInfo.fileName());
//        QFile::copy(fileInfo.path()+"/"+fileName+".txt",projectPath+"/"+getFolderNameByType(MARK_TYPE_EXPLORATIONRESULT)+"/"+fileName+".txt");

        //创建勘探成果图对象

        SingleWellChart *chart = new SingleWellChart;
        const osg::BoundingBox &bbox = this->explorationResultList->at(0)->getGeometry()->getBoundingBox();
        double length = bbox.xMax()- bbox.xMin();


        chart->setVertexArraybyURL(fileInfo.path()+"/"+fileName+"1.txt",length);
        chart->setImagebyURL(fileInfo.absoluteFilePath());
        chart->drawGeode();



        //添加转换节点
        switchCColumnNode->addChild(SwitchNodeFactory::createSingleWellChartSwitchNode(chart));

        //添加到treeview中

        ui->treeView->addCColumnFile(fileName);

        singleWellChartList->append(chart);


    }
    //重新计算包围盒
    ui->graphicsView->adjustCamera();
    //setPosition();
}

void MainWindow::on_quit_triggered()
{
    exit(0);
}

void MainWindow::on_ExplorationResultDataTransForm_triggered()
{
    LayerDialog *log = new LayerDialog;

    log->exec();
}

void MainWindow::on_ProfileDataTransform_triggered()
{
  //  LayerDialog *log = new LayerDialog;
    ProfileCalDialog *dlg = new ProfileCalDialog;

    dlg->exec();
}

void MainWindow::on_SinglewellDataTransform_triggered()
{
    SingleWellDialog *log = new SingleWellDialog;
    log->exec();
}

void MainWindow::on_DataTransform_triggered()
{
    CheckDialog *log = new CheckDialog;
    log->exec();
}

void MainWindow::wheelEvent(QWheelEvent*event ){

    float x,y,z;
    osg::Vec3d eye,center,up;
    sgeode=ui->graphicsView->getgeode();
    groupnext->removeChild(sgeode);
    sgeode =new osg::Geode;
    ui->graphicsView->getOSGViewer()->getCamera()->getViewMatrixAsLookAt(eye,center,up);
    if(abs(center.x()-bb.xMin())<abs(center.x()-bb.xMax()))
    {
          x=bb.xMax();
    }
    else
    {
         x=bb.xMin();
    }

    if(abs(center.y()-bb.yMin())<abs(center.y()-bb.yMax()))
    {
       y=bb.yMax();

    }

    else
    {
            y=bb.yMin();

    }



    if(abs(center.z()-bb.zMin())<abs(center.z()-bb.zMax()))
    {
         z=bb.zMax();
    }

    else
    {
        z=bb.zMin();

    }


    if(groupnext->getNumChildren()==0)
           return;
    else
    {
    if(event->delta()>0){//如果滚轮往上滚
    MainWindow::bian=MainWindow::bian+50;
       v1->clear();

       int i=0,nummm;
       while(5*i*MainWindow::bian<(bb.xMax()-bb.xMin()))
         {

           sgeode->addDrawable(createText(osg::Vec3(bb.xMin()+100+5*i*MainWindow::bian, y, bb.zMax()+200),bb.xMin()+i*5*MainWindow::bian));

            v1->push_back(osg::Vec3(bb.xMin()+i*5*MainWindow::bian, bb.yMin(), bb.zMax()));
            v1->push_back(osg::Vec3(bb.xMin()+i*5*MainWindow::bian, bb.yMin(), bb.zMax()+200));
            geom1->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, 2*i, 2)); //X
            i++;
       }
       nummm=i;
       i=1;
       while(5*i*MainWindow::bian<(bb.yMax()-bb.yMin()))
       {
             sgeode->addDrawable(createText(osg::Vec3(x, bb.yMin()+100+5*i*MainWindow::bian, bb.zMax()+100),bb.yMin()+i*5*MainWindow::bian));
             v1->push_back(osg::Vec3(bb.xMin(), bb.yMin()+i*5*MainWindow::bian, bb.zMax()));
             v1->push_back(osg::Vec3(bb.xMin(), bb.yMin()+i*5*MainWindow::bian, bb.zMax()+200));
             geom1->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, nummm*2, 2)); //X
             i++;
             nummm++;
       }
       while(5*i*MainWindow::bian<(bb.zMax()-bb.zMin()))
       {
             sgeode->addDrawable(createText(osg::Vec3(bb.xMin(), bb.yMin()+100+5*i*MainWindow::bian, bb.zMax()+100),bb.yMin()+i*5*MainWindow::bian));

       }
       if(num>nummm)
       for(int i=0;i<num-nummm;i++)
       {
           v1->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMax()));
           v1->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMax()));
       }
       geom1->setColorArray(c.get());
       geom1->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
       geom1->setVertexArray(v1.get());


           vminx->clear();
           vmaxx->clear();
           vminy->clear();
           vmaxy->clear();
           vminz->clear();
           vmaxz->clear();

        int icut=0;
        cut=0;
        a=MainWindow::bian;

        for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//xmin
        {
                vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin()+ MainWindow::bian, bb.zMin()));
                vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin()+ MainWindow::bian, bb.zMax()));
        MainWindow::bian+=a;
            cut=cut+1;
        }
         MainWindow::bian=a;
         for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//xmin
         {
             vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()+MainWindow::bian));
             vminx->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMin()+MainWindow::bian));
         MainWindow::bian+=a;
       cut=cut+1;
         }
         if (cut<cutminx)
         {
             for(int i=0;i<cutminx-cut;i++)
          {
               vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
                vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
          }
         }
          for(  icut=0;icut<cut;icut++)
          geomxmin->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
          geomxmin->setColorArray(c.get());
          geomxmin->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
          geomxmin->setVertexArray(vminx);



        cut=0;
        MainWindow::bian=a;
        for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//xmax
        {
        vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMin()+ MainWindow::bian, bb.zMin()));
        vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMin()+ MainWindow::bian, bb.zMax()));
        MainWindow::bian+=a;
            cut=cut+1;
         }
         MainWindow::bian=a;
         for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//xmax
         {
         vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMin()+MainWindow::bian));
         vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMin()+MainWindow::bian));
         MainWindow::bian+=a;
       cut=cut+1;
         }
          if (cut<cutmaxx)
         {
             for(int i=0;i<cutmaxx-cut;i++)
          {
               vmaxx->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
                vmaxx->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
          }
         }
         MainWindow::bian=a;
         for( icut=0 ;icut<cut;icut++)
         geomxmax->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
         geomxmax->setColorArray(c.get());
         geomxmax->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
         geomxmax->setVertexArray(vmaxx);



         cut=0;
        for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//ymin
        {
            vminy->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()+MainWindow::bian));
            vminy->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMin()+MainWindow::bian));
        MainWindow::bian+=a;
      cut=cut+1;
        }
         MainWindow::bian=a;
         for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//ymin
         {

                 vminy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMin()));
                 vminy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMax()));
             MainWindow::bian+=a;
            cut=cut+1;
         }
         if (cut<cutminy)
         {
             for(int i=0;i<cutminy-cut;i++)
          {
               vminy->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
                vminy->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
          }
         }
         MainWindow::bian=a;
         for( icut=0 ;icut<cut;icut++)
         geomymin->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
         geomymin->setColorArray(c.get());
         geomymin->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
         geomymin->setVertexArray(vminy);




         cut=0;
         for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//ymax
         {
         vmaxy->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMin()+MainWindow::bian));
         vmaxy->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMin()+MainWindow::bian));
         MainWindow::bian+=a;
       cut=cut+1;
         }
         MainWindow::bian=a;
         for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//ymax
         {
         vmaxy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMin()));
         vmaxy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMax()));
         MainWindow::bian+=a;
          cut=cut+1;
         }
        if (cut<cutmaxy)
         {
             for(int i=0;i<cutmaxy-cut;i++)
          {
               vmaxy->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
                vmaxy->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
          }
         }
         MainWindow::bian=a;
         for( icut=0 ;icut<cut;icut++)
         geomymax->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
         geomymax->setColorArray(c.get());
         geomymax->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
         geomymax->setVertexArray(vmaxy);



         cut=0;
         for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//zmin
         {
                 vminz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMin()));
                 vminz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMin()));
             MainWindow::bian+=a;
            cut=cut+1;
         }
         MainWindow::bian=a;

         for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//zmin
         {
                 vminz->push_back(osg::Vec3(bb.xMin(), bb.yMin()+MainWindow::bian, bb.zMin()));
                 vminz->push_back(osg::Vec3(bb.xMax(), bb.yMin()+MainWindow::bian, bb.zMin()));
         MainWindow::bian+=a;
             cut=cut+1;
         }
          if (cut<cutminz)
         {
             for(int i=0;i<cutminz-cut;i++)
          {
               vminz->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
                vminz->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
          }
         }
          MainWindow::bian=a;
          for(icut=0;icut<cut;icut++)
          geomzmin->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
          geomzmin->setColorArray(c.get());
          geomzmin->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
          geomzmin->setVertexArray(vminz);



         cut=0;
         for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//zmax
         {
         vmaxz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMax()));
         vmaxz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMax()));

         MainWindow::bian+=a;
          cut=cut+1;
         }
         MainWindow::bian=a;
         for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//zmax
         {
         vmaxz->push_back(osg::Vec3(bb.xMin(), bb.yMin()+MainWindow::bian, bb.zMax()));
         vmaxz->push_back(osg::Vec3(bb.xMax(), bb.yMin()+MainWindow::bian, bb.zMax()));

         MainWindow::bian+=a;
             cut=cut+1;
          }
          if (cut<cutmaxz)
         {
             for(int i=0;i<cutmaxz-cut;i++)
          {
               vmaxz->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
                vmaxz->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
          }
         }
          MainWindow::bian=a;
         for( icut=0 ;icut<cut;icut++)
         geomzmax->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
         geomzmax->setColorArray(c.get());
         geomzmax->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
         geomzmax->setVertexArray(vmaxz);

         geom1->dirtyDisplayList();
         geomxmin->dirtyDisplayList();
         geomxmax->dirtyDisplayList();
         geomymin->dirtyDisplayList();
         geomymax->dirtyDisplayList();
         geomzmin->dirtyDisplayList();
         geomzmax->dirtyDisplayList();
         ui->graphicsView->setnode(groupnext,MainWindow::bian);
    }

    else
    {
           v1->clear();
           vminx->clear();
           vmaxx->clear();
           vminy->clear();
           vmaxy->clear();
           vminz->clear();
           vmaxz->clear();

        MainWindow::bian=MainWindow::bian-50;
        if(MainWindow::bian<50)
            MainWindow::bian=50;

        int i=0,nummm;
        while(5*i*MainWindow::bian<(bb.xMax()-bb.xMin()))
          {


            sgeode->addDrawable(createText(osg::Vec3(bb.xMin()+100+5*i*MainWindow::bian, y, bb.zMax()+200),bb.xMin()+i*5*MainWindow::bian));

             v1->push_back(osg::Vec3(bb.xMin()+i*5*MainWindow::bian, bb.yMin(), bb.zMax()));
             v1->push_back(osg::Vec3(bb.xMin()+i*5*MainWindow::bian, bb.yMin(), bb.zMax()+200));
             geom1->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, 2*i, 2)); //X
             i++;
        }
        nummm=i;
        i=1;
        while(5*i*MainWindow::bian<(bb.yMax()-bb.yMin()))
        {
              sgeode->addDrawable(createText(osg::Vec3(x, bb.yMin()+100+5*i*MainWindow::bian, bb.zMax()+100),bb.yMin()+i*5*MainWindow::bian));
              v1->push_back(osg::Vec3(bb.xMin(), bb.yMin()+i*5*MainWindow::bian, bb.zMax()));
              v1->push_back(osg::Vec3(bb.xMin(), bb.yMin()+i*5*MainWindow::bian, bb.zMax()+200));
              geom1->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, nummm*2, 2)); //X
              i++;
              nummm++;
        }
        while(5*i*MainWindow::bian<(bb.zMax()-bb.zMin()))
        {
              sgeode->addDrawable(createText(osg::Vec3(bb.xMin(), bb.yMin()+100+5*i*MainWindow::bian, bb.zMax()+100),bb.yMin()+i*5*MainWindow::bian));

        }
        num=nummm;
        geom1->setColorArray(c.get());
        geom1->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
        geom1->setVertexArray(v1.get());



        int icut=0;
        cut=0;
        a=MainWindow::bian;

        for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//xmin
        {
                vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin()+ MainWindow::bian, bb.zMin()));
                vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin()+ MainWindow::bian, bb.zMax()));
        MainWindow::bian+=a;
            cut=cut+1;
        }
         MainWindow::bian=a;
         for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//xmin
         {
             vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()+MainWindow::bian));
             vminx->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMin()+MainWindow::bian));
         MainWindow::bian+=a;
       cut=cut+1;
         }
            cutminx=cut;
          for(  icut=0;icut<cut;icut++)
          geomxmin->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
          geomxmin->setColorArray(c.get());
          geomxmin->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
          geomxmin->setVertexArray(vminx);



        cut=0;
        MainWindow::bian=a;
        for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//xmax
        {
        vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMin()+ MainWindow::bian, bb.zMin()));
        vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMin()+ MainWindow::bian, bb.zMax()));
        MainWindow::bian+=a;
            cut=cut+1;
         }
         MainWindow::bian=a;
         for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//xmax
         {
         vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMin()+MainWindow::bian));
         vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMin()+MainWindow::bian));
         MainWindow::bian+=a;
       cut=cut+1;
         }
          cutmaxx=cut;
         MainWindow::bian=a;
         for( icut=0 ;icut<cut;icut++)
         geomxmax->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
         geomxmax->setColorArray(c.get());
         geomxmax->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
         geomxmax->setVertexArray(vmaxx);



         cut=0;
        for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//ymin
        {
            vminy->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()+MainWindow::bian));
            vminy->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMin()+MainWindow::bian));
        MainWindow::bian+=a;
      cut=cut+1;
        }
         MainWindow::bian=a;
         for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//ymin
         {

                 vminy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMin()));
                 vminy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMax()));
             MainWindow::bian+=a;
            cut=cut+1;
         }
       cutminy=cut;
         MainWindow::bian=a;
         for( icut=0 ;icut<cut;icut++)
         geomymin->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
         geomymin->setColorArray(c.get());
         geomymin->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
         geomymin->setVertexArray(vminy);




         cut=0;
         for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//ymax
         {
         vmaxy->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMin()+MainWindow::bian));
         vmaxy->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMin()+MainWindow::bian));
         MainWindow::bian+=a;
       cut=cut+1;
         }
         MainWindow::bian=a;
         for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//ymax
         {
         vmaxy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMin()));
         vmaxy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMax()));
         MainWindow::bian+=a;
          cut=cut+1;
         }
        cutmaxy=cut;
         MainWindow::bian=a;
         for( icut=0 ;icut<cut;icut++)
         geomymax->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
         geomymax->setColorArray(c.get());
         geomymax->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
         geomymax->setVertexArray(vmaxy);



         cut=0;
         for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//zmin
         {
                 vminz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMin()));
                 vminz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMin()));
             MainWindow::bian+=a;
            cut=cut+1;
         }
         MainWindow::bian=a;

         for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//zmin
         {
                 vminz->push_back(osg::Vec3(bb.xMin(), bb.yMin()+MainWindow::bian, bb.zMin()));
                 vminz->push_back(osg::Vec3(bb.xMax(), bb.yMin()+MainWindow::bian, bb.zMin()));
         MainWindow::bian+=a;
             cut=cut+1;
         }
        cutminz=cut;
          MainWindow::bian=a;
          for(icut=0;icut<cut;icut++)
          geomzmin->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
          geomzmin->setColorArray(c.get());
          geomzmin->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
          geomzmin->setVertexArray(vminz);



         cut=0;
         for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//zmax
         {
         vmaxz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMax()));
         vmaxz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMax()));

         MainWindow::bian+=a;
          cut=cut+1;
         }
         MainWindow::bian=a;
         for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//zmax
         {
         vmaxz->push_back(osg::Vec3(bb.xMin(), bb.yMin()+MainWindow::bian, bb.zMax()));
         vmaxz->push_back(osg::Vec3(bb.xMax(), bb.yMin()+MainWindow::bian, bb.zMax()));

         MainWindow::bian+=a;
             cut=cut+1;
          }
        cutmaxz=cut;
          MainWindow::bian=a;
         for( icut=0 ;icut<cut;icut++)
         geomzmax->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
         geomzmax->setColorArray(c.get());
         geomzmax->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
         geomzmax->setVertexArray(vmaxz);

         geom1->dirtyDisplayList();
         geomxmin->dirtyDisplayList();
         geomxmax->dirtyDisplayList();
         geomymin->dirtyDisplayList();
         geomymax->dirtyDisplayList();
         geomzmin->dirtyDisplayList();
         geomzmax->dirtyDisplayList();
         ui->graphicsView->setnode(groupnext,MainWindow::bian);
    }

    groupnext->addChild(sgeode);
    ui->graphicsView->settextnode(sgeode);

}

}
osgText::Text*  MainWindow::createText( osg::Vec3 pos,float a)
{

    QString s;
    s=QString::number(a,'f',2);
    string temp=s.toStdString();

     osg::ref_ptr<osgText::Text> text = new osgText::Text;
     text->setDataVariance(osg::Object::DYNAMIC);
     text->setText(temp);
     text->setColor(osg::Vec4(0.0,0.0,0.0,1.0));
     text->setAxisAlignment(osgText::Text::SCREEN);
     text->setCharacterSize(20);
     text->setPosition( pos);
     text->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);//跟随视角不断变化，离物体越远，文字越大
    // text->setAutoRotateToScreen(true);//跟随视角不断变化，但离物体越远，文字越小，和现实当中像类似
     return  text.release();
}

void MainWindow::XYZ()
{

    v->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
    v->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMin()));//x
    v->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
    v->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMin()));//y
    v->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()));
    v->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMax()));//z

    v->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMin()));
    v->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMax()));
    v->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMin()));
    v->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMin()));

    v->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMin()));
    v->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMax()));
    v->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMin()));
    v->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMin()));
    v->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMin()));
    v->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMax()));

    v->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMax()));
    v->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMax()));
    v->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMax()));
    v->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMax()));

    v->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMax()));
    v->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMax()));
    v->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMax()));
    v->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMax()));

}
void MainWindow::huakedu()
        {

     int icut=0;
     cut=0;
     a=MainWindow::bian;

     for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//xmin
     {

             vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin()+ MainWindow::bian, bb.zMin()));
             vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin()+ MainWindow::bian, bb.zMax()));
     MainWindow::bian+=a;
         cut=cut+1;
     }
      MainWindow::bian=a;
      for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//xmin
      {
          vminx->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()+MainWindow::bian));
          vminx->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMin()+MainWindow::bian));
      MainWindow::bian+=a;
    cut=cut+1;
      }
       for(  icut=0;icut<cut;icut++)
       geomxmin->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
       geomxmin->setColorArray(c.get());
       geomxmin->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
       geomxmin->setVertexArray(vminx);


     cut=0;
     MainWindow::bian=a;
     for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//xmax
     {
     vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMin()+ MainWindow::bian, bb.zMin()));
     vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMin()+ MainWindow::bian, bb.zMax()));
     MainWindow::bian+=a;
         cut=cut+1;
      }
      MainWindow::bian=a;
      for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//xmax
      {
      vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMin()+MainWindow::bian));
      vmaxx->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMin()+MainWindow::bian));
      MainWindow::bian+=a;
    cut=cut+1;
      }
      MainWindow::bian=a;
      for( icut=0 ;icut<cut;icut++)
      geomxmax->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
      geomxmax->setColorArray(c.get());
      geomxmax->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
      geomxmax->setVertexArray(vmaxx);



      cut=0;
     for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//ymin
     {
         vminy->push_back(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()+MainWindow::bian));
         vminy->push_back(osg::Vec3(bb.xMax(), bb.yMin(), bb.zMin()+MainWindow::bian));
     MainWindow::bian+=a;
   cut=cut+1;
     }
      MainWindow::bian=a;
      for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//ymin
      {

              vminy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMin()));
              vminy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMax()));
          MainWindow::bian+=a;
         cut=cut+1;
      }
      MainWindow::bian=a;
      for( icut=0 ;icut<cut;icut++)
      geomymin->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
      geomymin->setColorArray(c.get());
      geomymin->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
      geomymin->setVertexArray(vminy);




      cut=0;
      for(int i=1;i<(bb.zMax()-bb.zMin())/a;i++)//ymax
      {
      vmaxy->push_back(osg::Vec3(bb.xMin(), bb.yMax(), bb.zMin()+MainWindow::bian));
      vmaxy->push_back(osg::Vec3(bb.xMax(), bb.yMax(), bb.zMin()+MainWindow::bian));
      MainWindow::bian+=a;
    cut=cut+1;
      }
      MainWindow::bian=a;
      for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//ymax
      {
      vmaxy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMin()));
      vmaxy->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMax()));
      MainWindow::bian+=a;
       cut=cut+1;
      }
      MainWindow::bian=a;
      for( icut=0 ;icut<cut;icut++)
      geomymax->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
      geomymax->setColorArray(c.get());
      geomymax->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
      geomymax->setVertexArray(vmaxy);



      cut=0;
      for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//zmin
      {
              vminz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMin()));
              vminz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMin()));
          MainWindow::bian+=a;
         cut=cut+1;
      }
      MainWindow::bian=a;

      for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//zmin
      {
              vminz->push_back(osg::Vec3(bb.xMin(), bb.yMin()+MainWindow::bian, bb.zMin()));
              vminz->push_back(osg::Vec3(bb.xMax(), bb.yMin()+MainWindow::bian, bb.zMin()));
      MainWindow::bian+=a;
          cut=cut+1;
      }
       MainWindow::bian=a;
       for(icut=0;icut<cut;icut++)
       geomzmin->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
       geomzmin->setColorArray(c.get());
       geomzmin->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
       geomzmin->setVertexArray(vminz);



      cut=0;
      for(int i=1;i<(bb.xMax()-bb.xMin())/a;i++)//zmax
      {
      vmaxz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMin(), bb.zMax()));
      vmaxz->push_back(osg::Vec3(bb.xMin()+MainWindow::bian, bb.yMax(), bb.zMax()));

      MainWindow::bian+=a;
       cut=cut+1;
      }
      MainWindow::bian=a;
      for(int i=1;i<(bb.yMax()-bb.yMin())/a;i++)//zmax
      {
      vmaxz->push_back(osg::Vec3(bb.xMin(), bb.yMin()+MainWindow::bian, bb.zMax()));
      vmaxz->push_back(osg::Vec3(bb.xMax(), bb.yMin()+MainWindow::bian, bb.zMax()));

      MainWindow::bian+=a;
          cut=cut+1;
       }
       MainWindow::bian=a;
      for( icut=0 ;icut<cut;icut++)
      geomzmax->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, icut*2, 2)); //X
      geomzmax->setColorArray(c.get());
      geomzmax->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
      geomzmax->setVertexArray(vmaxz);


}

void MainWindow::huatu()
{


    if(groupnext->getNumChildren()!=0)
    {

        groupnext->removeChildren(0,groupnext->getNumChildren());
        group->removeChild(groupnext);//以索引删除一个子节点

        MainWindow::bian=1000;
        return;

    }
    else
    {
 // ui->graphicsView->adjustCamera();
      // qDebug()<<"bb"<<endl;

    switchxyz = new  osg::Switch;
    //获得包围盒
    group->accept(boundvisitor);
    bb = boundvisitor.getBoundingBox();
    float lengthx = bb.xMax()-bb.xMin();
    float lengthy = bb.yMax()-bb.yMin();
    float lengthz = bb.zMax()-bb.zMin();


   //绘制坐标系
    //创建保存几何信息的对象
        geom = new osg::Geometry();
        geomxmin = new osg::Geometry();
        geomxmax = new osg::Geometry();
        geomymin = new osg::Geometry();
        geomymax = new osg::Geometry();
        geomzmin = new osg::Geometry();
        geomzmax = new osg::Geometry();
        //创建所有顶点
        v = new osg::Vec3Array();
        vminx=new osg::Vec3Array();
        vmaxx=new osg::Vec3Array();
        vminy=new osg::Vec3Array();
        vmaxy=new osg::Vec3Array();
        vminz=new osg::Vec3Array();
        vmaxz=new osg::Vec3Array();
        XYZ();



        //为每个顶点指定一种颜色
        c = new osg::Vec4Array();

        for(int i=0;i<5000;i++)
        c->push_back(osg::Vec4(0.0f, 0.0f, 0.0f,1.0f));

        //如果没指定颜色则会变为黑色
        geom->setColorArray(c.get());
        geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
     //   setblend(geom->getOrCreateStateSet());
        geode = new osg::Geode();
        sgeode= new osg::Geode();
        geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
        geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.0),  osg::StateAttribute::ON);

        for(int i=0;i<24;i=i+2)
        geom->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, i, 2)); //X
        geom->setVertexArray(v);

        //三个轴


        osg::ref_ptr<osgText::Text> pTextXAuxis = new osgText::Text;
        pTextXAuxis->setText(L"X");
        pTextXAuxis->setFont("Fonts/simhei.ttf");
        pTextXAuxis->setColor(osg::Vec4(0.0,0.0,0.0,1.0));
        pTextXAuxis->setAxisAlignment(osgText::Text::SCREEN);
        pTextXAuxis->setCharacterSize(20);
        pTextXAuxis->setPosition(osg::Vec3(bb.xMin()+lengthx+10, bb.yMin(), bb.zMin()));
        pTextXAuxis->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);//跟随视角不断变化，离物体越远，文字越大
        //pTextXAuxis->setAutoRotateToScreen(true);//跟随视角不断变化，但离物体越远，文字越小，和现实当中像类似

        osg::ref_ptr<osgText::Text> pTextYAuxis = new osgText::Text;
        pTextYAuxis->setText(L"Y");
        pTextYAuxis->setFont("Fonts/simhei.ttf");
        pTextYAuxis->setColor(osg::Vec4(0.0,0.0,0.0,1.0));
        pTextYAuxis->setAxisAlignment(osgText::Text::SCREEN);
        pTextYAuxis->setCharacterSize(20);
        pTextYAuxis->setPosition(osg::Vec3(bb.xMin(), bb.yMin()+lengthy+10, bb.zMin()));
        pTextYAuxis->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);//跟随视角不断变化，离物体越远，文字越大
       // pTextYAuxis->setAutoRotateToScreen(true);//跟随视角不断变化，但离物体越远，文字越小，和现实当中像类似

        osg::ref_ptr<osgText::Text> pTextZAuxis = new osgText::Text;
        pTextZAuxis->setText(L"Z");
        pTextZAuxis->setFont("Fonts/simhei.ttf");
        pTextZAuxis->setColor(osg::Vec4(0.0,0.0,0.0,1.0));
        pTextZAuxis->setAxisAlignment(osgText::Text::SCREEN);
        pTextZAuxis->setCharacterSize(20);
        pTextZAuxis->setPosition(osg::Vec3(bb.xMin(), bb.yMin(), bb.zMin()+lengthz+10));
        pTextZAuxis->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);//跟随视角不断变化，离物体越远，文字越大
       // pTextZAuxis->setAutoRotateToScreen(true);//跟随视角不断变化，但离物体越远，文字越小，和现实当中像类似

        //geode->addDrawable(pTextKD0Auxis.get());
//            geode->addDrawable(pTextKDAuxis.get());
        geode->addDrawable(pTextXAuxis.get());
        geode->addDrawable(pTextYAuxis.get());
        geode->addDrawable(pTextZAuxis.get());



        huakedu();

         geom1=new osg::Geometry();
          v1 = new osg::Vec3Array();
       for(int i=1;i<lengthx/MainWindow::bian/5;i++)
       {
           sgeode->addDrawable(createText(osg::Vec3(bb.xMin()+100+i*MainWindow::bian*5, bb.yMin(), bb.zMax()+100),bb.xMin()+i*5*MainWindow::bian));

           v1->push_back(osg::Vec3(bb.xMin()+i*MainWindow::bian*5, bb.yMin(), bb.zMax()));
           v1->push_back(osg::Vec3(bb.xMin()+i*MainWindow::bian*5, bb.yMin(), bb.zMax()+200));
           geom1->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, 0+2*i, 2)); //X
           geom1->setColorArray(c.get());
           geom1->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
           geom1->setVertexArray(v1.get());
           geode->addDrawable(geom1.get());

       }
           //Y轴上的刻度
        for(int i=1;i<=lengthy/ MainWindow::bian/5;i++)
       {
           sgeode->addDrawable(createText(osg::Vec3(bb.xMin(), bb.yMin()-100+i*MainWindow::bian*5, bb.zMax()+100),bb.yMin()+i*5*MainWindow::bian));
           v1->push_back(osg::Vec3(bb.xMin(), bb.yMin()+i*MainWindow::bian*5, bb.zMax()));
           v1->push_back(osg::Vec3(bb.xMin(), bb.yMin()+i*MainWindow::bian*5, bb.zMax()+200));;
           geom1->addPrimitiveSet( new osg::DrawArrays(osg::PrimitiveSet::LINES, 12+2*i, 2)); //X
           geom1->setColorArray(c.get());
           geom1->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
           geom1->setVertexArray(v1.get());
           geode->addDrawable(geom1.get());
       }
       switchxyz->addChild(geomxmin);
       switchxyz->addChild(geomxmax);
       switchxyz->addChild(geomymin);
       switchxyz->addChild(geomymax);
       switchxyz->addChild(geomzmin);
       switchxyz->addChild(geomzmax);
       groupnext->addChild(sgeode);
       groupnext->addChild(geom.get());
       groupnext->addChild(switchxyz);
       groupnext->addChild(geode.get());


        group->addChild(groupnext);


     // root->addChild(sgeode);
       switchxyz->asSwitch()->setValue(2,false);

       ui->graphicsView->setSwitch(switchxyz);
       ui->graphicsView->settextnode(sgeode);
       ui->graphicsView->setnode(groupnext,MainWindow::bian);
       ui->graphicsView->getnum(bb.xMin(),bb.yMin(),bb.zMin(),bb.xMax(),bb.yMax(),bb.zMax());

}}
