#include "mainwindow.h"

#include <QApplication>
#include <QModbusDataUnit>
#include <QNetworkProxy>
#if 1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
    MainWindow w;
    w.show();
    return a.exec();
}
#endif

