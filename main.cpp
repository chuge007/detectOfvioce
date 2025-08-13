

#include "MotionControl.h"
#include <QApplication>
#include <QScreen> // 用于获取屏幕信息



// 设置应用程序样式
QString styleSheet = R"(
                     /* 主窗口样式 */
                     QMainWindow {
                     background-color: #f0f0f0;
                     }

                     /* 状态栏样式 */
                     QStatusBar {
                     background-color: #2b2b2b;
                     color: white;
                     border-top: 1px solid #555;
                     font-size: 12px;
                     }

                     /* 通用按钮样式 */
                     QPushButton {
                     background-color: #e0e0e0;
                     border: 1px solid #ccc;
                     border-radius: 4px;
                     padding: 8px 16px;
                     font-size: 12px;
                     min-height: 20px;
                     }

                     QFrame {
                     background-color: white;
                     border: 1px solid #ccc;
                     border-radius: 4px;
                     }

                     /* 启动按钮特殊样式 */
                     QPushButton#startButton {
                     background-color: #4CAF50;
                     color: white;
                     font-weight: bold;
                     padding: 12px 20px;
                     font-size: 14px;
                     }

                     QPushButton#startButton:hover {
                     background-color: #45a049;
                     }

                     /* 停止按钮样式 */
                     QPushButton#stopButton {
                     background-color: #f44336;
                     color: white;
                     font-weight: bold;
                     }

                     QPushButton#stopButton:hover {
                     background-color: #da190b;
                     }

                     /* 组合框样式 */
                     QComboBox {
                     background-color: white;
                     border: 1px solid #ccc;
                     border-radius: 4px;
                     padding: 5px 8px;
                     font-size: 12px;
                     min-height: 20px;
                     }

                     QComboBox:hover {
                     border-color: #999;
                     }

                     QComboBox::drop-down {
                     border: none;
                     width: 20px;
                     }

                     QComboBox::down-arrow {
                     image: none;
                     border-left: 5px solid transparent;
                     border-right: 5px solid transparent;
                     border-top: 5px solid #666;
                     margin-right: 5px;
                     }

                     /* 输入框样式 */
                     QLineEdit {
                     background-color: white;
                     border: 1px solid #ccc;
                     border-radius: 4px;
                     padding: 5px 8px;
                     font-size: 12px;
                     min-height: 20px;
                     }

                     QLineEdit:focus {
                     border-color: #4CAF50;
                     outline: none;
                     }

                     /* 组框样式 */
                     QGroupBox {
                     font-weight: bold;
                     font-size: 12px;
                     color: #333;
                     border: 1px solid #ccc;
                     border-radius: 6px;
                     margin-top: 10px;
                     padding-top: 10px;
                     }

                     QGroupBox::title {
                     subcontrol-origin: margin;
                     subcontrol-position: top left;
                     padding: 0 8px;
                     background-color: #f0f0f0;
                     border: none;
                     }

                     /* 表格样式 */
                     QTableWidget {
                     background-color: white;
                     border: 1px solid #ccc;
                     gridline-color: #ddd;
                     font-size: 11px;
                     }

                     QTableWidget::item {
                     padding: 4px 8px;
                     border: none;
                     }

                     QTableWidget::item:selected {
                     background-color: #3399ff;
                     color: white;
                     }

                     QHeaderView::section {
                     background-color: #e8e8e8;
                     border: 1px solid #ccc;
                     border-left: none;
                     border-right: none;
                     padding: 6px 8px;
                     font-weight: bold;
                     font-size: 11px;
                     }

                     QHeaderView::section:first {
                     border-left: 1px solid #ccc;
                     }

                     QHeaderView::section:last {
                     border-right: 1px solid #ccc;
                     }

                     QCheckBox::indicator {
                     width: 16px;
                     height: 16px;
                     border: 1px solid #ccc;
                     border-radius: 3px;
                     background-color: white;
                     }

                     /* 标签样式 */
                     QLabel {
                     font-size: 12px;
                     color: #333;
                     }


                     )";



int main(int argc, char *argv[])
{
    // 这些高DPI设置保持不变，它们是开启高DPI缩放的关键
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    // 建议使用 Round 策略，避免非整数缩放引起的问题
    //QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);

    QApplication app(argc, argv);

    app.setStyleSheet(styleSheet);

    MotionControl MotionControl; // 你的主窗口实例

    // 获取主屏幕信息
    QScreen *screen = QApplication::primaryScreen();
    if (screen) {
        // 获取屏幕的可用几何尺寸（不包括任务栏等）
        QRect availableGeometry = screen->availableGeometry();

        // 计算新窗口的尺寸：屏幕可用宽度的2/3，高度的2/3
        int newWidth = availableGeometry.width() * 5 / 6;
        int newHeight = availableGeometry.height() * 7 / 8;

        // 设置主窗口的尺寸
        MotionControl.resize(newWidth, newHeight);

        // 可选：将窗口移动到屏幕中央 (如果需要)
        int x = availableGeometry.x() + (availableGeometry.width() - newWidth) / 2;
        int y = availableGeometry.y() + (availableGeometry.height() - newHeight) / 2;
        MotionControl.move(x, y);
    }

    MotionControl.show();

    return app.exec();
}






//#include "MotionControl.h"

//#include <QApplication>
//#include <QModbusDataUnit>
//#include <QNetworkProxy>
//#include <QTextCodec>
//#include <QApplication>
//#include <QGuiApplication>
//#include <QScreen>     // 用于获取屏幕信息
//#include <QGuiApplication> // 用于访问 QScreen
//#if 1

//#include "MotionControl.h" // 包含你的 MotionControl 头文件

//int main(int argc, char *argv[])
//{
//    // 这些设置保持不变，它们是开启高DPI缩放的关键
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
//    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

//    QApplication app(argc, argv);

//    MotionControl MotionControl; // 你的主窗口实例

//    MotionControl.show();

//    return app.exec();
//}
//#endif

