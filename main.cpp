#include "mainwindow.h"

#include <QApplication>
#include <QModbusDataUnit>
#include <QNetworkProxy>
#include <QTextCodec>
#if 1

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);

    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
    MainWindow w;
    w.show();
    return a.exec();
}
#endif

