QT       += core gui widgets serialbus network sql  svg axcontainer charts opengl xml gui-private concurrent serialport

#webenginewidgets
#RC_ICONS = Phaseye.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++11  utf8

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addroute_dialog.cpp \
    dxflib/dl_dxf.cpp \
    dxflib/dl_writer_ascii.cpp \
    dxflib/dxfhelper.cpp \
    dxflib/dxfreader.cpp \
    gcodemodulation.cpp \
    imageProcessing.cpp \
    imageprocessing.cpp \
    main.cpp \
    mainwindow.cpp \
    scanMovecontrl/scandetect_frictionwelding.cpp \
    widgetDefin/Graphics_view_zoom.cpp \
    widgetDefin/QTableViewSpe.cpp \
    widgetDefin/graphicTool.cpp \
    widgetDefin/route_worksence.cpp \
    widgetDefin/tgraphicsviewrefactor.cpp

HEADERS += \
    DataBase.h \
    addroute_dialog.h \
    dxflib/dl_attributes.h \
    dxflib/dl_codes.h \
    dxflib/dl_creationadapter.h \
    dxflib/dl_creationinterface.h \
    dxflib/dl_dxf.h \
    dxflib/dl_entities.h \
    dxflib/dl_exception.h \
    dxflib/dl_extrusion.h \
    dxflib/dl_global.h \
    dxflib/dl_writer.h \
    dxflib/dl_writer_ascii.h \
    dxflib/dxfhelper.h \
    dxflib/dxfreader.h \
    gcodemodulation.h \
    imageProcessing.h \
    imageprocessing.h \
    libssh2_1.11.0_x64/libssh2.h \
    libssh2_1.11.0_x64/libssh2_publickey.h \
    libssh2_1.11.0_x64/libssh2_sftp.h \
    mainwindow.h \
    scanMovecontrl/modbusconfig.h \
    scanMovecontrl/scancontrolabstract.h \
    scanMovecontrl/scandetect_frictionwelding.h \
    widgetDefin/CoustomGraphicsView.h \
    widgetDefin/Graphics_view_zoom.h \
    widgetDefin/QTableViewSpe.h \
    widgetDefin/graphicTool.h \
    widgetDefin/route_worksence.h \
    widgetDefin/tgraphicsviewrefactor.h

FORMS += \
    ImageProcessing.ui \
    addroute_dialog.ui \
    gcodemodulation.ui \
    imageProcessing.ui \
    imageprocessing.ui \
    imageprocessing.ui \
    mainwindow.ui

#INCLUDEPATH += $$PWD/include
#LIBS += -L$$PWD/lib/ -ldxfrw

#LIBS += -L$$PWD/lib/ -ldxfrw
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

#选择合适的VTK版本
UT_SDK_VTK_VERSION = 9.1
#UT_SDK_VTK_VERSION = 8.1

CONFIG(debug, debug|release){
UT_SDK_VTK_VERSION = $${UT_SDK_VTK_VERSION}d
}

