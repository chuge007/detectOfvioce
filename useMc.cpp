#include "MotionControl.h"
#include <QApplication>
#include <QScreen> // 用于获取屏幕信息

MotionControl *mcWindow;

void useMotionControl()
{
    // 这些高DPI设置保持不变，它们是开启高DPI缩放的关键
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    // 建议使用 Round 策略，避免非整数缩放引起的问题
    //QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);
    if(mcWindow==nullptr){

        mcWindow = new MotionControl();

        // 获取主屏幕信息
        QScreen *screen = QApplication::primaryScreen();
        if (screen) {
            // 获取屏幕的可用几何尺寸（不包括任务栏等）
            QRect availableGeometry = screen->availableGeometry();

            // 计算新窗口的尺寸：屏幕可用宽度的2/3，高度的2/3
            int newWidth = availableGeometry.width() * 5 / 6;
            int newHeight = availableGeometry.height() * 5 / 6;

            // 设置主窗口的尺寸
            mcWindow->resize(newWidth, newHeight);

            // 可选：将窗口移动到屏幕中央 (如果需要)
            int x = availableGeometry.x() + (availableGeometry.width() - newWidth) / 2;
            int y = availableGeometry.y() + (availableGeometry.height() - newHeight) / 2;
            mcWindow->move(x, y);
        }
    }
    mcWindow->show();
}

void dlMotionControl(){

    delete  mcWindow;
    mcWindow=nullptr;

}
