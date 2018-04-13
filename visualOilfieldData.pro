#-------------------------------------------------
#
# Project created by QtCreator 2016-09-06T16:31:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visualOilfieldData
TEMPLATE = app
ROOT = D:\qt\OpenSceneGraph-3.4.0

SOURCES += main.cpp\
        mainwindow.cpp \
    eventadapter.cpp \
    function.cpp \
    graphicsview.cpp \
    treeview.cpp \
    projectDialog.cpp \
    explorationResult.cpp\
    well.cpp \
    projectOperation.cpp \
    profile.cpp \
    switchNodeFactory.cpp \
    folderMenu.cpp \
    itemMenu.cpp \
    loadWell.cpp \
    strataSurface.cpp \
    loadStrataSurface.cpp \
    xgradientslider.cpp \
    colorsetdialog.cpp \
    propertysetdialog.cpp \
    loadexplorationresult.cpp \
    loadprofile.cpp \
    checkdialog.cpp \
    layerdialog.cpp \
    singlewellchart.cpp \
    singlewelldialog.cpp \
    tin.cpp \
    layerscene.cpp \
    imageitem.cpp \
    loadsinglewellchart.cpp \
    profilecaldialog.cpp \
    form.cpp \
    texturedialog.cpp

HEADERS  += mainwindow.h \
    eventadapter.h \
    function.h \
    graphicsview.h \
    treeview.h \
    projectDialog.h \
    well.h \
    projectOperation.h \
    profile.h \
    texcoordgenerator.h \
    explorationResult.h \
    common.h \
    switchNodeFactory.h \
    folderMenu.h \
    itemMenu.h \
    loadWell.h \
    strataSurface.h \
    loadStrataSurface.h \
    xgradientslider.hpp \
    colorsetdialog.h \
    propertysetdialog.h \
    loadexplorationresult.h \
    loadprofile.h \
    checkdialog.h \
    layerdialog.h \
    singlewellchart.h \
    singlewelldialog.h \
    tin.h \
    layerscene.h \
    imageitem.h \
    loadsinglewellchart.h \
    profilecaldialog.h \
    form.h \
    texturedialog.h

FORMS    += \
    mainwindow.ui \
    projectDialog.ui \
    colorsetdialog.ui \
    propertysetdialog.ui \
    checkdialog.ui \
    layerdialog.ui \
    singlewelldialog.ui \
    profilecaldialog.ui \
    form.ui \
    texturedialog.ui

INCLUDEPATH  += $${ROOT}\include
LIBS += $${ROOT}\lib\libOpenThreads.dll.a
LIBS += $${ROOT}\lib\libosg.dll.a
LIBS += $${ROOT}\lib\libosgDB.dll.a
LIBS += $${ROOT}\lib\libosgGA.dll.a
LIBS += $${ROOT}\lib\libosgUtil.dll.a
LIBS += $${ROOT}\lib\libosgViewer.dll.a
LIBS += $${ROOT}\lib\libosgQt.dll.a
LIBS += $${ROOT}\lib\libosgText.dll.a
QT += opengl

DISTFILES += \
    images/body part.png \
    images/Bottom view.png \
    images/color.png \
    images/Cone.png \
    images/copy.png \
    images/crack.png \
    images/cuboid.png \
    images/Cutting.png \
    images/Cylinder.png \
    images/delete.png \
    images/Drag.png \
    images/Draw boundary.png \
    images/drilling.png \
    images/Ellipsoid.png \
    images/enlarge.png \
    images/exit.png \
    images/extend.png \
    images/further.png \
    images/Generate contours.png \
    images/Geological model.png \
    images/Hide Show.png \
    images/index.png \
    images/layer.png \
    images/Light control.png \
    images/line.png \
    images/Logs.png \
    images/merge.png \
    images/move.png \
    images/Narrow.png \
    images/new.png \
    images/North view.png \
    images/Online Help.png \
    images/open.png \
    images/Outsourcing box.png \
    images/panoramic.png \
    images/Parallel projection.png \
    images/Perforation.png \
    images/Perspective projection.png \
    images/perspective.png \
    images/Pick up.png \
    images/Plan view.png \
    images/point.png \
    images/profile.png \
    images/Property superposition.png \
    images/reduction.png \
    images/Reservoir Simulation.png \
    images/Revocation.png \
    images/Ring.png \
    images/Save as.png \
    images/save.png \
    images/select.png \
    images/Sphere.png \
    images/Staff.png \
    images/straight line.png \
    images/Stratified.png \
    images/Structural map.png \
    images/surface.png \
    images/table of Contents.png \
    images/text editor.png \
    images/Thematic map.png \
    images/Unselected.png \
    images/well deviation.png \
    images/Well trajectory.png \
    images/Wellhead.png \
    images/whirl£¨alone£©.png \
    images/whirl.png \
    images/XYZ.png \
    images/Yuantong.png \
    visualOilfieldData.pro.user \
    visualOilfieldData.pro.user.98741ee \
    visualOilfieldData.pro.user.785101f \
    visualOilfieldData.pro.user.bfafe03 \
    object_script.visualOilfieldData.Debug \
    object_script.visualOilfieldData.Release \
    Makefile \
    Makefile.Debug \
    Makefile.Release

RESOURCES += \
    icons.qrc

FONTS +=\
    fonts/STSONG.TTF\
    fonts/simkai.ttf