UT_SDK_VTK_LIBS = -lvtkChartsCore-$${UT_SDK_VTK_VERSION} \
    -lvtkCommonColor-$${UT_SDK_VTK_VERSION} \
    -lvtkCommonComputationalGeometry-$${UT_SDK_VTK_VERSION} \
    -lvtkCommonCore-$${UT_SDK_VTK_VERSION} \
    -lvtkCommonDataModel-$${UT_SDK_VTK_VERSION} \
    -lvtkCommonExecutionModel-$${UT_SDK_VTK_VERSION} \
    -lvtkCommonMath-$${UT_SDK_VTK_VERSION} \
    -lvtkCommonMisc-$${UT_SDK_VTK_VERSION} \
    -lvtkCommonSystem-$${UT_SDK_VTK_VERSION} \
    -lvtkCommonTransforms-$${UT_SDK_VTK_VERSION} \
    -lvtkDICOMParser-$${UT_SDK_VTK_VERSION} \
    -lvtkDomainsChemistry-$${UT_SDK_VTK_VERSION} \
    -lvtkDomainsChemistryOpenGL2-$${UT_SDK_VTK_VERSION} \
    -lvtkexpat-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersAMR-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersCore-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersExtraction-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersFlowPaths-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersGeneral-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersGeneric-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersGeometry-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersHybrid-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersHyperTree-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersImaging-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersModeling-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersParallel-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersParallelImaging-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersPoints-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersProgrammable-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersSelection-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersSMP-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersSources-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersStatistics-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersTexture-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersTopology-$${UT_SDK_VTK_VERSION} \
    -lvtkFiltersVerdict-$${UT_SDK_VTK_VERSION} \
    -lvtkfreetype-$${UT_SDK_VTK_VERSION} \
    -lvtkGeovisCore-$${UT_SDK_VTK_VERSION} \
    -lvtkgl2ps-$${UT_SDK_VTK_VERSION} \
    -lvtkglew-$${UT_SDK_VTK_VERSION} \
    -lvtkGUISupportQt-$${UT_SDK_VTK_VERSION} \
    -lvtkGUISupportQtSQL-$${UT_SDK_VTK_VERSION} \
    -lvtkhdf5_hl-$${UT_SDK_VTK_VERSION} \
    -lvtkhdf5-$${UT_SDK_VTK_VERSION} \
    -lvtkImagingColor-$${UT_SDK_VTK_VERSION} \
    -lvtkImagingCore-$${UT_SDK_VTK_VERSION} \
    -lvtkImagingFourier-$${UT_SDK_VTK_VERSION} \
    -lvtkImagingGeneral-$${UT_SDK_VTK_VERSION} \
    -lvtkImagingHybrid-$${UT_SDK_VTK_VERSION} \
    -lvtkImagingMath-$${UT_SDK_VTK_VERSION} \
    -lvtkImagingMorphological-$${UT_SDK_VTK_VERSION} \
    -lvtkImagingSources-$${UT_SDK_VTK_VERSION} \
    -lvtkImagingStatistics-$${UT_SDK_VTK_VERSION} \
    -lvtkImagingStencil-$${UT_SDK_VTK_VERSION} \
    -lvtkInfovisCore-$${UT_SDK_VTK_VERSION} \
    -lvtkInfovisLayout-$${UT_SDK_VTK_VERSION} \
    -lvtkInteractionImage-$${UT_SDK_VTK_VERSION} \
    -lvtkInteractionStyle-$${UT_SDK_VTK_VERSION} \
    -lvtkInteractionWidgets-$${UT_SDK_VTK_VERSION} \
    -lvtkIOAMR-$${UT_SDK_VTK_VERSION} \
    -lvtkIOCore-$${UT_SDK_VTK_VERSION} \
    -lvtkIOEnSight-$${UT_SDK_VTK_VERSION} \
    -lvtkIOExodus-$${UT_SDK_VTK_VERSION} \
    -lvtkIOGeometry-$${UT_SDK_VTK_VERSION} \
    -lvtkIOImage-$${UT_SDK_VTK_VERSION} \
    -lvtkIOImport-$${UT_SDK_VTK_VERSION} \
    -lvtkIOInfovis-$${UT_SDK_VTK_VERSION} \
    -lvtkIOLegacy-$${UT_SDK_VTK_VERSION} \
    -lvtkIOLSDyna-$${UT_SDK_VTK_VERSION} \
    -lvtkIOMINC-$${UT_SDK_VTK_VERSION} \
    -lvtkIOMovie-$${UT_SDK_VTK_VERSION} \
    -lvtkIONetCDF-$${UT_SDK_VTK_VERSION} \
    -lvtkIOParallel-$${UT_SDK_VTK_VERSION} \
    -lvtkIOParallelXML-$${UT_SDK_VTK_VERSION} \
    -lvtkIOPLY-$${UT_SDK_VTK_VERSION} \
    -lvtkIOSQL-$${UT_SDK_VTK_VERSION} \
    -lvtkIOTecplotTable-$${UT_SDK_VTK_VERSION} \
    -lvtkIOVideo-$${UT_SDK_VTK_VERSION} \
    -lvtkIOXML-$${UT_SDK_VTK_VERSION} \
    -lvtkIOXMLParser-$${UT_SDK_VTK_VERSION} \
    -lvtkjpeg-$${UT_SDK_VTK_VERSION} \
    -lvtkjsoncpp-$${UT_SDK_VTK_VERSION} \
    -lvtklibharu-$${UT_SDK_VTK_VERSION} \
    -lvtklibxml2-$${UT_SDK_VTK_VERSION} \
    -lvtklz4-$${UT_SDK_VTK_VERSION} \
    -lvtkmetaio-$${UT_SDK_VTK_VERSION} \
    -lvtkParallelCore-$${UT_SDK_VTK_VERSION} \
    -lvtkpng-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingAnnotation-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingContext2D-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingContextOpenGL2-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingCore-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingFreeType-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingGL2PSOpenGL2-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingImage-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingLabel-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingLOD-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingOpenGL2-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingQt-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingVolume-$${UT_SDK_VTK_VERSION} \
    -lvtkRenderingVolumeOpenGL2-$${UT_SDK_VTK_VERSION} \
    -lvtksqlite-$${UT_SDK_VTK_VERSION} \
    -lvtksys-$${UT_SDK_VTK_VERSION} \
    -lvtktiff-$${UT_SDK_VTK_VERSION} \
    -lvtkverdict-$${UT_SDK_VTK_VERSION} \
    -lvtkViewsContext2D-$${UT_SDK_VTK_VERSION} \
    -lvtkViewsCore-$${UT_SDK_VTK_VERSION} \
    -lvtkViewsInfovis-$${UT_SDK_VTK_VERSION} \
    -lvtkViewsQt-$${UT_SDK_VTK_VERSION} \
    -lvtkzlib-$${UT_SDK_VTK_VERSION} \



