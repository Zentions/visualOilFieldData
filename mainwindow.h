#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QRegExp>
#include <QFileInfo>
#include <QAction>

#include <osgText/Text>
#include <osg/DrawPixels>
#include <osg/ref_ptr>
#include <osgDB/ReadFile>
#include <osgDB/ConvertUTF>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/TexGen>
#include <osg/TexEnv>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/Switch>
#include <osg/Point>
#include <osg/BoundingSphere>
#include <osgUtil/Optimizer>
#include <osg/PositionAttitudeTransform>
#include <osg/Quat>
#include <osg/BoundingBox>
#include <osg/AutoTransform>
#include <osg/ComputeBoundsVisitor>

#include "graphicsview.h"
#include "function.h"
#include "explorationResult.h"
#include "projectDialog.h"
#include "profilecaldialog.h"

#include "profile.h"
#include "projectoperation.h"
#include "switchNodeFactory.h"
#include "folderMenu.h"
#include "itemMenu.h"
#include "loadWell.h"
#include "loadStrataSurface.h"
#include "loadexplorationresult.h"
#include "loadprofile.h"
#include "loadsinglewellchart.h"
#include "singlewelldialog.h"
#include "layerdialog.h"
#include "checkdialog.h"
#include "singlewellchart.h"

#include "tin.h"
#include "common.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static float bian;

    void openFile(QString name);
    void setPosition();
    void setHistoryPath(QString);
private:
    int cut=0;
    float a;
    int sum=0;
    int num=0;
    int cutminx=0,cutmaxx=0,cutminy=0,cutmaxy=0,cutminz=0,cutmaxz=0;
  osg::ref_ptr<osg::Vec4Array> c;
    osg::ref_ptr<osg::Geometry> geom;
     osg::ref_ptr<osg::Vec3Array> v ;
     osg::ref_ptr<osg::Vec3Array> vminx ;
     osg::ref_ptr<osg::Vec3Array> vmaxx ;
     osg::ref_ptr<osg::Vec3Array> vminy ;
     osg::ref_ptr<osg::Vec3Array> vmaxy ;
     osg::ref_ptr<osg::Vec3Array> vminz ;
     osg::ref_ptr<osg::Vec3Array> vmaxz ;
     osg::ref_ptr<osg::Geometry> geomxmin;
     osg::ref_ptr<osg::Geometry> geomxmax;
     osg::ref_ptr<osg::Geometry> geomymin;
     osg::ref_ptr<osg::Geometry> geomymax;
     osg::ref_ptr<osg::Geometry> geomzmin;
     osg::ref_ptr<osg::Geometry> geomzmax;
     osg::ref_ptr<osg::Geode> geode;
     osg::ref_ptr<osg::Geode> sgeode;
     osg::ref_ptr<osg::Geometry> geom1;
      osg::ref_ptr<osg::Vec3Array>  v1;
      osg::ref_ptr<osg::Group> root;
      osg::ref_ptr<osg::Switch> switchxyz;
      osg::ComputeBoundsVisitor boundvisitor ;
       osg::BoundingBox bb;


    Ui::MainWindow *ui;
    GraphicsView *w;
    ProjectDialog *projectDialog ;
    QString historyPath;
    //创建场景组节点
    osg::ref_ptr<osg::Group> group;

    osg::ref_ptr<osg::Group> groupnext; //坐标系节点

    osg::ref_ptr<osgViewer::Viewer> viewer;
    osg::ref_ptr<osg::Switch> switchStrataSurfaceNode;
    osg::ref_ptr<osg::Switch> switchFaultNode;
    osg::ref_ptr<osg::Switch> switchWellNode;
    osg::ref_ptr<osg::Switch> switchSModelNode;
    osg::ref_ptr<osg::Switch> switchVModelNode;
    osg::ref_ptr<osg::Switch> switchExplorationResultNode;
    osg::ref_ptr<osg::Switch> switchProfileNode;
    osg::ref_ptr<osg::Switch> switchCColumnNode;

    osg::ref_ptr<osg::PositionAttitudeTransform> posNode; 
    //创建各类子菜单
