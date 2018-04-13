#ifndef COMMON
#define COMMON

#define ROLE_MARK Qt::UserRole+1 //根节点
#define ROLE_MARK_FOLDER  Qt::UserRole+2//文件夹节点
#define ROLE_MARK_ITEM Qt::UserRole+3//条目节点
#define ROLE_MARK_TYPE Qt::UserRole+4//对象类型

//对应ROLE_MARK
#define MARK_PROJECT 1//总项目标记
#define MARK_FOLDER 2//文件夹标记
#define MARK_ITEM 3//条目标记
#define MARK_TYPE 4//类型标记
//对应ROLE_MARK_FOLDER，标记folder种类
#define MARK_FOLDER_STRATASURFACE 1//地层面文件文件夹标记
#define MARK_FOLDER_FAULT 2 //断层面文件文件夹标记
#define MARK_FOLDER_WELL 3 //井文件文件夹标记
#define MARK_FOLDER_SMODEL 4 //表面模型文件文件夹标记
#define MARK_FOLDER_VMODEL 5 //体元模型文件文件夹标记
#define MARK_FOLDER_EXPLORATIONRESULT 6 //勘探成果文件文件夹标记
#define MARK_FOLDER_PROFILE 7 //连井剖面文件文件夹标记
#define MARK_FOLDER_CCOLUMN 8//综合柱状图文件文件夹标记
//对应ROLE_MARK_ITEM,标记item种类
#define MARK_ITEM_STRATASURFACE 1 //地层面文件标记
#define MARK_ITEM_FAULT 2 //断层面文件标记
#define MARK_ITEM_WELL 3 //井文件标记
#define MARK_ITEM_SMODEL 4 //表面模型文件标记
#define MARK_ITEM_VMODEL 5 //体元模型文件标记
#define MARK_ITEM_EXPLORATIONRESULT 6 //勘探成果文件标记
#define MARK_ITEM_PROFILE 7 //连井剖面文件标记
#define MARK_ITEM_CCOLUMN 8//综合柱状图文件标记
//对应ROLE_MARK_TYPE,标记对象类型
#define MARK_TYPE_STRATASURFACE 1 //地层面文件标记
#define MARK_TYPE_FAULT 2 //断层面文件标记
#define MARK_TYPE_WELL 3 //井文件标记
#define MARK_TYPE_SMODEL 4 //表面模型文件标记
#define MARK_TYPE_VMODEL 5 //体元模型文件标记
#define MARK_TYPE_EXPLORATIONRESULT 6 //勘探成果文件标记
#define MARK_TYPE_PROFILE 7 //连井剖面文件标记
#define MARK_TYPE_CCOLUMN 8//综合柱状图文件标记



#define MARK_EXPLORATIONRESULT_PIX 1 //成果图文件夹地层标记
#define MARK_EXPLORATIONRESULT_NAME 2 //成果图文件夹名称标记
#define MARK_EXPLORATIONRESULT_DEL 6 //地层对象删除标记
#define MARK_EXPLORATIONRESULT_CHANGEMODE 19//剖面图对象改变模式标记
#define MARK_EXPLORATIONRESULT_TRANSPARENT 12 //勘探成果图半透明标记


#define MARK_WELL_WELL 3 //井文件夹标井记
#define MARK_WELL_HEAD 4 //井文件夹井头标记
#define MARK_WELL_NAME 5 //井文件夹名称标记
#define MARK_WELL_DEL 7//井对象删除标记
#define MARK_WELL_CHANGEPIC 23//井对象改变贴图样式
#define MARK_WELL_SELECTPIC 24//选择井筒贴图图片


#define MARK_PROFILE_PIX 8//剖面图文件夹图片标记
#define MARK_PROFILE_NAME 9//剖面图文件夹名称标记
#define MARK_PROFILE_DEL 10//剖面图对象删除标记
#define MARK_PROFILE_TRANSPARENT 11//剖面图对象半透明标记

#define MARK_STRATASURFACE_TIN 13 //地层文件夹地层标记
#define MARK_STRATASURFACE_NAME 14 //地层文件夹地层名称标记
#define MARK_STRATASURFACE_DEL 15 //地层对象删除标记
#define MARK_STRATASURFACE_TRANSPARENT 16//地层对象半透明标记
#define MARK_STRATASURFACE_PROPERTY 17//地层属性标记
#define MARK_STRATASURFACE_COLORSET 18 //地层属性配色标记

#define MARK_SINGLEWELLCHART_DEL 20 //综合柱状图删除标记
#define MARK_SINGLEWELLCHART_PIX 21//综合柱状图图片标记
#define MARK_SINGLEWELLCHART_NAME 22//综合柱状图名称标记


typedef struct {
    QString name;
    QString text;
    int type;
}PROJECTITEM;
#endif // COMMON

