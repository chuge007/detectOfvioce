#include "mainwindow.h"

#include <QApplication>
#include <QModbusDataUnit>
#include <QNetworkProxy>
#include <QTextCodec>
#include <QApplication>
#include <QGuiApplication>
#if 1

//int main(int argc, char *argv[])
//{
//    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

////    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

////    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

////    qputenv("QT_SCALE_FACTOR", "1");
////    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0");
////    qputenv("QT_ENABLE_HIGHDPI_SCALING", "0");


//    QApplication a(argc, argv);


////    qreal currentDpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();
////    QFont defaultFont = a.font();
////    QFontInfo fontInfo(defaultFont);  // 获取当前字体信息
////    qreal baseDpi = fontInfo.pixelSize() / defaultFont.pointSizeF() * 72.0;

////    // 然后缩放
////    defaultFont.setPointSizeF(defaultFont.pointSizeF() * currentDpi / baseDpi);
////    a.setFont(defaultFont);




//    qDebug() << "Logical DPI:" << QGuiApplication::primaryScreen()->logicalDotsPerInch();
//    qDebug() << "Device Pixel Ratio:" << QGuiApplication::primaryScreen()->devicePixelRatio();



//    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
//    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());  // 设置插件目录路径，指向打包后的插件文件夹
//    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/sqldrivers");  // 设置插件目录路径，指向打包后的插件文件夹
//    //QCoreApplication::addLibraryPath("D:/qt/5.12.4/msvc2017_64/plugins");  // 设置插件目录

//    qDebug() << "Available drivers: " << QSqlDatabase::drivers();

//    MainWindow w;

//    // 获取当前屏幕的可用大小（不包含任务栏）
//    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
//    int screenWidth = screenGeometry.width();
//    int screenHeight = screenGeometry.height();

//    // 你设计的窗口初始大小
//    QSize designedSize(2046, 1426);

//    // 计算缩放比例（最大为 1.0）
//    qreal scaleW = screenWidth / static_cast<qreal>(designedSize.width());
//    qreal scaleH = screenHeight / static_cast<qreal>(designedSize.height());
//    qreal scale = qMin(scaleW, scaleH);
//    scale = qMin(scale, 1.0); // 确保不会放大

//    // 设置缩放后的窗口大小
//    w.resize(designedSize.width() * scale, designedSize.height() * scale);


//    w.show();
//    return a.exec();
//}



int main(int argc, char *argv[])
{
    // 开启高 DPI 支持
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

        //qputenv("QT_SCALE_FACTOR", "1");
        //qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0");
        //qputenv("QT_ENABLE_HIGHDPI_SCALING", "0");

    QApplication a(argc, argv);

    // 动态调整窗口大小和位置
    MainWindow w;
    w.show();

    return a.exec();
}



#endif