CONFIG(debug, debug|release){
UT_SDK_OTHER_LIBS += -lopencv_core453d \
    -lopencv_imgproc453d
}

CONFIG(release, debug|release){
UT_SDK_OTHER_LIBS += -lopencv_core453 \
    -lopencv_imgproc453
}

UT_SDK_OTHER_LIBS += -llibfftw3-3 \
    -lmkl_intel_lp64_dll \
    -lmkl_intel_thread_dll \
    -lmkl_core_dll

unix{
UT_SDK_OTHER_LIBS += -lopencv_core \
    -lopencv_imgproc \
    -lfftw3 \
    -lmkl_intel_lp64 \
    -lmkl_intel_thread \
    -lmkl_core
}

contains(QMAKE_HOST.arch, aarch64){
    message("编译目标平台: arm-64 编译器平台类型: $$QMAKE_HOST.arch")
    UT_SDK_APP_LIBS_PATHNAME = UtSDKAppLibs-linux-arm64
}else{
    message("编译目标平台: x86 编译器平台类型: $$QMAKE_HOST.arch")
    win32-msvc*{
    CONFIG(debug, debug|release){
             #UT_SDK_APP_LIBS_PATHNAME = UtSDKAppLibs-win64-debug
              UT_SDK_APP_LIBS_PATHNAME = UtSDKAppLibs-win64
        } else {
            UT_SDK_APP_LIBS_PATHNAME = UtSDKAppLibs-win64
        }
        LIBS += -lDbgHelp  -lSetupAPI
        QMAKE_CXXFLAGS_RELEASE += $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
        #release版也将生成“.pdb”后缀的调试信息文件
        QMAKE_LFLAGS_RELEASE = /NODEFAULTLIB:libcmt $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
        #QMAKE_LFLAGS_RELEASE = /INCREMENTAL:NO /DEBUG

        DEPEND_FILE = $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/NextUt.lib \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/NextAlgorithm.lib \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/NextScan.lib \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/NextDebug.lib \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/NextDraw.lib \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/NextHardware.lib \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/calculator.lib
    }

    unix{
        UT_SDK_APP_LIBS_PATHNAME = NextAppLibs-linux-x64

        DEPEND_FILE = $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/libNextUt.a \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/libNextAlgorithm.a \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/libNextScan.a \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/libNextDebug.a \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/libNextDraw.a \
            $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib/libNextHardware.a

    }
}