//    ExplorationResultFolderMenu *explorationResultFolderMenu;
//    WellFolderMenu *wellFolderMenu;
//    ProfileFolderMenu *profileFolderMenu;
//    TinFolderMenu *tinFolderMenu;
    FolderMenu *explorationResultFolderMenu;
    FolderMenu *wellFolderMenu;
    FolderMenu *profileFolderMenu;
    FolderMenu *strataSurfaceFolderMenu;
    FolderMenu *singleWellChartFolderMenu;

    ItemMenu *explorationResultItemMenu;
    ItemMenu *wellItemMenu;
    ItemMenu *profileItemMenu;
    ItemMenu *strataSurfaceItemMenu;
    ItemMenu *singleWellChartItemMenu;
    //辅助参数
    QFileInfo fileInfo;
    QString projectPath;
    QPoint temppos;
    //对象容器
    QList<ExplorationResult*> *explorationResultList;
    QList<Well*> *wellList;
    QList<Profile*> *profileList;
    QList<StrataSurface*> *strataSurfaceList;
    QList<SingleWellChart*> *singleWellChartList;
   // ProfileItemMenu *profileItemMenu;
    bool treeCreated;//判断树的父节点是否生成
    int counter;//记录第几个载入
    double proW;//实际图形与osg图形的宽度比
    double proH;//实际图形与osg图形的高度比
    double X;
    //以第一张图的左上角为相对原点
    double Y;

    QList<PROJECTITEM*> *itemTypeList;//工程中的数据类型列表

    QString getFolderNameByType(int type);

    void init();
    void addSwitchNode(int);

    void huatu();
    void XYZ();
    void huakedu();
    osgText::Text* createText( osg::Vec3 pos,float a);

private slots:

    void wheelEvent(QWheelEvent*event);//滚轮

    void changeState(int,int,int,bool);
    void receiveData(QString,QList<PROJECTITEM*>*);

    void adjustTreeWidth(const QModelIndex &index);

    void operateExplorationResultItem(QAction*);
    void operateWellItem(QAction*);
    void operateProfileItem(QAction*);
    void operateStrataSurfaceItem(QAction*);
    void operateSingleWellChartItem(QAction*);

    void reCreate();


    void on_Revocation_triggered();

    void on_Restore_triggered();

    void on_table_of_Contents_triggered();

    void on_Index_triggered();

    void on_Online_Help_triggered();

    void on_Pick_up_triggered();

    void on_Drag_triggered();

    void on_extend_triggered();

    void on_merge_triggered();

    void on_delete_2_triggered();

    void on_copy_triggered();

    void on_Cutting_triggered();

    void on_Property_superposition_triggered();

    void on_Unselected_triggered();



    void on_reduction_triggered();

    void on_whirl_alone_triggered();

    void on_whirl_triggered();

    void on_panoramic_triggered();

    void on_Bottom_view_triggered();

    void on_Parallel_projection_triggered();

    void on_Perspective_projection_triggered();

    void on_enlarge_triggered();

    void on_Narrow_triggered();

    void on_Outsourcing_box_triggered();

    void on_XYZ_triggered();

    void on_Staff_triggered();

    void on_North_view_triggered();

    void on_Wellhead_triggered();

    void on_Well_trajectory_triggered();

    void on_Logs_triggered();

    void on_Perforation_triggered();

    void on_Stratified_triggered();

    void on_Reservoir_Simulation_triggered();

    void on_Geological_model_triggered();

    void on_crack_triggered();

    void on_color_triggered();

    void on_Hide_Show_triggered();

    void on_move_triggered();

    void on_Light_control_triggered();

    void on_drilling_triggered();

    void on_profile_triggered();

    void on_well_deviation_triggered();

    void on_straight_line_triggered();

    void on_text_editor_triggered();

    void on_Draw_boundary_triggered();

    void on_Generate_contours_triggered();

    void on_layer_triggered();

    void on_Structural_map_triggered();

    void on_Thematic_map_triggered();

    void on_point_triggered();

    void on_line_triggered();

    void on_surface_triggered();

    void on_body_part_triggered();

    void on_Sphere_triggered();

    void on_cuboid_triggered();

    void on_Ellipsoid_triggered();

    void on_Cone_triggered();

    void on_Cylinder_triggered();

    void on_Yuantong_triggered();

    void on_Ring_triggered();


    void on_treeView_customContextMenuRequested(const QPoint &pos);


    void on_AssistantView_triggered();
    void on_createProject_triggered();
    void on_saveProject_triggered();
    void on_saveProjectAs_triggered();
    void on_openProject_triggered();
    void on_closeProject_triggered();
    void on_loadStrataSurface_triggered();
    void on_loadFault_triggered();
    void on_loadWell_triggered();
    void on_loadSModel_triggered();
    void on_loadVModel_triggered();
    void on_loadExplorationResult_triggered();
    void on_loadProfile_triggered();
    void on_loadCompositeColumn_triggered();
    void on_quit_triggered();
    void on_ExplorationResultDataTransForm_triggered();
    void on_ProfileDataTransform_triggered();
    void on_SinglewellDataTransform_triggered();
    void on_DataTransform_triggered();
};

#endif // MAINWINDOW_H
