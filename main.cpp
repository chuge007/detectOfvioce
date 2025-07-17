//#include "mainwindow.h"

//#include <QApplication>
//#include <QModbusDataUnit>
//#include <QNetworkProxy>
//#include <QTextCodec>
//#include <QApplication>
//#include <QGuiApplication>
//#include <QScreen>     // 用于获取屏幕信息
//#include <QGuiApplication> // 用于访问 QScreen
//#if 1

//#include "mainwindow.h" // 包含你的 MainWindow 头文件

//int main(int argc, char *argv[])
//{
//    // 这些设置保持不变，它们是开启高DPI缩放的关键
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
//    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

//    QApplication app(argc, argv);

//    MainWindow mainWindow; // 你的主窗口实例

//    mainWindow.show();

//    return app.exec();
//}
//#endif



#include "mainwindow.h"
#include <QApplication>
#include <QScreen> // 用于获取屏幕信息

int main(int argc, char *argv[])
{
    // 这些高DPI设置保持不变，它们是开启高DPI缩放的关键
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    // 建议使用 Round 策略，避免非整数缩放引起的问题
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);

    QApplication app(argc, argv);

    MainWindow mainWindow; // 你的主窗口实例

    // 获取主屏幕信息
    QScreen *screen = QApplication::primaryScreen();
    if (screen) {
        // 获取屏幕的可用几何尺寸（不包括任务栏等）
        QRect availableGeometry = screen->availableGeometry();

        // 计算新窗口的尺寸：屏幕可用宽度的2/3，高度的2/3
        int newWidth = availableGeometry.width() * 4 / 5;
        int newHeight = availableGeometry.height() * 4 / 5;

        // 设置主窗口的尺寸
        mainWindow.resize(newWidth, newHeight);

        // 可选：将窗口移动到屏幕中央 (如果需要)
         int x = availableGeometry.x() + (availableGeometry.width() - newWidth) / 2;
         int y = availableGeometry.y() + (availableGeometry.height() - newHeight) / 2;
         mainWindow.move(x, y);
    }

    mainWindow.show();

    return app.exec();
}
