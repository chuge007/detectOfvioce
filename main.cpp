#include "mainwindow.h"

#include <QApplication>
#include <QModbusDataUnit>
#include <QNetworkProxy>
#include <QTextCodec>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>     // 用于获取屏幕信息
#include <QGuiApplication> // 用于访问 QScreen

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



//int main(int argc, char *argv[])
//{
//    // 开启高 DPI 支持
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

//    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
//    //qputenv("QT_SCALE_FACTOR", "1");
//    //qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0");
//    //qputenv("QT_ENABLE_HIGHDPI_SCALING", "0");

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}

#include <QApplication>
#include <QMainWindow>
#include <QScreen>
#include <QGuiApplication>
#include <QDebug> // 用于调试输出

#include <QApplication>
#include <QMainWindow>
#include <QScreen>
#include <QGuiApplication>
#include <QDebug> // 务必包含这个头文件，用于 qDebug()

#include "mainwindow.h" // 包含你的 MainWindow 头文件

int main(int argc, char *argv[])
{
    // 这些设置保持不变，它们是开启高DPI缩放的关键
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

    QApplication app(argc, argv);

    MainWindow mainWindow; // 你的主窗口实例

//    // --- 调试输出 1: 窗口内容初始化后的最小尺寸提示 ---
//    // 此时，MainWindow 的构造函数已经执行，内部的控件和布局已经设置完毕。
//    // 这个 minimumSizeHint() 反映了你的 UI 设计在“最紧凑”状态下的需求。
//    qDebug() << "--- Debug Phase 1: After MainWindow Creation ---";
//    qDebug() << "MainWindow's initial minimumSizeHint():" << mainWindow.minimumSizeHint();
//    qDebug() << "MainWindow's initial size():" << mainWindow.size(); // 通常是默认的或者0x0

//    QScreen *primaryScreen = QGuiApplication::primaryScreen();

//    if (primaryScreen) {
//        QRect screenAvailableGeometry = primaryScreen->availableGeometry();

//        // 例如，我们还是用 80% 缩放为例，或者换成你想要的等距缩小计算
//        const double scaleFactor = 0.8;
//        int targetWidth = static_cast<int>(screenAvailableGeometry.width() * scaleFactor);
//        int targetHeight = static_cast<int>(screenAvailableGeometry.height() * scaleFactor);

//        // --- 调试输出 2: 目标尺寸 ---
//        qDebug() << "--- Debug Phase 2: Before Resize ---";
//        qDebug() << "Screen Available Geometry (Logic):" << screenAvailableGeometry;
//        qDebug() << "Calculated Target Window Size (Logic):" << targetWidth << "x" << targetHeight;

//        mainWindow.resize(targetWidth, targetHeight);

//        // --- 调试输出 3: resize() 后的实际尺寸和最小尺寸提示 ---
//        // 这一步至关重要！
//        // 如果 mainWindow.size() 不等于 targetWidth x targetHeight，
//        // 并且 minimumSizeHint() 很大，那么问题就出在 UI 内容上。
//        qDebug() << "--- Debug Phase 3: After Resize ---";
//        qDebug() << "MainWindow's minimumSizeHint() after resize attempt:" << mainWindow.minimumSizeHint();
//        qDebug() << "Actual Window Size After Resize (Logic):" << mainWindow.size();


//        int newX = screenAvailableGeometry.x() + (screenAvailableGeometry.width() - targetWidth) / 2;
//        int newY = screenAvailableGeometry.y() + (screenAvailableGeometry.height() - targetHeight) / 2;

//        mainWindow.move(newX, newY);

//        // --- 调试输出 4: move() 后的实际位置 ---
//        qDebug() << "--- Debug Phase 4: After Move ---";
//        qDebug() << "Calculated Target Window Position (Logic):" << newX << "," << newY;
//        qDebug() << "Actual Window Position After Move (Logic):" << mainWindow.pos();

//    } else {
//        mainWindow.resize(800, 600);
//        mainWindow.move(100, 100);
//        qDebug() << "Warning: Could not retrieve primary screen information. Using default size and position.";
//    }

    mainWindow.show();

    return app.exec();
}
#endif