UT_SDK_LIBS_PATH = $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib
UT_SDK_INCLUDE_PATH = $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/include
UT_SDK_QT_DEPEND_PATH = $${PWD}/../$${UT_SDK_APP_LIBS_PATHNAME}/lib
LIBS += -L$${UT_SDK_LIBS_PATH} $${UT_SDK_VTK_LIBS} $${UT_SDK_OTHER_LIBS}

LIBS += -L$${UT_SDK_LIBS_PATH} \
        $${UT_SDK_VTK_LIBS} \
        $${UT_SDK_OTHER_LIBS} \
        -lNextAlgorithm \
        -lNextUt \
        -lNextDraw \
        -lNextScan \
        -lNextDebug \
        -lNextHardware \
        -lriffa \
        -lippcore \
        -lipps \
        -lippvm \
        -ldxflib \
        -lrmath \
        -lopennurbs \
        -lzlib \
        -lcal_entity \
        -lcal_self \
        -llibfftw3-3 \
        -lcalculator \
        -lCyAPI


win32 {
    LIBS += -lRpcrt4 -lAdvapi32
    LIBS += -luser32 -lgdi32
}


PRE_TARGETDEPS += $${DEPEND_FILE}

uinx{
    QMAKE_LFLAGS += -Wl,-rpath,$${UT_SDK_LIBS_PATH}
}

win32: QMAKE_CXXFLAGS+= -openmp
else:unix:!macx: QMAKE_CXXFLAGS+= -fopenmp -O2

#message("include path: $$UT_SDK_INCLUDE_PATH $${NEXT_QT_DEPENDT_PATH}")
INCLUDEPATH += $${UT_SDK_INCLUDE_PATH} $$PWD/PublicModules
INCLUDEPATH += $$PWD/widgetDefin
INCLUDEPATH += $$PWD/scanMovecontrl
INCLUDEPATH += $$PWD/dxflib

DEPENDPATH += $${NEXT_QT_DEPENDT_PATH}
win32:CONFIG(release, debug|release): LIBS +=
else:win32:CONFIG(debug, debug|release): LIBS += -lqBreakpad
else:unix: LIBS += -lNextAlgorithm -lm -lfftw3 -lopencv_core -lopencv_imgproc -lgomp -lpthread -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5  -ldl

win32-msvc*{
#OTHER_FILES += scripts/resource.rc
#RC_FILE = scripts/resource.rc
#QMAKE_PRE_LINK = $${PWD}/scripts/prebuild.bat \"$${PWD}/scripts\"
}

unix {
INCLUDEPATH += /usr/local/include
QMAKE_LFLAGS += -Wl,-rpath,$${UT_SDK_LIBS_PATH}
}



DISTFILES += \
    libssh2_1.11.0_x64/libssh2.dll \
    libssh2_1.11.0_x64/libssh2.lib \
    libssh2_1.11.0_x64/libssh2_static.lib



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libssh2_1.11.0_x64/ -llibssh2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libssh2_1.11.0_x64/ -llibssh2d
else:unix: LIBS += -L$$PWD/libssh2_1.11.0_x64/ -llibssh2

INCLUDEPATH += $$PWD/libssh2_1.11.0_x64
DEPENDPATH += $$PWD/libssh2_1.11.0_x64

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libssh2_1.11.0_x64/ -llibssh2_static
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libssh2_1.11.0_x64/ -llibssh2_staticd
else:unix: LIBS += -L$$PWD/libssh2_1.11.0_x64/ -llibssh2_static

INCLUDEPATH += $$PWD/libssh2_1.11.0_x64
DEPENDPATH += $$PWD/libssh2_1.11.0_x64

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libssh2_1.11.0_x64/liblibssh2_static.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libssh2_1.11.0_x64/liblibssh2_staticd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libssh2_1.11.0_x64/libssh2_static.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libssh2_1.11.0_x64/libssh2_staticd.lib
else:unix: PRE_TARGETDEPS += $$PWD/libssh2_1.11.0_x64/liblibssh2_static.a
