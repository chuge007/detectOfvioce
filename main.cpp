#include "mainwindow.h"

#include <QApplication>
#include <QModbusDataUnit>
#include <QNetworkProxy>
#include <QTextCodec>
#include <QApplication>
#include <QGuiApplication>
#if 1

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);


    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());  // 设置插件目录路径，指向打包后的插件文件夹
    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/sqldrivers");  // 设置插件目录路径，指向打包后的插件文件夹
    //QCoreApplication::addLibraryPath("D:/qt/5.12.4/msvc2017_64/plugins");  // 设置插件目录

    qDebug() << "Available drivers: " << QSqlDatabase::drivers();

    MainWindow w;
    w.show();
    return a.exec();
}
#endif

