#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DataBase.h"
#include "graphicTool.h"
#include "CoustomGraphicsView.h"
#include "dxfhelper.h"
#include "scandetect_frictionwelding.h"
#include "imageprocessing.h"
#include "gcodemodulation.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "ascan.h"
=======
>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da
=======
#include "ascan.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <tool.h>
>>>>>>> c82df02 (界面)

#include <QModbusDataUnit>
#include <QDebug>
#include <QByteArray>
#include <iostream>
#include <vector>
#include <algorithm> // for std::reverse
#include <iomanip>
#include <cstring> // for memcpy
#include <cstdint>
#include <QtEndian>
#include <QDir>
#include <QObject>
#include <QList>
#include <QStandardItem>
#include <QFileDialog>
#include <QAxObject>
#include <QProcess>
#include <QDir>
#include <QProcessEnvironment>
#include <QWaitCondition>
#include <QInputDialog>
<<<<<<< HEAD


ScanControlAbstract *MainWindow::scanDetectCtrl=0;
=======
#include <QScreen>
#include <QGuiApplication>
#include <QWidget>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QFont>

ScanControlAbstract *MainWindow::scanDetectCtrl=0;

>>>>>>> c82df02 (界面)


void MainWindow::init()
{
    // 使用用户数据目录存放数据库文件
    QString appDataPath = QCoreApplication::applicationDirPath()+"/date";
    QDir dir(appDataPath);
    if (!dir.exists())
        dir.mkpath(".");

    // 构建目标数据库完整路径
    QString targetDb = "weld_check_data.db";
    QString targetPath = appDataPath + "/" + targetDb;
    qDebug() << "Db path:" << targetPath;

    // 检查目标数据库是否存在
    if (QFileInfo::exists(targetPath)) {
        // 存在则直接初始化数据库
        openDb(targetPath);

    }
    else {
        // 不存在则先创建再初始化
        createNewDb(targetPath);
        openDb(targetPath);
    }


    // 创建一个表名为 "2d" 的表，包含主键 id，其他字段可以根据需要添加
    QSqlQuery query(db);
    QString createTableSQL =  QString::fromLocal8Bit(R"(
                                                     CREATE TABLE IF NOT EXISTS Initialization (
                                                     id INTEGER PRIMARY KEY AUTOINCREMENT,
                                                     类型 TEXT,
                                                     起点x TEXT,
                                                     起点y TEXT,
                                                     起点z TEXT,
                                                     起点r TEXT,
                                                     过渡点x TEXT,
                                                     过渡点y TEXT,
                                                     过渡点z TEXT,
                                                     过渡点r TEXT,
                                                     终点x TEXT,
                                                     终点y TEXT,
                                                     终点z TEXT,
                                                     终点r TEXT
                                                     )
                                                     )");
    if (!query.exec(createTableSQL)) {
        qDebug() << "创建表失败:" << query.lastError().text();
    } else {
        qDebug() << "表创建成功或者已存在";
    }

    model = new QSqlTableModel(this, db);
    model->setTable("Initialization");
    ui->tableView->setModel(model);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();


    if (!db.transaction()) {
        qDebug() << "Failed to start transaction:" << db.lastError().text();
        QMessageBox::critical(this, "Error", "无法开启数据库事务");
        return;
    }


    settings=new QSettings(appDataPath+"/settings.ini", QSettings::IniFormat);

    //config.loadConfig(appDataPath+"/settings.ini");

    ui->stopScan_but->setCheckable(true);



}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , modbusDevice(new QModbusTcpClient(this))
    , config(NdtCfgMachine::getInstance())
{
    ui->setupUi(this);

    init();


    scanDetectCtrl = new scanDetect_frictionWelding();
    scanDetectCtrl->Rsettings=settings;

    connect(scanDetectCtrl, &ScanControlAbstract::modbusStateChange,this, &MainWindow::modbusStateChange);
    connect(ui->xAdd_but, &QPushButton::pressed, scanDetectCtrl, &ScanControlAbstract::on_xAddBtn_pressed);
    connect(ui->xAdd_but, &QPushButton::released, scanDetectCtrl, &ScanControlAbstract::on_xAddBtn_released);
    connect(ui->xSub_but, &QPushButton::pressed, scanDetectCtrl, &ScanControlAbstract::on_xSubBtn_pressed);
    connect(ui->xSub_but, &QPushButton::released, scanDetectCtrl, &ScanControlAbstract::on_xSubBtn_released);
    connect(ui->yAdd_but, &QPushButton::pressed, scanDetectCtrl, &ScanControlAbstract::on_yAddBtn_pressed);
    connect(ui->yAdd_but, &QPushButton::released, scanDetectCtrl, &ScanControlAbstract::on_yAddBtn_released);
    connect(ui->ySub_but, &QPushButton::pressed, scanDetectCtrl, &ScanControlAbstract::on_ySubBtn_pressed);
    connect(ui->ySub_but, &QPushButton::released, scanDetectCtrl, &ScanControlAbstract::on_ySubBtn_released);
    connect(ui->zAdd_but, &QPushButton::pressed, scanDetectCtrl, &ScanControlAbstract::on_zAddBtn_pressed);
    connect(ui->zAdd_but, &QPushButton::released, scanDetectCtrl, &ScanControlAbstract::on_zAddBtn_released);
    connect(ui->zSub_but, &QPushButton::pressed, scanDetectCtrl, &ScanControlAbstract::on_zSubBtn_pressed);
    connect(ui->zSub_but, &QPushButton::released, scanDetectCtrl, &ScanControlAbstract::on_zSubBtn_released);
    connect(ui->rAdd_but, &QPushButton::pressed, scanDetectCtrl, &ScanControlAbstract::on_rAddBtn_pressed);
    connect(ui->rAdd_but, &QPushButton::released, scanDetectCtrl, &ScanControlAbstract::on_rAddBtn_released);
    connect(ui->rSub_but, &QPushButton::pressed, scanDetectCtrl, &ScanControlAbstract::on_rSubBtn_pressed);
    connect(ui->rSub_but, &QPushButton::released, scanDetectCtrl, &ScanControlAbstract::on_rSubBtn_released);

    connect(ui->writeInPLC_but, &QPushButton::clicked, this, &MainWindow::pbWriteInPLC);
    connect(scanDetectCtrl, &ScanControlAbstract::positionChange, this, &MainWindow::updatePosition);
    connect(ui->alarmReset_but, &QPushButton::clicked, scanDetectCtrl, &ScanControlAbstract::on_alarmResetBtn_clicked);
    //connect(ui->startScan_But, &QPushButton::clicked, scanDetectCtrl, &ScanControlAbstract::on_startScanBtn_clicked);
    connect(ui->stopScan_but, &QPushButton::clicked, scanDetectCtrl, &ScanControlAbstract::on_stopScanBtn_clicked);
    connect(ui->stopScan_but, &QPushButton::released, scanDetectCtrl, &ScanControlAbstract::on_stopScanBtn_clicked);
    connect(ui->endScan_but, &QPushButton::clicked, scanDetectCtrl, &ScanControlAbstract::on_endScanBtn_clicked);
    connect(ui->pbBackO,&QPushButton::clicked, scanDetectCtrl, &ScanControlAbstract::onBackOriginBtn_clicked);

    connect(ui->startScan_But, &QPushButton::clicked, this, &MainWindow::pbStartScanBtn);
    connect(ui->lineVelocity_lin, &QLineEdit::editingFinished, this, &MainWindow::PblinVelocity_lin);
    connect(ui->arcVelocity_lin, &QLineEdit::editingFinished, this, &MainWindow::PbarcVelocity_lin);
    connect(ui->AxleVelocity_lin, &QLineEdit::editingFinished, this, &MainWindow::PbAxleVelocity_lin);
    connect(ui->pointVelocity_lin, &QLineEdit::editingFinished, this, &MainWindow::PbPointVelocity_lin);
    connect(ui->setOrigin_but, &QPushButton::clicked, this, &MainWindow::PbSetOrigin);
    connect(ui->insertArcPos_but, &QPushButton::clicked, this, &MainWindow::pbAddArcPos);
    connect(ui->insertLinePos_but, &QPushButton::clicked, this, &MainWindow::pbAddLinePos);
    connect(ui->DXFimport_but, &QPushButton::clicked, this, &MainWindow::pbDXFimportBut);
    connect(ui->creatG_but, &QPushButton::clicked, this, &MainWindow::PbCreatGcode);
    connect(ui->cleanTable_but, &QPushButton::clicked, this, &MainWindow::cleanTable);
    connect(ui->connect_but, &QPushButton::clicked, this, &MainWindow::PbModbusConnectBtn);
    connect(ui->moveToPosition_but, &QPushButton::clicked, this, &MainWindow::PbMoveToPosition);
    connect(ui->plcType_cb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::cbSelectPlcType);
    connect(ui->moveUpTabelRow_btu, &QPushButton::clicked, this, &MainWindow::pbmoveUpForSort);
    connect(ui->moveDownTabelRow_btu,&QPushButton::clicked, this, &MainWindow::pbmoveDownForSort);
    connect(ui->setTrajecStart_but,&QPushButton::clicked, this, &MainWindow::on_setTrajec_start_clicked);
<<<<<<< HEAD
<<<<<<< HEAD
    connect(ui->getCurryPoint_but,&QPushButton::clicked, this, &MainWindow::pbGetModelPoint);
=======
    connect(ui->getCurryPoint_but,&QPushButton::clicked, this, &MainWindow::pbGetCurryPoint);
>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da
=======
    connect(ui->getCurryPoint_but,&QPushButton::clicked, this, &MainWindow::pbGetModelPoint);
>>>>>>> c82df02 (界面)
    connect(ui->moveDirectionNot_but,&QPushButton::clicked, this, &MainWindow::pbMoveDirectionNot);
    connect(ui->pBdeletePiece,&QPushButton::clicked, this, &MainWindow::pbdeletePiece);
    connect(ui->pBbrazing,&QPushButton::clicked, this, &MainWindow::pBbrazing);
    connect(ui->imageProcess_but,&QPushButton::clicked, this, &MainWindow::PbImageProcess);
<<<<<<< HEAD
<<<<<<< HEAD
    connect(ui->ascan_but,&QPushButton::clicked, this, &MainWindow::pbAscan);
=======
>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da
=======
    connect(ui->ascan_but,&QPushButton::clicked, this, &MainWindow::pbAscan);
>>>>>>> c82df02 (界面)

    connect(ui->cBworkpiece,
            QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::selectWorkpiece);
    connect(ui->pbNewPiece,&QPushButton::clicked, this, &MainWindow::pbnewPiece);

    connect(ui->trajectoryOffset_but,&QPushButton::clicked, this, &MainWindow::PbtrajectoryOffset);



    addRoute = new addRoute_dialog(this);

    connect(addRoute, &addRoute_dialog::addBut_x_pressed, scanDetectCtrl, &ScanControlAbstract::on_xAddBtn_pressed);
    connect(addRoute, &addRoute_dialog::addBut_x_released, scanDetectCtrl, &ScanControlAbstract::on_xAddBtn_released);
    connect(addRoute, &addRoute_dialog::subBut_x_pressed, scanDetectCtrl, &ScanControlAbstract::on_xSubBtn_pressed);
    connect(addRoute, &addRoute_dialog::subBut_x_released, scanDetectCtrl, &ScanControlAbstract::on_xSubBtn_released);
    connect(addRoute, &addRoute_dialog::addBut_y_pressed, scanDetectCtrl, &ScanControlAbstract::on_yAddBtn_pressed);
    connect(addRoute, &addRoute_dialog::addBut_y_released, scanDetectCtrl, &ScanControlAbstract::on_yAddBtn_released);
    connect(addRoute, &addRoute_dialog::subBut_y_pressed, scanDetectCtrl, &ScanControlAbstract::on_ySubBtn_pressed);
    connect(addRoute, &addRoute_dialog::subBut_y_released, scanDetectCtrl, &ScanControlAbstract::on_ySubBtn_released);
    connect(addRoute, &addRoute_dialog::addBut_z_pressed, scanDetectCtrl, &ScanControlAbstract::on_zAddBtn_pressed);
    connect(addRoute, &addRoute_dialog::subBut_z_pressed, scanDetectCtrl, &ScanControlAbstract::on_zSubBtn_pressed);
    connect(addRoute, &addRoute_dialog::addBut_z_released, scanDetectCtrl, &ScanControlAbstract::on_zAddBtn_released);
    connect(addRoute, &addRoute_dialog::subBut_z_released, scanDetectCtrl, &ScanControlAbstract::on_zSubBtn_released);

    connect(addRoute, &addRoute_dialog::subBut_r_pressed, scanDetectCtrl, &ScanControlAbstract::on_rSubBtn_pressed);
    connect(addRoute, &addRoute_dialog::subBut_r_released, scanDetectCtrl, &ScanControlAbstract::on_rSubBtn_released);

    connect(addRoute, &addRoute_dialog::addBut_r_pressed, scanDetectCtrl, &ScanControlAbstract::on_rAddBtn_pressed);
    connect(addRoute, &addRoute_dialog::addBut_r_released, scanDetectCtrl, &ScanControlAbstract::on_rAddBtn_released);


    imageProcessingTool = new imageprocessing();
    imageProcessingTool->settings=settings;

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> c82df02 (界面)
    scan=new ascan();
    scan->Rsettings=settings;
    scan->mw=this;

<<<<<<< HEAD
=======
>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da
=======
>>>>>>> c82df02 (界面)
    gcodeEidt=new gCodeModulation();

    zomm_gview = new Graphics_view_zoom(ui->graphicsView);
    scene = new route_worksence( ui->graphicsView );

    ui->graphicsView->setScene( scene );

    //zomm_gview->set_modifiers(Qt::NoModifier);
    // 将场景原点移动到视图的左上角
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //ui->graphicsView->setSceneRect(0, 0, 750, 500);

    connect(zomm_gview,SIGNAL(zoomed(void)),this,SLOT(graphics_view_zoom(void)));

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::tableSelectionChanged);

    connect(scene, &QGraphicsScene::selectionChanged,
            this, &MainWindow::graphicsSelectionChanged);

    connect(ui->graphicsView, SIGNAL(zoomChanged(qreal)),
            this, SLOT(updateSence()));


    initSetting();

    saveOriginalWidgetStates(this->centralWidget());


}

MainWindow::~MainWindow()
{


    saveSetting();
<<<<<<< HEAD
    closeDb();
    delete model;
=======

    if (model) {
        model->clear();
        delete model;
        model = nullptr;
    }
    closeDb();

>>>>>>> c82df02 (界面)
    delete addRoute;
    delete scene;
    delete zomm_gview;
    delete scanDetectCtrl;
    delete settings;
    delete imageProcessingTool;
<<<<<<< HEAD
<<<<<<< HEAD
    delete scan;
=======
>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da
=======
    delete scan;
>>>>>>> c82df02 (界面)
    delete ui;




}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 这里做必要的保存、释放动作（如果不是都放在析构里）

    qApp->quit();  // 请求退出事件循环，程序退出

    event->accept();

    forceExit();
}


void MainWindow::updatePosition(QPointF pos,float cur_r,float cur_z)
{
    scanDetectCtrl->isAddRoute_dialogOpen=addRoute->isOpen;
    //qDebug()<<"updatePosition isAddRoute_dialogOpen: "<<scanDetectCtrl->isAddRoute_dialogOpen;

    ui->xCurPos_lab->setText(QString::number(static_cast<double>(pos.x()), 'f', 3));
    ui->yCurPos_lab->setText(QString::number(static_cast<double>(pos.y()), 'f', 3));
    ui->zCurPos_lab->setText(QString::number(static_cast<double>(cur_z), 'f', 3));
    ui->rCurPos_lab->setText(QString::number(static_cast<double>(cur_r), 'f', 3));

    addRoute->set_Xcurpos(QString::number(static_cast<double>(pos.x()), 'f', 3));
    addRoute->set_Ycurpos(QString::number(static_cast<double>(pos.y()), 'f', 3));
    addRoute->set_Zcurpos(QString::number(static_cast<double>(cur_z), 'f', 3));
    addRoute->set_Rcurpos(QString::number(static_cast<double>(cur_r), 'f', 3));

    // 删除之前的圆圈（如果有）
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (item->type() == QGraphicsEllipseItem::Type) {
            scene->removeItem(item);
            delete item;
        }
    }

    // 计算视图的缩放因子
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> c82df02 (界面)
    qreal scaleFactor = ui->graphicsView->transform().m11(); // 获取水平缩放因子

    // 在新位置绘制红色小圆圈
    qreal scaledX = pos.x() * scaleFactor;
    qreal scaledY = pos.y() * scaleFactor;

    // 创建新的圆圈，调整大小以考虑缩放
    QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(scaledX - 5, scaledY - 5, 10, 10); // 半径为 5 的小圆圈
    circle->setBrush(QBrush(Qt::red));  // 红色
    scene->addItem(circle);
=======
      qreal scaleFactor = ui->graphicsView->transform().m11(); // 获取水平缩放因子

      // 在新位置绘制红色小圆圈
      qreal scaledX = pos.x() * scaleFactor;
      qreal scaledY = pos.y() * scaleFactor;

      // 创建新的圆圈，调整大小以考虑缩放
      QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(scaledX - 5, scaledY - 5, 10, 10); // 半径为 5 的小圆圈
      circle->setBrush(QBrush(Qt::red));  // 红色
      scene->addItem(circle);
>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da

}



void MainWindow::updateAddRoute(int arc,int edit,int curRow)
{
    qDebug()<<"updateAddRoute";
    db.transaction();

    if (addRoute->exec()) {



        if (curRow<=0){return;}
        QString x0=QString::number(model->data(model->index(curRow-1, 10), Qt::DisplayRole).toFloat(), 'f', 3);
        QString y0=QString::number(model->data(model->index(curRow-1, 11), Qt::DisplayRole).toFloat(), 'f', 3);
        QString z0=QString::number(model->data(model->index(curRow-1, 12), Qt::DisplayRole).toFloat(), 'f', 3);
        QString r0=QString::number(model->data(model->index(curRow-1, 13), Qt::DisplayRole).toFloat(), 'f', 3);
        QList<QString> curStartPos_list = {x0,y0,z0,r0};

        if(edit==0){


            // 插入新行
            if (!model->insertRow(curRow)) {
                qDebug() << "Failed to insert row at" << curRow;
                db.rollback();
                QMessageBox::critical(this, "Error", QString::fromLocal8Bit(" 插入新行失败 "));
                return;
            }

        }

        QList<QString> curTransPos_list = addRoute->getTransPos();
        QList<QString> curEndPos_list = addRoute->getEndPos();

        if ( curStartPos_list == curTransPos_list ||
             curStartPos_list == curEndPos_list   ||
             curTransPos_list == curEndPos_list )
        {
            QMessageBox::information(this, " warning ", QString::fromLocal8Bit(" 有至少两个点重合，请检查 "));
            return;
        }



        // 根据 arc 标志判断，设置类型及转换位置信息
        if (arc == 1) {


            model->setData(model->index(curRow, 0), curRow);
            model->setData(model->index(curRow, 1), "arc");
            model->setData(model->index(curRow, 2), curStartPos_list.at(0));
            model->setData(model->index(curRow, 3), curStartPos_list.at(1));
            model->setData(model->index(curRow, 4), curStartPos_list.at(2));
            model->setData(model->index(curRow, 5), curStartPos_list.at(3));

            model->setData(model->index(curRow, 6), curTransPos_list.at(0));
            model->setData(model->index(curRow, 7), curTransPos_list.at(1));
            model->setData(model->index(curRow, 8), curTransPos_list.at(2));
            model->setData(model->index(curRow, 9), curTransPos_list.at(3));

            model->setData(model->index(curRow, 10), curEndPos_list.at(0));
            model->setData(model->index(curRow, 11), curEndPos_list.at(1));
            model->setData(model->index(curRow, 12), curEndPos_list.at(2));
            model->setData(model->index(curRow, 13), curEndPos_list.at(3));
            qDebug()<<"***arc:*****start="<< curStartPos_list <<"trans"<<curTransPos_list<<
                      " end"<<curEndPos_list;
        } else {

            model->setData(model->index(curRow, 0), curRow);
            model->setData(model->index(curRow, 1), "line");
            model->setData(model->index(curRow, 2), curStartPos_list.at(0));
            model->setData(model->index(curRow, 3), curStartPos_list.at(1));
            model->setData(model->index(curRow, 4), curStartPos_list.at(2));
            model->setData(model->index(curRow, 5), curStartPos_list.at(3));

            model->setData(model->index(curRow, 10), curEndPos_list.at(0));
            model->setData(model->index(curRow, 11), curEndPos_list.at(1));
            model->setData(model->index(curRow, 12), curEndPos_list.at(2));
            model->setData(model->index(curRow, 13), curEndPos_list.at(3));
            qDebug()<<"***lin:*****start="<< curStartPos_list <<
                      " end"<<curEndPos_list;
        }



        if (!model->submitAll()) {
            qDebug() << "提交数据失败:" << model->lastError().text();
            db.rollback();
            QMessageBox::critical(this, "Error", "提交数据失败: " + model->lastError().text());
            return;
        }
    } else {
        db.rollback();
        return;
    }


    if (!db.commit()) {
        qDebug() << "Failed to commit transaction:" << db.lastError().text();
        QMessageBox::critical(this, "Error", "事务提交失败:" + db.lastError().text());
        db.rollback();
    }


    updateSence();
}

void MainWindow::PbModbusConnectBtn(){

    scanDetectCtrl->setModbusTcpIP(ui->ip_lin->text());
    scanDetectCtrl->setModbusPort(ui->port_lin->text().toInt());

    scanDetectCtrl->on_connectBtn_clicked();



}

void MainWindow::pbAddSpline()
{   qDebug()<<"pbAddSpline";
    //addRoute->update_Ui(0,ui->xCurPos->text(),ui->yCurPos->text(),ui->rCurPos->text(),NULL,NULL,NULL);
    //updateAddRoute(0,0,0);

}

void MainWindow::pbAddElliptical()
{
    qDebug()<<"pbAddElliptical";
    //addRoute->update_Ui(1,ui->xCurPos->text(),ui->yCurPos->text(),ui->rCurPos->text(),NULL,NULL,NULL);
    //updateAddRoute(1,0,0);
}

void MainWindow::pbAddArcPos()
{
    if(!scanDetectCtrl->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;
    }
    int route_rowNum=model->rowCount();
    if (route_rowNum < 0) {
        QMessageBox::information(this," warning ",QString::fromLocal8Bit(" 请先选择要编辑的行 "));
        return;
    }
    addRoute->update_Ui(1,ui->xCurPos_lab->text(),ui->yCurPos_lab->text(),ui->zCurPos_lab->text(),ui->rCurPos_lab->text(),NULL,NULL,NULL,NULL);
    updateAddRoute(1,0,route_rowNum);

    ui->messText_lin->setText(QString::fromLocal8Bit(" 图元已添加   "));


}

void MainWindow::pbAddLinePos()
{
    if(!scanDetectCtrl->modbusState()){
        QMessageBox::warning(nullptr, "error",QString::fromLocal8Bit( " 通讯未连接   "));
        return;
    }
    int route_rowNum=model->rowCount();
    if (route_rowNum < 0) {
        QMessageBox::information(this," warning ",QString::fromLocal8Bit(" 请先选择要编辑的行 "));
        return;
    }
    addRoute->update_Ui(0,ui->xCurPos_lab->text(),ui->yCurPos_lab->text(),ui->zCurPos_lab->text(),ui->rCurPos_lab->text(),NULL,NULL,NULL,NULL);
    updateAddRoute(0,0,route_rowNum);
    ui->messText_lin->setText(QString::fromLocal8Bit(" 图元已添加   "));

}

void MainWindow::on_editPos_but_clicked()
{
    int cur_row = ui->tableView->currentIndex().row();
    QVariant value = model->data(model->index(cur_row, 1), Qt::DisplayRole);
    QString curName= value.toString();
    QString xTrans=QString::number(model->data(model->index(cur_row, 6), Qt::DisplayRole).toFloat(), 'f', 3);
    QString yTrans=QString::number(model->data(model->index(cur_row, 7), Qt::DisplayRole).toFloat(), 'f', 3);
    QString zTrans=QString::number(model->data(model->index(cur_row, 8), Qt::DisplayRole).toFloat(), 'f', 3);
    QString rTrans=QString::number(model->data(model->index(cur_row, 9), Qt::DisplayRole).toFloat(), 'f', 3);

    QString xEnd=QString::number(model->data(model->index(cur_row, 10), Qt::DisplayRole).toFloat(), 'f', 3);
    QString yEnd=QString::number(model->data(model->index(cur_row, 11), Qt::DisplayRole).toFloat(), 'f', 3);
    QString zEnd=QString::number(model->data(model->index(cur_row, 12), Qt::DisplayRole).toFloat(), 'f', 3);
    QString rEnd=QString::number(model->data(model->index(cur_row, 13), Qt::DisplayRole).toFloat(), 'f', 3);

     if(curName=="line")
    {
        addRoute->isOpen=true;
        addRoute->update_Ui(0,xEnd,yEnd,zEnd,rEnd,xTrans,yTrans,zTrans,rTrans);
        updateAddRoute(0,1,cur_row);
    }
    else if(curName=="arc")
    {
        addRoute->isOpen=true;
        addRoute->update_Ui(1,xEnd,yEnd,zEnd,rEnd,xTrans,yTrans,zTrans,rTrans);
        updateAddRoute(1,1,cur_row);
    }

}


void MainWindow::on_delete_but_clicked()
{

    db.transaction(); // 开始一个事务
    QItemSelection selection(ui->tableView->selectionModel()->selection());
    QList<int> rows;
    foreach(const QModelIndex & index, selection.indexes())
    {
        rows.append( index.row() );
    }


    int ok = QMessageBox::warning(this,QString::fromLocal8Bit("删除选中的行!"),QString::fromLocal8Bit("你确定删除当前选取中的行吗?"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes)
    {
        int prev = -1;
        for( int i = rows.count() - 1; i >= 0; i -= 1 )
        {
            int current = rows[i];
            if( current != prev )
            {
                QSqlQuery query(db);
                // 1. 更新插入位置之后的行的 sort_order 值
                query.prepare("UPDATE default_testdb SET sort_order = sort_order - 1 WHERE sort_order >= :insertOrder");
                query.bindValue(":insertOrder", current);
                if (!query.exec()) {
                    qDebug() << "Failed to update sort_order: " << query.lastError();
                    return;
                }
                model->removeRows( current, 1 );
                prev = current;
            }
        }

        model->submitAll(); //提交，在数据库中删除该行

    }
    else
    {
        model->revertAll(); //如果不删除，则撤销
    }

    updateSence();
    db.commit(); // 提交
}


void MainWindow::pbWriteInPLC()
{


    if(!scanDetectCtrl->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;}

    if(!scanDetectCtrl->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;}

    if(ui->cBworkpiece->currentText()==""){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit("请选择工件"));
        return;
    }

    createOrSwitchTable(ui->cBworkpiece->currentText(),false);

    int row_count =model->rowCount();

    float x0,y0,r0,z0,x1,y1,r1,z1,x2,y2,z2,r2;
    QString name;
    QVector<QVector<float>> point;
    QVector<modelDate> modelDates;

    for(int i = 0; i < row_count; ++i)
    {
        name=model->data(model->index(i, 1), Qt::DisplayRole).toString();

        if(name=="arc"){
            //x0=model->data(model->index(i, 2), Qt::DisplayRole).toFloat();
            //y0=model->data(model->index(i, 3), Qt::DisplayRole).toFloat();
            //z0=model->data(model->index(i, 4), Qt::DisplayRole).toFloat();
            //r0=model->data(model->index(i, 5), Qt::DisplayRole).toFloat();

            x1=model->data(model->index(i, 6), Qt::DisplayRole).toFloat();
            y1=model->data(model->index(i, 7), Qt::DisplayRole).toFloat();
            z1=model->data(model->index(i, 8), Qt::DisplayRole).toFloat();
            r1=model->data(model->index(i, 9), Qt::DisplayRole).toFloat();

            x2=model->data(model->index(i, 10), Qt::DisplayRole).toFloat();
            y2=model->data(model->index(i, 11), Qt::DisplayRole).toFloat();
            z2=model->data(model->index(i, 12), Qt::DisplayRole).toFloat();
            r2=model->data(model->index(i, 13), Qt::DisplayRole).toFloat();

            modelDate segment;
            segment.type = "arc";
            segment.points.push_back({x2, y2, r2});
            segment.points.push_back({x1, y1, r1});


            modelDates.push_back(segment);

        }else if (name=="line") {
            //x0=model->data(model->index(i, 2), Qt::DisplayRole).toFloat();
            //y0=model->data(model->index(i, 3), Qt::DisplayRole).toFloat();
            //z0=model->data(model->index(i, 4), Qt::DisplayRole).toFloat();
            //r0=model->data(model->index(i, 5), Qt::DisplayRole).toFloat();

            x2=model->data(model->index(i, 10), Qt::DisplayRole).toFloat();
            y2=model->data(model->index(i, 11), Qt::DisplayRole).toFloat();
            z2=model->data(model->index(i, 12), Qt::DisplayRole).toFloat();
            r2=model->data(model->index(i, 13), Qt::DisplayRole).toFloat();

            modelDate segment;
            segment.type = "line";
            segment.points.push_back({x2, y2, r2});
            modelDates.push_back(segment);
        }


    }



    scanDetectCtrl->writeRegisterGroup(3000,modelDates,1);


}

void MainWindow::pbStartScanBtn(){

    qDebug()<<"pbStartScanBtn";
    ui->messText_lin->setText(QString::fromLocal8Bit(" 开始启动   "));
    scanDetectCtrl->workPiece=ui->cBworkpiece->currentText();
    scanDetectCtrl->selectProcessType(ui->processType_cb->currentIndex());
    scanDetectCtrl->on_startScanBtn_clicked();
    ui->messText_lin->setText(QString::fromLocal8Bit(" 已启动   "));


}

void MainWindow::updateSence()//on_testRout_but_clicked()
{

    scene->clear();
    rownum_itme_lst.clear();
    model->select();
    int row_count =model->rowCount();
    float x0,y0,z0,r0,x1,y1,z1,r1,x2,y2,z2,r2;
    QString type;
    QList<float>list_x0,list_y0,list_r0,list_x1,list_y1,list_r1;
    QList<QString>list_name;
    QPointF start_pos,end_pos,trans_pos ;
    float factor=ui->graphicsView->transform().m11();;

    for (auto it = GlobeUniquePoints.constBegin(); it != GlobeUniquePoints.constEnd(); ++it){

        QStringList parts = it->split("_"); // 正确写法！
        if (parts.size() < 2) {
            db.rollback();
            return;
        }
        double posx = parts[0].toDouble();
        double posy = parts[1].toDouble();

        // 在新位置绘制红色小圆圈
        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem((posx - 20)*factor, (posy - 20)*factor, 40*factor, 40*factor); // 半径为20
        circle->setBrush(QBrush(Qt::red));  // 红色
        //circle->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        scene->addItem(circle);
        // 显示坐标文字
        QString coordText = QString("(%1, %2)").arg(posx*factor).arg(posy*factor);
        QGraphicsTextItem* textItem = new QGraphicsTextItem(coordText);
        textItem->setDefaultTextColor(Qt::black); // 设置字体颜色
        textItem->setFont(QFont("Arial", 10));    // 设置字体大小
        //textItem->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        // 放在圆的旁边（你可以微调这个偏移）
        textItem->setPos(posx + 25, posy - 10);  // 右边偏移一些位置
        scene->addItem(textItem);

        if(GlobeUniquePoints.length()>3){
            QString coordText = QString::fromLocal8Bit("轨迹首非相连，请检查红点处有无衔接好（红点数量不能大于2）");
            QGraphicsTextItem* textItem = new QGraphicsTextItem(coordText);
            textItem->setDefaultTextColor(Qt::black); // 设置字体颜色
            textItem->setFont(QFont("Arial", 25));    // 设置字体大小
            // 放在圆的旁边（你可以微调这个偏移）
            textItem->setPos(0,0);  // 右边偏移一些位置
            scene->addItem(textItem);

        }
    }


    for(int i = 0; i < row_count; ++i)
    {
        type=model->data(model->index(i, 1), Qt::DisplayRole).toString();
        x0=model->data(model->index(i, 2), Qt::DisplayRole).toFloat();
        y0=model->data(model->index(i, 3), Qt::DisplayRole).toFloat();
        z0=model->data(model->index(i, 4), Qt::DisplayRole).toFloat();
        r0=model->data(model->index(i, 5), Qt::DisplayRole).toFloat();

        x1=model->data(model->index(i, 6), Qt::DisplayRole).toFloat();
        y1=model->data(model->index(i, 7), Qt::DisplayRole).toFloat();
        z1=model->data(model->index(i, 8), Qt::DisplayRole).toFloat();
        r1=model->data(model->index(i, 9), Qt::DisplayRole).toFloat();

        x2=model->data(model->index(i, 10), Qt::DisplayRole).toFloat();
        y2=model->data(model->index(i, 11), Qt::DisplayRole).toFloat();
        z2=model->data(model->index(i, 12), Qt::DisplayRole).toFloat();
        r2=model->data(model->index(i, 13), Qt::DisplayRole).toFloat();

        int row= model->data(model->index(i, 16), Qt::DisplayRole).toInt();

        start_pos= QPointF( x0*factor,y0*factor );
        trans_pos= QPointF( x1*factor,y1*factor );
        end_pos = QPointF( x2*factor,y2*factor );

        if(type=="line"){

            line_item* line = new line_item(start_pos,end_pos,i,scene);
            scene->addItem(line);
            rownum_itme_lst.append(row);
        }else if(type=="arc"){


            arc_item* arc = new arc_item(start_pos,trans_pos,end_pos,i,scene);
            scene->addItem(arc);
            rownum_itme_lst.append(row);

        }
    }

    ui->graphicsView->setCacheMode(QGraphicsView::CacheNone);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    scene->update();
    ui->graphicsView->scene()->update();         // 强制场景重绘
    ui->graphicsView->viewport()->update();
    ui->graphicsView->show();

}

void MainWindow::tableSelectionChanged()
{

    QItemSelectionModel *select = ui->tableView->selectionModel();
    QModelIndex index =select->currentIndex();
    int selectedRow = index.row();
    QString name=model->data(model->index(selectedRow, 1), Qt::DisplayRole).toString();
    if(scene->items().count() >0)
    {
        foreach (QGraphicsItem *item, scene->items()) {
            item->setSelected(false);
        }
        // 获取场景中的所有项
        foreach (QGraphicsItem *item, scene->items()) {
            if (line_item *item_a = dynamic_cast<line_item *>(item)) {
                int sortNum=item_a->_sortNum;
                if(sortNum==selectedRow){
                    item->setSelected(true);
                    //qDebug() << "*******0";
                }
                //qDebug() << "This is a line_itme"<<item_a->_sortNum<<"selectedRow="<<selectedRow;
            } else if (arc_item *item_b = dynamic_cast<arc_item *>(item)) {
                int sortNum=item_b->_sortNum;
                if(sortNum==selectedRow){
                    item->setSelected(true);
                    //qDebug() << "*******0";
                }
                //qDebug() << "This is a arc_item";
            }
        }
    }else{
        return;
    }
    scene->update();

    m_lastClickedRow = selectedRow;
    m_isSelected =  ui->tableView->selectionModel()->isSelected(index);

}


void MainWindow::graphicsSelectionChanged()
{

    if(scene->items().count() >0)
    {
        /*foreach (QGraphicsItem *item, scene->items()) {
                    item->setSelected(false);
                }*/
        // 获取场景中的所有项
        foreach (QGraphicsItem *item, scene->items()) {
            if (line_item *item_a = dynamic_cast<line_item *>(item)) {
                int sortNum=item_a->_sortNum;
                if(item->isSelected()==true){
                    ui->tableView->selectRow(sortNum);
                    //qDebug() << "*******0";
                }
                //qDebug() << "This is a line_itme"<<item_a->_sortNum<<"selectedRow="<<selectedRow;
            } else if (arc_item *item_b = dynamic_cast<arc_item *>(item)) {
                int sortNum=item_b->_sortNum;
                if(item->isSelected()==true){
                    ui->tableView->selectRow(sortNum);
                    //qDebug() << "*******0";
                }
                //qDebug() << "This is a arc_item";
            }
        }
    }
    else{
        return;
    }
    scene->update();

}

void MainWindow::pBbrazing(){

    db.transaction();
    scene->clear();
    model->removeRows(0, model->rowCount());
    model->submitAll();
    model->select();

    bool ok = false;
    // 弹出“横向/纵向”选择框
    QString dir = QInputDialog::getItem(
                this,
                QString::fromLocal8Bit("选择扫描方向"),
                QString::fromLocal8Bit("横向扫还是纵向扫？"),
                QStringList{ QString::fromLocal8Bit("横向"), QString::fromLocal8Bit("纵向") },
                0, false, &ok
                );
    if (!ok) return;  // 用户取消

    QString subDir;
    if (dir == QString::fromLocal8Bit("纵向")) {
        subDir = QInputDialog::getItem(
                    this,
                    QString::fromLocal8Bit("选择纵向方向"),
                    QString::fromLocal8Bit("请选择向上还是向下？"),
                    QStringList{ QString::fromLocal8Bit("向上"), QString::fromLocal8Bit("向下") },
                    0, false, &ok
                    );  // :contentReference[oaicite:1]{index=1}
    } else { // 横向
        subDir = QInputDialog::getItem(
                    this,
                    QString::fromLocal8Bit("选择横向方向"),
                    QString::fromLocal8Bit("请选择向左还是向右？"),
                    QStringList{ QString::fromLocal8Bit("向左"), QString::fromLocal8Bit("向右") },
                    0, false, &ok
                    );  // :contentReference[oaicite:2]{index=2}
    }
    if (!ok) return;

    // 3. 输入“扫描长度”和“步进值”
    double length = QInputDialog::getDouble(
                this, QString::fromLocal8Bit("输入参数"), QString::fromLocal8Bit("扫描长度（mm）："),
                100.0, 0.0, 1e6, 2, &ok
                );
    if (!ok) return;

    double step = QInputDialog::getDouble(
                this, QString::fromLocal8Bit("输入参数"), QString::fromLocal8Bit("步进值（mm）："),
                1.0, 0.0, length, 2, &ok
                );

    double lengthStep = QInputDialog::getDouble(
                this, QString::fromLocal8Bit("输入参数"), QString::fromLocal8Bit("步进长度（mm）："),
                100, 0.0, length, 2, &ok
                );

    if (!ok) return;

    // 4. 根据参数生成之字形线段列表
    struct Seg { QPointF p1, p2; };
    QVector<Seg> segs;
    double offset = 0.0;
    bool isHorizontal = (dir == QString::fromLocal8Bit("横向"));
    bool isPositiveDirection = (subDir == QString::fromLocal8Bit("向右") || subDir == QString::fromLocal8Bit("向下"));

    while (offset <= lengthStep) {
        QPointF a, b, a2, b2;

        if (isHorizontal) {
            // 水平段
            double y = offset;
            if (isPositiveDirection) {
                a = QPointF(0, y);
                b = QPointF(length, y);
            } else {
                a = QPointF(length, y);
                b = QPointF(0, y);
            }

            int quotient = static_cast<int>(offset / step);
            if (quotient % 2 == 0) {
                segs.append({a, b});
                a2 = b;
            } else {
                segs.append({b, a});
                a2 = a;
            }

            // 垂直段
            offset += step;
            if (offset > lengthStep) break;

            b2 = QPointF(a2.x(), offset);
            segs.append({a2, b2});
        } else {
            // 垂直段
            double x = offset;
            if (isPositiveDirection) {
                a = QPointF(x, 0);
                b = QPointF(x, length);
            } else {
                a = QPointF(x, length);
                b = QPointF(x, 0);
            }

            int quotient = static_cast<int>(offset / step);
            if (quotient%2 == 0.0) {
                segs.append({a, b});
                a2 = b;
            } else {
                segs.append({b, a});
                a2 = a;
            }

            // 水平段
            offset += step;
            if (offset > lengthStep) break;
            b2 = QPointF(offset, a2.y());
            segs.append({a2, b2});
        }
    }

    // 5. 将生成的坐标写入模型，并绘制到场景中
    for (int i = 0; i < segs.size(); ++i) {
        model->insertRow(i);
        model->setData(model->index(i, 0), i);
        model->setData(model->index(i, 1), "line");
        model->setData(model->index(i, 2), segs[i].p1.x());
        model->setData(model->index(i, 3), segs[i].p1.y());
        model->setData(model->index(i, 10), segs[i].p2.x());
        model->setData(model->index(i, 11), segs[i].p2.y());

        auto *item = new line_item(segs[i].p1, segs[i].p2, i, scene);
        scene->addItem(item);
    }

    model->submitAll();
    model->select();



    if (!db.commit()) {
        qDebug() << "事务提交失败:" << db.lastError().text();
        QMessageBox::critical(this, "错误", "事务提交失败:" + db.lastError().text());
        db.rollback();
    } else {
        qDebug() << "排序及更新完成，事务提交成功！";
    }
}

void MainWindow::pbDXFimportBut()
{



    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open DXF File"),
                settings->value("lastDir", QDir::homePath()).toString(),
                tr("DXF Files (*.dxf)"));

    if (!fileName.isEmpty()) {
        settings->setValue("lastDir", QFileInfo(fileName).absolutePath());
    }

    if (fileName.isEmpty()) {

        return;  // 没有选择文件时直接返回
    }
    selectWorkpiece();

    db.transaction();
    scene->clear();
    model->removeRows(0, model->rowCount());
    model->submitAll();
    model->select();

    int  AantalDesimalePlekke=2;
    DxfHelper dxfHelper;
    if(dxfHelper.generateDxf(fileName.toStdString().c_str())) {
        QVector<QVector<QPointF> >dcfData=dxfHelper.dxfPaths_LA;//line_acr_lines  acr01
        if(dcfData.count()<=0 ){return;}
        qDebug()<<"***paths.count()="<<dcfData.count();

        double _translationX=dcfData.at(0).at(0).x();
        double _translationY=dcfData.at(0).at(0).y();

        //double _translationX=0;
        //double _translationY=0;

        for (int i=0; i<dcfData.count();i++) {
            model->insertRow(i); //添加一行
            QVector<QPointF>points=dcfData.at(i);
            if(points.count()==2)
            {
                double l_startX,l_startY,l_endX,l_endY;

                l_startX= points.at(0).x()-_translationX;
                l_startY=points.at(0).y()-_translationY;
                l_endX=points.at(1).x()-_translationX;
                l_endY=points.at(1).y()-_translationY;

                l_startX = std::round(l_startX * 100.0) / 100.0;  // std::round(v) 四舍五入到最近整数 :contentReference[oaicite:0]{index=0}
                l_startY = std::round(l_startY * 100.0) / 100.0;
                l_endX   = std::round(l_endX   * 100.0) / 100.0;
                l_endY   = std::round(l_endY   * 100.0) / 100.0;

                QPointF start= QPointF(l_startX,l_startY);
                QPointF end= QPointF(l_endX,l_endY);
                model->setData (model->index(i,0),i);
                model->setData (model->index(i,1),"line");
                model->setData (model->index(i,2),start.x());
                model->setData (model->index(i,3),start.y());
                //model->setData (model->index(i,5),end.x());
                //model->setData (model->index(i,6),end.y());
                model->setData (model->index(i,10),end.x());
                model->setData (model->index(i,11),end.y());

                line_item *itme =new line_item(start,end,i,scene);
                scene->addItem(itme);

                qDebug()<<"***lin:*****start_x="<<start.x()<<"   start_y"<<start.y()<<"    end_x="<<end.x()<<"end_y:"<<end.y()<<" i "<<i;

            }
            else if(points.count()==3){

                double c_start_x,c_start_y,c_end_x,c_end_y,c_trans_x,c_trans_y;
                c_start_x= points.at(0).x()-_translationX;
                c_start_y=points.at(0).y()-_translationY;
                c_end_x=points.at(1).x()-_translationX;
                c_end_y=points.at(1).y()-_translationY;
                c_trans_x=points.at(2).x()-_translationX;
                c_trans_y=points.at(2).y()-_translationY;

                c_start_x = std::round(c_start_x * 100.0) / 100.0;  // std::round(v) 四舍五入到最近整数 :contentReference[oaicite:0]{index=0}
                c_start_y = std::round(c_start_y * 100.0) / 100.0;
                c_end_x   = std::round(c_end_x   * 100.0) / 100.0;
                c_end_y   = std::round(c_end_y   * 100.0) / 100.0;
                c_trans_x   = std::round(c_trans_x   * 100.0) / 100.0;
                c_trans_y   = std::round(c_trans_y   * 100.0) / 100.0;

                QPointF start_arc= QPointF(c_start_x,c_start_y);
                QPointF trans_arc= QPointF(c_trans_x,c_trans_y);
                QPointF end_arc= QPointF(c_end_x,c_end_y);
                model->setData (model->index(i,0),i);
                model->setData (model->index(i,1),"arc");
                model->setData (model->index(i,2),start_arc.x());
                model->setData (model->index(i,3),start_arc.y());


                model->setData (model->index(i,6),trans_arc.x());
                model->setData (model->index(i,7),trans_arc.y());

                model->setData (model->index(i,10),end_arc.x());
                model->setData (model->index(i,11),end_arc.y());

                qDebug()<<"***arc:*****start_arc="<<start_arc<<"trans_arc="<<trans_arc<<"end_arc="<<end_arc<<" i "<<i;
                arc_item *itme =new arc_item(start_arc,trans_arc,end_arc,i,scene);
                scene->addItem(itme);
            }

        }


    }
    else{
        qDebug()<<"***dxf file do not open*****";
        return;
    }
    model->submitAll();
    model->select();

    if (!db.commit()) {
        qDebug() << "Failed to commit transaction:" << db.lastError().text();
        QMessageBox::critical(this, "Error", "事务提交失败:" + db.lastError().text());
        db.rollback();
    }


    sortModelLine();
    CalculatingAngles();
}

void MainWindow::sortModelLine()
{
    qDebug() << "开始排序模型图形链...";
    db.transaction();

    const double eps = 0.1;
    int  AantalDesimalePlekke=2;
    int rowCount = model->rowCount();
    qDebug() << "模型行数:" << rowCount;

    // 保存所有点（“x_y”格式）和单独保存起点与终点列表
    QList<QString> startKeys;
    QList<QString> endKeys;
    for (int i = 0; i < rowCount; ++i) {
        QSqlRecord rec = model->record(i);

        // 获取并转换起点和终点坐标
        double startX = rec.value(2).toDouble();
        double startY = rec.value(3).toDouble();
        double endX   = rec.value(10).toDouble();
        double endY   = rec.value(11).toDouble();

        // 格式化为保留两位小数的字符串
        QString startXStr = QString::number(startX, 'f', AantalDesimalePlekke);
        QString startYStr = QString::number(startY, 'f', AantalDesimalePlekke);
        QString endXStr   = QString::number(endX, 'f', AantalDesimalePlekke);
        QString endYStr   = QString::number(endY, 'f', AantalDesimalePlekke);

        // 构造键
        QString startKey = startXStr + "_" + startYStr;
        QString endKey   = endXStr + "_" + endYStr;

        startKeys.append(startKey);
        endKeys.append(endKey);

        qDebug() << "第" << i << "行:" << "startKey:" << startKey << " endKey:" << endKey;
    }

    // 统计所有点的频次
    QMap<QString, int> pointFreq;
    for (const QString &pt : startKeys)
        pointFreq[pt] += 1;
    for (const QString &pt : endKeys)
        pointFreq[pt] += 1;

    qDebug() << "所有点频次统计:";
    for (auto it = pointFreq.constBegin(); it != pointFreq.constEnd(); ++it) {
        qDebug() << "点:" << it.key() << "频次:" << it.value();
    }

    // 提取出现频次为1的点（候选首尾）
    QList<QString> uniquePoints;
    for (auto it = pointFreq.constBegin(); it != pointFreq.constEnd(); ++it) {
        if (it.value() == 1){
            uniquePoints.append(it.key());
            GlobeUniquePoints=uniquePoints;
        }
        qDebug() << "候选唯一点:" << uniquePoints;

    }

    // 检查非唯一点是否均出现两次
    for (auto it = pointFreq.constBegin(); it != pointFreq.constEnd(); ++it) {
        if (it.value() != 1 && it.value() != 2) {
            QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit("数据有误：非首尾相连！"));
            db.rollback();
            return;
        }
    }


    QString candidatePoint1 ;
    QString candidatePoint2;
    if(uniquePoints.size()==0){
        QSqlRecord rec = model->record(0);
        double sx = rec.value(2).toDouble();
        double sy = rec.value(3).toDouble();
        QString sKey = QString::number(sx, 'f', AantalDesimalePlekke) + "_" + QString::number(sy, 'f', AantalDesimalePlekke);
        double ex = rec.value(10).toDouble();
        double ey = rec.value(11).toDouble();
        QString eKey = QString::number(ex, 'f', AantalDesimalePlekke) + "_" + QString::number(ey, 'f', AantalDesimalePlekke);
        candidatePoint1 = sKey;
        candidatePoint2 = sKey;
        GlobeUniquePoints={sKey};
    }else {

        candidatePoint1 = uniquePoints.at(0);
        candidatePoint2 = uniquePoints.at(1);

    }



    qDebug() << "候选点1:" << candidatePoint1 << "候选点2:" << candidatePoint2;

    // 询问用户选择哪个点作为轨迹起点
    QString chosenStartKey;
    QMessageBox::StandardButton reply = QMessageBox::question(
                nullptr,
                QString::fromLocal8Bit("起点选择"),
                QString::fromLocal8Bit("发现两个候选起点：%1 和 %2。\n是否以坐标 %1 作为轨迹起点？否则选择%2作轨迹起点")
                .arg(candidatePoint1, candidatePoint2),
                QMessageBox::Yes | QMessageBox::No
                );

    if (reply == QMessageBox::Yes) {
        chosenStartKey = candidatePoint1;
    } else {
        chosenStartKey = candidatePoint2;
    }
    qDebug() << "用户选择的起点:" << chosenStartKey;

    // 解析 chosenStartKey 得到起始坐标（这里仅用于调试，后续链条匹配直接使用字符串比较）
    QStringList parts = chosenStartKey.split("_");
    if (parts.size() < 2) {
        db.rollback();
        return;
    }
    double chosenStartX = parts[0].toDouble();
    double chosenStartY = parts[1].toDouble();
    QPointF chosenStart(chosenStartX, chosenStartY);
    qDebug() << "解析起点:" << chosenStart;

    // 构造链式排序：保存新顺序（存储原模型行号）
    QList<int> newOrder;
    QSet<int> usedRows;

    // 首先在模型中查找包含 chosenStartKey 的记录
    int startRow = -1;
    for (int i = 0; i < rowCount; ++i) {
        if (usedRows.contains(i))
            continue;
        QSqlRecord rec = model->record(i);
        double sx = rec.value(2).toDouble();
        double sy = rec.value(3).toDouble();
        QString sKey = QString::number(sx, 'f', AantalDesimalePlekke) + "_" + QString::number(sy, 'f', AantalDesimalePlekke);
        double ex = rec.value(10).toDouble();
        double ey = rec.value(11).toDouble();
        QString eKey = QString::number(ex, 'f', AantalDesimalePlekke) + "_" + QString::number(ey, 'f', AantalDesimalePlekke);

        if (sKey == chosenStartKey || eKey == chosenStartKey) {
            // 如果起点在记录中出现在终点，则交换，使之成为起点
            if (eKey == chosenStartKey) {
                qDebug() << QString::fromLocal8Bit("记录") << i <<QString::fromLocal8Bit(
                                "中，候选起点在终点，进行交换。");
                double tmpX = sx, tmpY = sy;
                sx = ex;
                sy = ey;
                ex = tmpX;
                ey = tmpY;
                sKey = QString::number(sx, 'f', AantalDesimalePlekke) + "_" + QString::number(sy, 'f', AantalDesimalePlekke);
                eKey = QString::number(ex, 'f', AantalDesimalePlekke) + "_" + QString::number(ey, 'f', AantalDesimalePlekke);

                // 更新模型中该记录的起点和终点
                model->setData(model->index(i, 2), sx);
                model->setData(model->index(i, 3), sy);
                model->setData(model->index(i, 10), ex);
                model->setData(model->index(i, 11), ey);
                model->submitAll();
                model->select();
            }
            startRow = i;
            newOrder.append(i);
            usedRows.insert(i);
            // 更新当前链头为该记录的终点
            chosenStartX = ex;
            chosenStartY = ey;
            qDebug()<<"sx"<<sx<<"  "<<"sy"<<sy<<"  "<<"ex"<<ex<<"  "<<"ey"<<ey;
            qDebug() << QString::fromLocal8Bit("找到起始记录:" )<< i <<QString::fromLocal8Bit( ", 新链头:")
                     << QString::number(chosenStartX, 'f', AantalDesimalePlekke)
                     << "_" << QString::number(chosenStartY, 'f', AantalDesimalePlekke);
            break;
        }
    }
    if (startRow == -1) {
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit("未找到包含用户选择起点的记录。"));
        db.rollback();
        return;
    }


    // 链式排序：依次查找未使用记录中，与当前链头匹配的记录
    QString currentChainKey = QString::number(chosenStartX, 'f', AantalDesimalePlekke) + "_" + QString::number(chosenStartY, 'f', AantalDesimalePlekke);
    qDebug() << "初始链头:" << currentChainKey;
    while (newOrder.size() < rowCount) {
        bool found = false;
        for (int i = 0; i < rowCount; ++i) {
            if (usedRows.contains(i))
                continue;
            QSqlRecord rec = model->record(i);
            double sx = rec.value(2).toDouble();
            double sy = rec.value(3).toDouble();
            double ex = rec.value(10).toDouble();
            double ey = rec.value(11).toDouble();
            QString sKey = QString::number(sx, 'f', AantalDesimalePlekke) + "_" + QString::number(sy, 'f', AantalDesimalePlekke);
            QString eKey = QString::number(ex, 'f', AantalDesimalePlekke) + "_" + QString::number(ey, 'f', AantalDesimalePlekke);

            if (sKey == currentChainKey || eKey == currentChainKey) {
                // 如果匹配记录中当前链头在终点，则交换使其出现在起点
                if (eKey == currentChainKey) {
                    qDebug() << "记录" << i << "中链头在终点，进行交换。";
                    double tmpX = sx, tmpY = sy;
                    sx = ex;
                    sy = ey;
                    ex = tmpX;
                    ey = tmpY;
                    sKey = QString::number(sx, 'f', AantalDesimalePlekke) + "_" + QString::number(sy, 'f', AantalDesimalePlekke);
                    eKey = QString::number(ex, 'f', AantalDesimalePlekke) + "_" + QString::number(ey, 'f', AantalDesimalePlekke);

                    // 更新模型中该记录的起点和终点
                    model->setData(model->index(i, 2), sx);
                    model->setData(model->index(i, 3), sy);
                    model->setData(model->index(i, 10), ex);
                    model->setData(model->index(i, 11), ey);
                    model->submitAll();
                    model->select();
                }
                newOrder.append(i);
                usedRows.insert(i);
                currentChainKey = eKey;
                qDebug() << "添加记录" << i << ", 更新链头为:" << currentChainKey;
                found = true;
                break;
            }
        }
        if (!found) {
            qDebug() << "链条构造中断，当前链头:" << currentChainKey;
            break;
        }
    }


    qDebug() << "最终链条记录数:" << newOrder.size();
    if (newOrder.size() != rowCount) {
        QMessageBox::warning(nullptr, "错误", QString::fromLocal8Bit("图形链条不完整，数据可能非首尾相连。"));
        db.rollback();
        return;
    }

    // 将排序后的记录存入临时变量，并更新记录中的 id（假设 id 在第0列）
    QList<QSqlRecord> sortedRecords;
    for (int newId = 0; newId < newOrder.size(); ++newId) {
        int rowIndex = newOrder[newId];
        QSqlRecord rec = model->record(rowIndex);
        rec.setValue(0, newId);
        sortedRecords.append(rec);
        qDebug() << "新顺序: 新 id:" << newId << " 原行:" << rowIndex;
    }


    // 将临时变量中的记录写回原模型
    for (int i = 0; i < sortedRecords.size(); ++i) {
        QSqlRecord rec = sortedRecords.at(i);
        model->setRecord(i, rec);
    }

    QSqlRecord rec = sortedRecords[0];
    qDebug()<<"rec.value(2).toDouble()"<<rec.value(2).toDouble()
           <<"  "<<"rec.value(3).toDouble()"<<rec.value(3).toDouble()
          <<"  "<<"rec.value(10).toDouble()"<<rec.value(10).toDouble()<<"  "
         <<"rec.value(11).toDouble()"<<rec.value(11).toDouble();
    model->submitAll();
    model->select();



    if (!db.commit()) {
        qDebug() << "事务提交失败:" << db.lastError().text();
        QMessageBox::critical(this, "错误", "事务提交失败:" + db.lastError().text());
        db.rollback();
    } else {
        qDebug() << "排序及更新完成，事务提交成功！";
    }

    QStringList quePoints = GlobeUniquePoints;          // QList<QString> → QStringList
    settings->setValue("startPoint", quePoints);
    updateSence();
}




void MainWindow::on_setTrajec_start_clicked()
{
    // 开始数据库事务
    db.transaction();

    // 获取用户输入的数据
    bool ok;
    double _x0 = ui->traject_x0->text().toDouble(&ok);
    double _y0 = ui->traject_y0->text().toDouble(&ok);
    double _z0 = ui->traject_z0->text().toDouble(&ok);
    double _r0 = ui->traject_r0->text().toDouble(&ok);

    // 获取第一行的终点数据
    double x2 = model->data(model->index(0, 2), Qt::DisplayRole).toDouble();
    double y2 = model->data(model->index(0, 3), Qt::DisplayRole).toDouble();
    double z2 = model->data(model->index(0, 4), Qt::DisplayRole).toDouble();
    double r2 = model->data(model->index(0, 5), Qt::DisplayRole).toDouble();

    model->insertRow(model->rowCount());
    // 将现有记录的 id 值加 1，并将记录向下移动一行
    for (int i = model->rowCount() - 1; i >= 0; --i) {
        QSqlRecord record = model->record(i);
        int currentId = record.value("id").toInt();
        record.setValue("id", currentId + 1);
        model->setRecord(i + 1, record);
    }
    // 在第一行插入新行


    // 设置新插入行的数据
    model->setData(model->index(0, 1), "line");
    model->setData(model->index(0, 2), _x0);
    model->setData(model->index(0, 3), _y0);
    model->setData(model->index(0, 4), _z0);
    model->setData(model->index(0, 5), _r0);
    model->setData(model->index(0, 10), x2);
    model->setData(model->index(0, 11), y2);
    model->setData(model->index(0, 12), z2);
    model->setData(model->index(0, 13), r2);

    // 提交更改并更新视图
    model->submitAll();
    model->select();

    // 提交数据库事务
    db.commit();

    // 更新场景视图
    updateSence();
    ui->messText_lin->setText(QString::fromLocal8Bit(" 起点已添加   "));

}


QString MainWindow::generateGCode(/*const QVector<TrackSegment>& segments*/)
{

    bool ok;

    //double addV=10;
    //QString gCode = QString("N0 F%1 E%2 E%3\n").arg(ui->AxleVelocity_lin->text()).arg(addV).arg(-addV);
    //double inputR = ui->traject_r0->text().toDouble(&ok); // 角度
    QString name;
    QString gCode;
    double inputR =0;
    int row_count =model->rowCount();
    float x0,y0,z0,r0,x1,y1,z1,r1,x2,y2,z2,r2;
    int firstNum=10;
    if(row_count<0){return "";}
    for(int i = 0; i < row_count; ++i)
    {
        name=model->data(model->index(i, 1), Qt::DisplayRole).toString();
        x0=model->data(model->index(i, 2), Qt::DisplayRole).toFloat();
        y0=model->data(model->index(i, 3), Qt::DisplayRole).toFloat();
        z0=model->data(model->index(i, 4), Qt::DisplayRole).toFloat();
        r0=model->data(model->index(i, 5), Qt::DisplayRole).toFloat();

        x1=model->data(model->index(i, 6), Qt::DisplayRole).toFloat();
        y1=model->data(model->index(i, 7), Qt::DisplayRole).toFloat();
        z1=model->data(model->index(i, 8), Qt::DisplayRole).toFloat();
        r1=model->data(model->index(i, 9), Qt::DisplayRole).toFloat();

        x2=model->data(model->index(i, 10), Qt::DisplayRole).toFloat();
        y2=model->data(model->index(i, 11), Qt::DisplayRole).toFloat();
        z2=model->data(model->index(i, 12), Qt::DisplayRole).toFloat();
        r2=model->data(model->index(i, 13), Qt::DisplayRole).toFloat();


        if(name=="line"){



            gCode += QString("N%1 G01 X%2 Y%3 Z%4 A%5\n")
                    .arg(firstNum+10)
                    .arg(x0)
                    .arg(y0)
                    .arg(z0)
                    .arg(r2);

            gCode += QString("N%1 G01 X%2 Y%3 Z%4 A%5\n")
                    .arg(firstNum+10)
                    .arg(x2)
                    .arg(y2)
                    .arg(z2)
                    .arg(r2);

            qDebug()<<"line: "<<r2<<"   "<<i;

        }else{

            QPointF A, B, C;
            A= QPointF( x0,y0 );
            C = QPointF( x2,y2 );
            B= QPointF( x1,y1 );

            float area = (B.x() - A.x()) * (C.y() - A.y()) - (B.y() - A.y()) * (C.x() - A.x());
            if (fabs(area) < 1e-9) {
                //throw std::runtime_error("三点共线，无法构成圆弧");
                qDebug()<<"Three points are not collinear";
            }
            //计算中点和垂直方向向量
            QPointF M1((A.x() + B.x()) / 2, (A.y() + B.y()) / 2);
            QPointF M2((B.x() + C.x()) / 2, (B.y() + C.y()) / 2);

            QPointF d1(B.y() - A.y(), A.x() - B.x()); // AB 的垂直向量
            QPointF d2(C.y() - B.y(), B.x() - C.x()); // BC 的垂直向量

            // 求两条中垂线的交点
            float det = d1.x() * d2.y() - d1.y() * d2.x();
            if (fabs(det) < 1e-9) {
                //throw std::runtime_error("计算中垂线交点失败");
                qDebug()<<"Failed to calculate the intersection point of the perpendicular line in the middle";
            }

            float t = ((M2.x() - M1.x()) * d2.y() - (M2.y() - M1.y()) * d2.x()) / det;
            QPointF center(M1.x() + t * d1.x(), M1.y() + t * d1.y());

            // 计算半径
            //double radius = std::hypot(center.x() - A.x(), center.y() - A.y());

            // 判断旋转方向
            float crossProduct = (B.x() - A.x()) * (C.y() - B.y()) - (B.y() - A.y()) * (C.x() - B.x());
            QString direction = crossProduct > 0 ? "CCW" : "CW";

            float I = center.x() - A.x();
            float J = center.y() - A.y();


            if(direction=="CW"){
                gCode += QString("N%1 G02 X%2 Y%3 Z%4 A%5 I%6 J%7 \n")
                        .arg(firstNum)
                        .arg(C.x())
                        .arg(C.y())
                        .arg(z2)
                        .arg(r2)
                        .arg(I)
                        .arg(J);

            }
            else if(direction=="CCW"){
                gCode += QString("N%1 G03 X%2 Y%3 Z%4 A%5 I%6 J%7 \n")
                        .arg(firstNum)
                        .arg(C.x())
                        .arg(C.y())
                        .arg(z2)
                        .arg(r2)
                        .arg(I)
                        .arg(J);

            }

        }
        firstNum+=10;
    }
    gCode+=QString("N%1 G01 X0  Y0 Z0 A0\n").arg(firstNum);
    gCode += "M30";//程序结束
    return gCode;
}


void MainWindow::CalculatingAngles(){

    bool ok;
    db.transaction();

    QModelIndex index = model->index(0, 13);
    double inputR=model->data(model->index(0, 13), Qt::DisplayRole).toFloat();

    if (!index.isValid() || std::isnan(inputR)) {
        inputR = 0.0;  // 默认值
    }

    int row_count =model->rowCount();
    float x0,y0,z0,r0,x1,y1,z1,r1,x2,y2,z2,r2;
    QString name;

    if(row_count<0){return ;}

    for(int i = 0; i < row_count; ++i)
    {
        name=model->data(model->index(i, 1), Qt::DisplayRole).toString();
        x0=model->data(model->index(i, 2), Qt::DisplayRole).toFloat();
        y0=model->data(model->index(i, 3), Qt::DisplayRole).toFloat();
        z0=model->data(model->index(i, 4), Qt::DisplayRole).toFloat();
        r0=model->data(model->index(i, 5), Qt::DisplayRole).toFloat();

        x1=model->data(model->index(i, 6), Qt::DisplayRole).toFloat();
        y1=model->data(model->index(i, 7), Qt::DisplayRole).toFloat();
        z1=model->data(model->index(i, 8), Qt::DisplayRole).toFloat();
        r1=model->data(model->index(i, 9), Qt::DisplayRole).toFloat();

        x2=model->data(model->index(i, 10), Qt::DisplayRole).toFloat();
        y2=model->data(model->index(i, 11), Qt::DisplayRole).toFloat();
        z2=model->data(model->index(i, 12), Qt::DisplayRole).toFloat();
        //r2=model->data(model->index(i, 13), Qt::DisplayRole).toFloat();









        if(name=="line"){
            float dx = x2 - x0;
            float dy = y2 - y0;


            // 计算方向角
            float angleRad = std::atan2(dy, dx);
            float angleDeg = (angleRad * 180.0 / M_PI)+(inputR);

            float angleDegEquivalence;
            int cycleNum = r2 / 360;

            qDebug()<<"___________________";
            qDebug()<<"angleDegbefor: "<<angleDeg<<"   "<<i;

            // 让姿态角随方向走
            if (angleDeg>=0){

                if(cycleNum>=0){

                    angleDegEquivalence=(angleDeg)-((cycleNum-1)*360);
                    angleDeg=angleDeg+(cycleNum*360);
                }else{

                    angleDegEquivalence=(angleDeg)+((cycleNum+1)*360);
                    angleDeg=angleDeg-(cycleNum*360);
                }


            }else{

                if(cycleNum>=0){

                    angleDegEquivalence=(angleDeg)-((cycleNum-1)*360);
                    angleDeg=angleDeg+(cycleNum*360);
                }else{

                    angleDegEquivalence=(angleDeg)+((cycleNum+1)*360);
                    angleDeg=angleDeg-(cycleNum*360);
                }
            }

            float DifferenceA =fabs(angleDegEquivalence-r2);
            float DifferenceB =fabs(angleDeg-r2);

            qDebug()<<"______________________________________";
            qDebug()<<"curryR"<<r2<<"   cycleNum:"<<cycleNum;
            qDebug()<<"DifferenceA: "<<DifferenceA<<"   "<<i;
            qDebug()<<"DifferenceB: "<<DifferenceB<<"   "<<i;
            qDebug()<<"angleDeg2: "<<angleDegEquivalence<<"   "<<i;
            qDebug()<<"angleDegafter: "<<angleDeg<<"   "<<i;

            if(DifferenceA<DifferenceB){
                r2=angleDegEquivalence;
            }else{
                r2=angleDeg;
            }

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> c82df02 (界面)
            double Previous_r0= model->data(model->index(i-1, 13), Qt::DisplayRole).toFloat();

            model->setData(model->index(i, 4), 0);
            model->setData(model->index(i, 5), std::round(Previous_r0*100)/100);
            model->setData(model->index(i, 8), 0);
            model->setData(model->index(i, 12), 0);
            model->setData(model->index(i, 13), std::round(r2 * 100.0) / 100.0);
<<<<<<< HEAD
=======
            double Previous_r0=model->data(model->index(i-1, 13), Qt::DisplayRole).toFloat();

            model->setData(model->index(i, 4), 0);
            model->setData(model->index(i, 5), Previous_r0);
            model->setData(model->index(i, 8), 0);
            model->setData(model->index(i, 12), 0);
            model->setData(model->index(i, 13), r2);
>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da
=======
>>>>>>> c82df02 (界面)


            qDebug()<<"line: "<<r2<<"   "<<i;

        }else{

            QPointF A, B, C;
            A= QPointF( x0,y0 );
            C = QPointF( x2,y2 );
            B= QPointF( x1,y1 );

            float area = (B.x() - A.x()) * (C.y() - A.y()) - (B.y() - A.y()) * (C.x() - A.x());
            if (fabs(area) < 1e-9) {
                //throw std::runtime_error("三点共线，无法构成圆弧");
                qDebug()<<"Three points are not collinear";
            }
            //计算中点和垂直方向向量
            QPointF M1((A.x() + B.x()) / 2, (A.y() + B.y()) / 2);
            QPointF M2((B.x() + C.x()) / 2, (B.y() + C.y()) / 2);

            QPointF d1(B.y() - A.y(), A.x() - B.x()); // AB 的垂直向量
            QPointF d2(C.y() - B.y(), B.x() - C.x()); // BC 的垂直向量

            // 求两条中垂线的交点
            float det = d1.x() * d2.y() - d1.y() * d2.x();
            if (fabs(det) < 1e-9) {
                //throw std::runtime_error("计算中垂线交点失败");
                qDebug()<<"Failed to calculate the intersection point of the perpendicular line in the middle";
            }

            float t = ((M2.x() - M1.x()) * d2.y() - (M2.y() - M1.y()) * d2.x()) / det;
            QPointF center(M1.x() + t * d1.x(), M1.y() + t * d1.y());

            // 计算半径
            //double radius = std::hypot(center.x() - A.x(), center.y() - A.y());

            // 判断旋转方向
            float crossProduct = (B.x() - A.x()) * (C.y() - B.y()) - (B.y() - A.y()) * (C.x() - B.x());
            QString direction = crossProduct > 0 ? "CCW" : "CW";

            float I = center.x() - A.x();
            float J = center.y() - A.y();


            // 将点转换为从圆心出发的向量
            QPointF vec1 = A - center;
            QPointF vec2 = C - center;
            // 计算两向量夹角（弧度）
            float angle = std::atan2(vec2.y(), vec2.x()) - std::atan2(vec1.y(), vec1.x());

            // 根据方向调整角度方向和范围
            if (direction == "CW" && angle > 0) {
                angle -= 2 * M_PI;
            }
            else if (direction == "CCW" && angle < 0) {
                angle += 2 * M_PI;
            }

            // 将弧度转为角度（如果你希望以角度为单位加到 r2 上）
            double angleDeg = (angle * 180.0 / M_PI)+(inputR);

            // 加到 r2 上
            r2 += angleDeg;

            qDebug()<<"arc: "<<r2<<"   "<<i;
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> c82df02 (界面)
            double Previous_r0= model->data(model->index(i-1, 13), Qt::DisplayRole).toFloat();

            model->setData(model->index(i, 4), 0);
            model->setData(model->index(i, 5), std::round(Previous_r0*100)/100);
            model->setData(model->index(i, 8), 0);
            model->setData(model->index(i, 12), 0);
            model->setData(model->index(i, 13), std::round(r2 * 100.0) / 100.0);
<<<<<<< HEAD
=======
            double Previous_r0=model->data(model->index(i-1, 13), Qt::DisplayRole).toFloat();

            model->setData(model->index(i, 4), 0);
            model->setData(model->index(i, 5), Previous_r0);
            model->setData(model->index(i, 8), 0);
            model->setData(model->index(i, 12), 0);
            model->setData(model->index(i, 13), r2);
>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da
=======
>>>>>>> c82df02 (界面)


        }

    }

    model->submitAll();
    model->select();


    if (!db.commit()) {
        qDebug() << "Failed to commit transaction:" << db.lastError().text();
        QMessageBox::critical(this, "Error", "事务提交失败:" + db.lastError().text());
        db.rollback();
    }

}

void MainWindow::PbCreatGcode()
{
    if(ui->cBworkpiece->currentText()==""){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit("请选择工件"));
        return;
    }

    QString gCode = generateGCode();
    gcodeEidt->gcode=gCode;
    gcodeEidt->workPiece=ui->cBworkpiece->currentText();

    gcodeEidt->show();
    QTimer::singleShot(0, gcodeEidt, [this](){
        gcodeEidt->loadGCodeToPlainText();
    });
    ui->messText_lin->setText(QString::fromLocal8Bit(" g代码已导出   "));

}


void MainWindow::cleanTable(){

    db.transaction();
    GlobeUniquePoints.clear();
    model->removeRows(0, model->rowCount());
    model->submitAll();
    model->select();
    scene->clear();
    if (!db.commit()) {
        qDebug() << "Failed to commit transaction:" << db.lastError().text();
        QMessageBox::critical(this, "Error", "事务提交失败:" + db.lastError().text());
        db.rollback();
    }

}

void MainWindow::PbAxleVelocity_lin(){

    if(!scanDetectCtrl->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;
    }

    qDebug()<<"PbAxleVelocity_lin"<<ui->AxleVelocity_lin->text().toFloat();
    scanDetectCtrl->on_jog_velocity_editingFinished(ui->AxleVelocity_lin->text().toFloat());
    //QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 速度已设置   "));
    ui->messText_lin->setText(QString::fromLocal8Bit(" 定位速度已设置   "));
    saveSetting();
}



void MainWindow::PbPointVelocity_lin(){

    if(!scanDetectCtrl->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;
    }

    qDebug()<<"PbPointVelocity_lin"<<ui->pointVelocity_lin->text().toFloat();
    scanDetectCtrl->on_point_velocity_editingFinished(ui->pointVelocity_lin->text().toFloat());
    //QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 速度已设置   "));
    ui->messText_lin->setText(QString::fromLocal8Bit(" 点动速度已设置   "));
    saveSetting();
}


void MainWindow::PblinVelocity_lin(){

    if(!scanDetectCtrl->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;
    }

    qDebug()<<"PblinVelocity_lin"<<ui->lineVelocity_lin->text().toFloat();
    scanDetectCtrl->on_line_velocity_editingFinished(ui->lineVelocity_lin->text().toFloat());
    //QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 直线速度已设置   "));
    ui->messText_lin->setText(QString::fromLocal8Bit(" 直线速度已设置   "));
    saveSetting();

}

void MainWindow::PbarcVelocity_lin(){

    if(!scanDetectCtrl->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;
    }

    qDebug()<<"PbarcVelocity_lin"<<ui->arcVelocity_lin->text().toFloat();
    scanDetectCtrl->on_arc_velocity_editingFinished(ui->arcVelocity_lin->text().toFloat());
    //QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 圆弧速度已设置   "));
    ui->messText_lin->setText(QString::fromLocal8Bit(" 圆弧速度已设置   "));
    saveSetting();

}
void MainWindow::PbtrajectoryOffset() {
    bool ok;
    double inputX = ui->traject_x0->text().toDouble(&ok);
    double inputY = ui->traject_y0->text().toDouble(&ok);
    double inputR = ui->traject_r0->text().toDouble(&ok); // 角度

    // 获取第一个点的原始坐标
    double originalX = model->data(model->index(0, 2), Qt::DisplayRole).toFloat();
    double originalY = model->data(model->index(0, 3), Qt::DisplayRole).toFloat();

    // 计算平移偏移量
    _translationX = originalX - inputX;
    _translationY = originalY - inputY;
    _translationR = inputR;

    // 将角度转换为弧度
    double radians = _translationR * M_PI / 180.0;
    double cosR = std::cos(radians);
    double sinR = std::sin(radians);

    // 计算旋转中心（平移后的第一个点）
    double centerX = originalX - _translationX;
    double centerY = originalY - _translationY;

    int rowCount = model->rowCount();
    db.transaction();

    for (int i = 0; i < rowCount; ++i) {
        QString type = model->data(model->index(i, 1), Qt::DisplayRole).toString();

        if (type == "line") {
            double x1 = model->data(model->index(i, 2), Qt::DisplayRole).toFloat() - _translationX;
            double y1 = model->data(model->index(i, 3), Qt::DisplayRole).toFloat() - _translationY;
            double x2 = model->data(model->index(i, 10), Qt::DisplayRole).toFloat() - _translationX;
            double y2 = model->data(model->index(i, 11), Qt::DisplayRole).toFloat() - _translationY;

            // 旋转
            double rx1 = (x1 - centerX) * cosR - (y1 - centerY) * sinR +centerX;
            double ry1 = (x1 - centerX) * sinR + (y1 - centerY) * cosR +centerY;
            double rx2 = (x2 - centerX) * cosR - (y2 - centerY) * sinR +centerX;
            double ry2 = (x2 - centerX) * sinR + (y2 - centerY) * cosR +centerY;

            rx1 = std::round(rx1 * 100.0) / 100.0;  // std::round(v) 四舍五入到最近整数 :contentReference[oaicite:0]{index=0}
            ry1 = std::round(ry1 * 100.0) / 100.0;
            rx2   = std::round(rx2   * 100.0) / 100.0;
            ry2   = std::round(ry2   * 100.0) / 100.0;

            model->setData(model->index(i, 2), rx1);
            model->setData(model->index(i, 3), ry1);
            model->setData(model->index(i, 10), rx2);
            model->setData(model->index(i, 11), ry2);
        }
        else if (type == "arc") {
            double x1 = model->data(model->index(i, 2), Qt::DisplayRole).toFloat() - _translationX;
            double y1 = model->data(model->index(i, 3), Qt::DisplayRole).toFloat() - _translationY;
            double cx = model->data(model->index(i, 6), Qt::DisplayRole).toFloat() - _translationX;
            double cy = model->data(model->index(i, 7), Qt::DisplayRole).toFloat() - _translationY;
            double x2 = model->data(model->index(i, 10), Qt::DisplayRole).toFloat() - _translationX;
            double y2 = model->data(model->index(i, 11), Qt::DisplayRole).toFloat() - _translationY;

            // 旋转
            double rx1 = (x1 - centerX) * cosR - (y1 - centerY) * sinR +centerX;
            double ry1 = (x1 - centerX) * sinR + (y1 - centerY) * cosR +centerY;
            double rcx = (cx - centerX) * cosR - (cy - centerY) * sinR +centerX;
            double rcy = (cx - centerX) * sinR + (cy - centerY) * cosR +centerY;
            double rx2 = (x2 - centerX) * cosR - (y2 - centerY) * sinR +centerX;
            double ry2 = (x2 - centerX) * sinR + (y2 - centerY) * cosR +centerY;

            rx1 = std::round(rx1 * 100.0) / 100.0;  // std::round(v) 四舍五入到最近整数 :contentReference[oaicite:0]{index=0}
            ry1 = std::round(ry1 * 100.0) / 100.0;
            rcx   = std::round(rcx   * 100.0) / 100.0;
            rcy   = std::round(rcy   * 100.0) / 100.0;
            rx2   = std::round(rx2   * 100.0) / 100.0;
            ry2   = std::round(ry2   * 100.0) / 100.0;

            model->setData(model->index(i, 2), rx1);
            model->setData(model->index(i, 3), ry1);
            model->setData(model->index(i, 6), rcx);
            model->setData(model->index(i, 7), rcy);
            model->setData(model->index(i, 10), rx2);
            model->setData(model->index(i, 11), ry2);
        }
    }


    currentR=currentR-_translationR;
    settings->setValue("_translationX", _translationX);
    settings->setValue("_translationY", _translationY);
    settings->setValue("_translationR", _translationR);
    settings->setValue("currentR", currentR);

    ui->messText_lin->setText(QString::fromLocal8Bit("当前角度:%1").arg(currentR));
    model->submitAll();
    model->select();
    updateSence();
    if (!db.commit()) {
        qDebug() << "Failed to commit transaction:" << db.lastError().text();
        QMessageBox::critical(this, "Error", "事务提交失败:" + db.lastError().text());
        db.rollback();
    }

    ui->messText_lin->setText(QString::fromLocal8Bit(" 已偏移 x%1 y%2 r%3  ").arg(_translationX).arg(_translationY).arg(_translationR));

}




void MainWindow::PbImageProcess()
{

    imageProcessingTool->show();

}

void MainWindow::pbAscan()
{


    scan->show();
}


void MainWindow::modbusStateChange(QModbusDevice::State state){


    if (state==QModbusDevice::ConnectedState){
        ui->connect_but->setText(QString::fromLocal8Bit("已连接"));
    }
    else {
        ui->connect_but->setText(QString::fromLocal8Bit("未连接"));
    }

}

void MainWindow::PbMoveToPosition(){

    double x = ui->traject_x0->text().toDouble();
    double y = ui->traject_y0->text().toDouble();
    double z = ui->traject_z0->text().toDouble();
    double r = ui->traject_r0->text().toDouble();

    qDebug()<<"x"<<x<<"y"<<y<<"z"<<z<<"r"<<r;
    // 调用运动控制，设置目标位置
    scanDetectCtrl->runTargetPosition(x, y, z, r);

}
void MainWindow::PbSetOrigin(){

    QString Axit=ui->selectAxitO_cb->currentText();
    scanDetectCtrl->on_setOriginBtn_clicked(Axit);
    ui->messText_lin->setText(QString::fromLocal8Bit(" 零点已设置   "));



}


void MainWindow::selectWorkpiece(){


    curryWorkpieceName=ui->cBworkpiece->currentText();
    if(curryWorkpieceName==""){
        curryWorkpieceName="Initialization";
        createOrSwitchTable(curryWorkpieceName,true);
<<<<<<< HEAD
<<<<<<< HEAD
        ui->cBworkpiece->addItem(curryWorkpieceName);
=======
         ui->cBworkpiece->addItem(curryWorkpieceName);
>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da
=======
        ui->cBworkpiece->addItem(curryWorkpieceName);
>>>>>>> c82df02 (界面)
        ui->cBworkpiece->setCurrentText(curryWorkpieceName);
    }else{
        createOrSwitchTable(curryWorkpieceName,false);

    }




}

void MainWindow::pbnewPiece(){

    bool ok;
    QString text = QInputDialog::getText(this, QString::fromLocal8Bit("添加新工件"),
                                         QString::fromLocal8Bit("请输入新工件名称："), QLineEdit::Normal,
                                         "", &ok);

    if (ok && !text.isEmpty()) {
        // 检查输入是否以数字开头
        if (text.at(0).isDigit()) {
            QMessageBox::warning(this, QString::fromLocal8Bit("无效输入"),
                                 QString::fromLocal8Bit("工件名称不能以数字开头，请重新输入。"));
            return;
        }

    }
    if (ok && !text.isEmpty()) {

        createOrSwitchTable(text,true);

        // 添加新工件名称到 QComboBox
        ui->cBworkpiece->addItem(text);
        // 设置新添加的工件为当前选中项
        ui->cBworkpiece->setCurrentText(text);

        WorkpieceList.push_back(text);

        QStringList list = QStringList::fromVector(WorkpieceList);

        settings->setValue("WorkpieceList", list);

    } else if (ok && text.isEmpty()) {
        // 用户点击了“确定”但未输入内容
        QMessageBox::warning(this, tr("输入无效"), tr("工件名称不能为空。"));
    }
    // 如果用户点击了“取消”，不执行任何操作

    saveSetting();

}

void MainWindow::pbdeletePiece(){

    QString selectedText = ui->cBworkpiece->currentText();
    if (selectedText.isEmpty()||selectedText=="Initialization") {
        return;
    }

    // 从 QComboBox 中移除选中的项
    int index = ui->cBworkpiece->currentIndex();
    if (index != -1) {
        ui->cBworkpiece->removeItem(index);
    }

    // 更新 WorkpieceList
    WorkpieceList.removeOne(selectedText);
    QStringList list = QStringList::fromVector(WorkpieceList);
    settings->setValue("WorkpieceList", list);

    // 删除数据库中关联的表
    QSqlQuery query(db);
    QString dropTableQuery = QString("DROP TABLE IF EXISTS %1").arg(selectedText);
    if (!query.exec(dropTableQuery)) {
        qDebug() << "删除表失败：" << query.lastError().text();
    }

    // 更新 QComboBox 的显示顺序
    //std::reverse(WorkpieceList.begin(), WorkpieceList.end());
    ui->cBworkpiece->clear();
    ui->cBworkpiece->addItems(QStringList::fromVector(WorkpieceList));

    // 切换逻辑
    if (!WorkpieceList.isEmpty()) {
        QString newCurrent = WorkpieceList.first();
        ui->cBworkpiece->setCurrentText(newCurrent);
        createOrSwitchTable(newCurrent, false);  // 切换到新表
    } else {
        // 没有工件了，自动切换到备用表 Initialization
        ui->cBworkpiece->setCurrentText("Initialization");
        createOrSwitchTable("Initialization", false);  // 如果没有就创建
    }



}

void MainWindow::cbSelectPlcType(int index){

    if (index == 0) {
        // 直接将 h5u 数据复制到 basePlc
        memcpy(&scanDetectCtrl->basePlcData, &scanDetectCtrl->h5uData, sizeof(h5u));
    }
    else if (index == 1) {
        // 直接将 ac700 数据复制到 basePlc
        memcpy(&scanDetectCtrl->basePlcData, &scanDetectCtrl->ac700Data, sizeof(ac700));
    }



    qDebug() << "MovePointDate:" << scanDetectCtrl->basePlcData.MovePointDate;
    qDebug() << "Start:" << scanDetectCtrl->basePlcData.Start;
    qDebug() << "Stop:" << scanDetectCtrl->basePlcData.Stop;
    qDebug() << "End:" << scanDetectCtrl->basePlcData.End;
    qDebug() << "AlarmReset:" << scanDetectCtrl->basePlcData.AlarmReset;
    qDebug() << "SetOrigin:" << scanDetectCtrl->basePlcData.SetOrigin;
    qDebug() << "ZdetctHight:" << scanDetectCtrl->basePlcData.ZdetctHight;
    qDebug() << "LineV:" << scanDetectCtrl->basePlcData.LineV;
    qDebug() << "ArcV:" << scanDetectCtrl->basePlcData.ArcV;
    qDebug() << "xV:" << scanDetectCtrl->basePlcData.xV;
    qDebug() << "yV:" << scanDetectCtrl->basePlcData.yV;
    qDebug() << "jv:" << scanDetectCtrl->basePlcData.jv;
    qDebug() << "EndNumber:" << scanDetectCtrl->basePlcData.EndNumber;
    qDebug() << "XOrigin:" << scanDetectCtrl->basePlcData.XOrigin;
    qDebug() << "YOrigin:" << scanDetectCtrl->basePlcData.YOrigin;
    qDebug() << "ZOrigin:" << scanDetectCtrl->basePlcData.ZOrigin;
    qDebug() << "ROrigin:" << scanDetectCtrl->basePlcData.ROrigin;
    qDebug() << "moveType:" << scanDetectCtrl->basePlcData.moveType;
    qDebug() << "singeMove:" << scanDetectCtrl->basePlcData.singeMove;
    qDebug() << "curX:" << scanDetectCtrl->basePlcData.curX;
    qDebug() << "curY:" << scanDetectCtrl->basePlcData.curY;
    qDebug() << "curZ:" << scanDetectCtrl->basePlcData.curZ;
    qDebug() << "curR:" << scanDetectCtrl->basePlcData.curR;
    qDebug() << "AxiSid:" << scanDetectCtrl->basePlcData.AxiSid;
    qDebug() << "X_ADD:" << scanDetectCtrl->basePlcData.X_ADD;
    qDebug() << "X_SUB:" << scanDetectCtrl->basePlcData.X_SUB;
    qDebug() << "Y_ADD:" << scanDetectCtrl->basePlcData.Y_ADD;
    qDebug() << "Y_SUB:" << scanDetectCtrl->basePlcData.Y_SUB;
    qDebug() << "Z_ADD:" << scanDetectCtrl->basePlcData.Z_ADD;
    qDebug() << "Z_SUB:" << scanDetectCtrl->basePlcData.Z_SUB;
    qDebug() << "R_ADD:" << scanDetectCtrl->basePlcData.R_ADD;
    qDebug() << "R_SUB:" << scanDetectCtrl->basePlcData.R_SUB;
    qDebug() << "X_VIRTUAL_ORIGIN:" << scanDetectCtrl->basePlcData.X_VIRTUAL_ORIGIN;
    qDebug() << "Y_VIRTUAL_ORIGIN:" << scanDetectCtrl->basePlcData.Y_VIRTUAL_ORIGIN;
    qDebug() << "MACHINE_ORIGIN:" << scanDetectCtrl->basePlcData.MACHINE_ORIGIN;
    qDebug() << "LIMIT_POINT:" << scanDetectCtrl->basePlcData.LIMIT_POINT;
    qDebug() << "xDone:" << scanDetectCtrl->basePlcData.xDone;
    qDebug() << "YDone:" << scanDetectCtrl->basePlcData.YDone;
}


// 上移按钮点击事件
void MainWindow::pbmoveUpForSort()
{
    // 获取当前选中的行
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) return;

    int row = selectedIndexes.first().row();
    int rowCount = model->rowCount();
    if (row ==0) {return;  }

    // 获取当前行和下一行的数据
    QSqlRecord currentRecord = model->record(row);
    QSqlRecord nextRecord = model->record(row -1);

    // 开始执行交换操作
    QSqlQuery query(db);

    // 先将当前行的 id 设置为临时值 -1
    query.prepare("UPDATE Initialization SET id=-1 WHERE id=:id");
    query.bindValue(":id", currentRecord.value("id"));
    if (!query.exec()) {
        qDebug() << "Error updating current row to temp id: " << query.lastError().text();
        return;
    }

    // 将下一行的 id 设置为当前行的 id
    query.prepare("UPDATE Initialization SET id=:id WHERE id=:next_id");
    query.bindValue(":id", currentRecord.value("id"));
    query.bindValue(":next_id", nextRecord.value("id"));
    if (!query.exec()) {
        qDebug() << "Error updating next row to current id: " << query.lastError().text();
        return;
    }

    // 将临时 id (-1) 设置为下一行的 id
    query.prepare("UPDATE Initialization SET id=:id WHERE id=-1");
    query.bindValue(":id", nextRecord.value("id"));
    if (!query.exec()) {
        qDebug() << "Error updating temp id to next id: " << query.lastError().text();
        return;
    }

    // 提交更改并调试
    if (model->submitAll()) {
        qDebug() << "Changes submitted successfully.";
    } else {
        qDebug() << "Error submitting changes: " << model->lastError().text();
    }


    // 重新选择数据以更新视图
    model->select();
    updateSence();
}

// 下移按钮点击事件
void MainWindow::pbmoveDownForSort()
{
    // 获取当前选中的行
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) return;

    int row = selectedIndexes.first().row();
    int rowCount = model->rowCount();
    if (row ==rowCount) {return;  }

    // 获取当前行和下一行的数据
    QSqlRecord currentRecord = model->record(row);
    QSqlRecord nextRecord = model->record(row +1);


    // 开始执行交换操作
    QSqlQuery query(db);

    // 先将当前行的 id 设置为临时值 -1
    query.prepare("UPDATE Initialization SET id=-1 WHERE id=:id");
    query.bindValue(":id", currentRecord.value("id"));
    if (!query.exec()) {
        qDebug() << "Error updating current row to temp id: " << query.lastError().text();
        return;
    }

    // 将下一行的 id 设置为当前行的 id
    query.prepare("UPDATE Initialization SET id=:id WHERE id=:next_id");
    query.bindValue(":id", currentRecord.value("id"));
    query.bindValue(":next_id", nextRecord.value("id"));
    if (!query.exec()) {
        qDebug() << "Error updating next row to current id: " << query.lastError().text();
        return;
    }

    // 将临时 id (-1) 设置为下一行的 id
    query.prepare("UPDATE Initialization SET id=:id WHERE id=-1");
    query.bindValue(":id", nextRecord.value("id"));
    if (!query.exec()) {
        qDebug() << "Error updating temp id to next id: " << query.lastError().text();
        return;
    }

    // 提交更改并调试
    if (model->submitAll()) {
        qDebug() << "Changes submitted successfully.";
    } else {
        qDebug() << "Error submitting changes: " << model->lastError().text();
    }



    // 重新选择数据以更新视图
    model->select();
    updateSence();
}


void MainWindow::pbMoveDirectionNot(){
<<<<<<< HEAD
<<<<<<< HEAD
=======


    // 获取当前选中的行
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        qDebug() << "没有选中行";
        return;
    }
    int row = selectedIndexes.first().row();
    qDebug() << "选中行:" << row;

    // 读取当前行中起点与终点的 xyzr 数据
    double startX = model->data(model->index(row, 2)).toDouble();
    double startY = model->data(model->index(row, 3)).toDouble();
    double startZ = model->data(model->index(row, 4)).toDouble();
    double startR = model->data(model->index(row, 5)).toDouble();

    double endX   = model->data(model->index(row, 10)).toDouble();
    double endY   = model->data(model->index(row, 11)).toDouble();
    double endZ   = model->data(model->index(row, 12)).toDouble();
    double endR   = model->data(model->index(row, 13)).toDouble();

    qDebug() << "交换前:";
    qDebug() << "起点: " << startX << startY << startZ << startR;
    qDebug() << "终点: " << endX << endY << endZ << endR;

    // 进行互换操作：将起点数据设置为旧终点的数据，终点数据设置为旧起点的数据
    model->setData(model->index(row, 2), endX);
    model->setData(model->index(row, 3), endY);
    model->setData(model->index(row, 4), endZ);
    model->setData(model->index(row, 5), endR);

    model->setData(model->index(row, 10), startX);
    model->setData(model->index(row, 11), startY);
    model->setData(model->index(row, 12), startZ);
    model->setData(model->index(row, 13), startR);

    // 调试信息，检查更新后的数据
    qDebug() << "交换后:";
    qDebug() << "起点: " << model->data(model->index(row, 2)).toDouble()
             << model->data(model->index(row, 3)).toDouble()
             << model->data(model->index(row, 4)).toDouble()
             << model->data(model->index(row, 5)).toDouble();
    qDebug() << "终点: " << model->data(model->index(row, 10)).toDouble()
             << model->data(model->index(row, 11)).toDouble()
             << model->data(model->index(row, 12)).toDouble()
             << model->data(model->index(row, 13)).toDouble();

    // 提交更改并刷新模型视图
    if (model->submitAll()) {
        qDebug() << "数据更新成功";
    } else {
        qDebug() << "数据更新失败:" << model->lastError().text();
    }
    model->select();
    updateSence();




}

void MainWindow::pbGetCurryPoint(){
>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da

    if(m_isSelected){

<<<<<<< HEAD
    // 获取当前选中的行
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        qDebug() << "没有选中行";
        return;
    }
    int row = selectedIndexes.first().row();
    qDebug() << "选中行:" << row;

    // 读取当前行中起点与终点的 xyzr 数据
    double startX = model->data(model->index(row, 2)).toDouble();
    double startY = model->data(model->index(row, 3)).toDouble();
    double startZ = model->data(model->index(row, 4)).toDouble();
    double startR = model->data(model->index(row, 5)).toDouble();

    double endX   = model->data(model->index(row, 10)).toDouble();
    double endY   = model->data(model->index(row, 11)).toDouble();
    double endZ   = model->data(model->index(row, 12)).toDouble();
    double endR   = model->data(model->index(row, 13)).toDouble();

    qDebug() << "交换前:";
    qDebug() << "起点: " << startX << startY << startZ << startR;
    qDebug() << "终点: " << endX << endY << endZ << endR;

    // 进行互换操作：将起点数据设置为旧终点的数据，终点数据设置为旧起点的数据
    model->setData(model->index(row, 2), endX);
    model->setData(model->index(row, 3), endY);
    model->setData(model->index(row, 4), endZ);
    model->setData(model->index(row, 5), endR);

    model->setData(model->index(row, 10), startX);
    model->setData(model->index(row, 11), startY);
    model->setData(model->index(row, 12), startZ);
    model->setData(model->index(row, 13), startR);

    // 调试信息，检查更新后的数据
    qDebug() << "交换后:";
    qDebug() << "起点: " << model->data(model->index(row, 2)).toDouble()
             << model->data(model->index(row, 3)).toDouble()
             << model->data(model->index(row, 4)).toDouble()
             << model->data(model->index(row, 5)).toDouble();
    qDebug() << "终点: " << model->data(model->index(row, 10)).toDouble()
             << model->data(model->index(row, 11)).toDouble()
             << model->data(model->index(row, 12)).toDouble()
             << model->data(model->index(row, 13)).toDouble();

    // 提交更改并刷新模型视图
    if (model->submitAll()) {
        qDebug() << "数据更新成功";
    } else {
        qDebug() << "数据更新失败:" << model->lastError().text();
    }
    model->select();
    updateSence();



=======


    // 获取当前选中的行
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
        qDebug() << "没有选中行";
        return;
    }
    int row = selectedIndexes.first().row();
    qDebug() << "选中行:" << row;

    // 读取当前行中起点与终点的 xyzr 数据
    double startX = model->data(model->index(row, 2)).toDouble();
    double startY = model->data(model->index(row, 3)).toDouble();
    double startZ = model->data(model->index(row, 4)).toDouble();
    double startR = model->data(model->index(row, 5)).toDouble();

    double endX   = model->data(model->index(row, 10)).toDouble();
    double endY   = model->data(model->index(row, 11)).toDouble();
    double endZ   = model->data(model->index(row, 12)).toDouble();
    double endR   = model->data(model->index(row, 13)).toDouble();

    qDebug() << "交换前:";
    qDebug() << "起点: " << startX << startY << startZ << startR;
    qDebug() << "终点: " << endX << endY << endZ << endR;

    // 进行互换操作：将起点数据设置为旧终点的数据，终点数据设置为旧起点的数据
    model->setData(model->index(row, 2), endX);
    model->setData(model->index(row, 3), endY);
    model->setData(model->index(row, 4), endZ);
    model->setData(model->index(row, 5), endR);

    model->setData(model->index(row, 10), startX);
    model->setData(model->index(row, 11), startY);
    model->setData(model->index(row, 12), startZ);
    model->setData(model->index(row, 13), startR);

    // 调试信息，检查更新后的数据
    qDebug() << "交换后:";
    qDebug() << "起点: " << model->data(model->index(row, 2)).toDouble()
             << model->data(model->index(row, 3)).toDouble()
             << model->data(model->index(row, 4)).toDouble()
             << model->data(model->index(row, 5)).toDouble();
    qDebug() << "终点: " << model->data(model->index(row, 10)).toDouble()
             << model->data(model->index(row, 11)).toDouble()
             << model->data(model->index(row, 12)).toDouble()
             << model->data(model->index(row, 13)).toDouble();

    // 提交更改并刷新模型视图
    if (model->submitAll()) {
        qDebug() << "数据更新成功";
    } else {
        qDebug() << "数据更新失败:" << model->lastError().text();
    }
    model->select();
    updateSence();



>>>>>>> c82df02 (界面)

}

void MainWindow::pbGetModelPoint(){

    if(m_isSelected){

        // 弹出对话框让用户选点类型……
        QStringList options;
        options << QStringLiteral("起始点")
                << QStringLiteral("过渡点")
                << QStringLiteral("终点");

<<<<<<< HEAD
=======
        // 弹出对话框让用户选点类型……
        QStringList options;
        options << QStringLiteral("起始点")
                << QStringLiteral("过渡点")
                << QStringLiteral("终点");

>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da
=======
>>>>>>> c82df02 (界面)
        bool ok;
        QString choice = QInputDialog::getItem(this,
                                               QStringLiteral("选择点类型"),
                                               QStringLiteral("请选择点类型:"),
                                               options, 0, false, &ok);


        // —— 直接从 model 里取坐标 ——
        // 起始点列：2–5， 过渡点列：6–9， 终点列：10–13
        int colBase = 0;
        if (choice == QStringLiteral("起始点"))      colBase = 2;
        else if (choice == QStringLiteral("过渡点")) colBase = 6;
        else if (choice == QStringLiteral("终点"))    colBase = 10;

        // 依次读取 x,y,z,r
        double x = model->data(model->index(m_lastClickedRow, colBase + 0)).toDouble();
        double y = model->data(model->index(m_lastClickedRow, colBase + 1)).toDouble();
        double z = model->data(model->index(m_lastClickedRow, colBase + 2)).toDouble();
        double r = model->data(model->index(m_lastClickedRow, colBase + 3)).toDouble();


        ui->traject_x0->setText(QString::number(x));
        ui->traject_y0->setText(QString::number(y));
        ui->traject_z0->setText(QString::number(z));
        ui->traject_r0->setText(QString::number(r));

    }


<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> c82df02 (界面)
}


std::tuple<double, double, double, double> MainWindow::pbGetCurrentlyPoint(){

    double x=ui->xCurPos_lab->text().toDouble();
    double y=ui->yCurPos_lab->text().toDouble();
    double z=ui->zCurPos_lab->text().toDouble();
    double r=ui->rCurPos_lab->text().toDouble();

    return std::make_tuple(x, y, z, r);

}

void MainWindow::createOrSwitchTable(const QString &tableName, bool isCreate)
{
    qDebug() << "isCreate =" << isCreate;


    db.transaction();
    if (isCreate) {
        QString currentTable = model->tableName();
        if (tableName == currentTable) {
            qDebug() << "目标表与当前表相同，跳过复制。";
            return;
        }

        QSqlDriver *drv = db.driver();
        QString qtgt = drv->escapeIdentifier(tableName, QSqlDriver::TableName);
        QString qsrc = drv->escapeIdentifier(currentTable, QSqlDriver::TableName);

        QSqlQuery q(db);
        QString checkSQL = QString(
                    "SELECT 1 FROM sqlite_master "
                    "WHERE type='table' AND name='%1';"
                    ).arg(tableName);
        if (!q.exec(checkSQL)) {
            qDebug() << "检查表存在性失败：" << q.lastError().text();
            return;
        }

        if (q.next()) {
            QString copySQL = QString(
                        "INSERT INTO %1 SELECT * FROM %2;"
                        ).arg(qtgt).arg(qsrc);
            if (!q.exec(copySQL)) {
                qDebug() << "复制数据失败：" << q.lastError().text();
                return;
            }
        } else {
            QString createSQL = QString(
                        "CREATE TABLE %1 AS SELECT * FROM %2;"
                        ).arg(qtgt).arg(qsrc);
            if (!q.exec(createSQL)) {
                qDebug() << "创建表并复制数据失败：" << q.lastError().text();
                return;
            }
        }
        model->setTable(tableName);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        ui->tableView->setModel(model);
    }else {
        model->setTable(tableName);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        ui->tableView->setModel(model);
    }



    if (!model->submitAll()) {
        qDebug() << "submiall fail：" << model->lastError().text();
        return;
    }

    if (!db.commit()) {
        qDebug() << "事务提交失败:" << db.lastError().text();
        QMessageBox::critical(this, "错误", "事务提交失败:" + db.lastError().text());
        db.rollback();
    } else {
        qDebug() << "排序及更新完成，事务提交成功！";
    }

    //saveSetting();
    updateSence();
}


<<<<<<< HEAD
=======
}

void MainWindow::createOrSwitchTable(const QString &tableName, bool isCreate)
{
    qDebug() << "isCreate =" << isCreate;


    db.transaction();
    if (isCreate) {
        QString currentTable = model->tableName();
        if (tableName == currentTable) {
            qDebug() << "目标表与当前表相同，跳过复制。";
            return;
        }

        QSqlDriver *drv = db.driver();
        QString qtgt = drv->escapeIdentifier(tableName, QSqlDriver::TableName);
        QString qsrc = drv->escapeIdentifier(currentTable, QSqlDriver::TableName);

        QSqlQuery q(db);
        QString checkSQL = QString(
                    "SELECT 1 FROM sqlite_master "
                    "WHERE type='table' AND name='%1';"
                    ).arg(tableName);
        if (!q.exec(checkSQL)) {
            qDebug() << "检查表存在性失败：" << q.lastError().text();
            return;
        }

        if (q.next()) {
            QString copySQL = QString(
                        "INSERT INTO %1 SELECT * FROM %2;"
                        ).arg(qtgt).arg(qsrc);
            if (!q.exec(copySQL)) {
                qDebug() << "复制数据失败：" << q.lastError().text();
                return;
            }
        } else {
            QString createSQL = QString(
                        "CREATE TABLE %1 AS SELECT * FROM %2;"
                        ).arg(qtgt).arg(qsrc);
            if (!q.exec(createSQL)) {
                qDebug() << "创建表并复制数据失败：" << q.lastError().text();
                return;
            }
        }
        model->setTable(tableName);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        ui->tableView->setModel(model);
    }else {
        model->setTable(tableName);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        ui->tableView->setModel(model);
    }



    if (!model->submitAll()) {
        qDebug() << "submiall fail：" << model->lastError().text();
        return;
    }

    if (!db.commit()) {
        qDebug() << "事务提交失败:" << db.lastError().text();
        QMessageBox::critical(this, "错误", "事务提交失败:" + db.lastError().text());
        db.rollback();
    } else {
        qDebug() << "排序及更新完成，事务提交成功！";
    }

    //saveSetting();
    updateSence();
}


>>>>>>> 7058bd5fc092b9b1a7f69132c6264c009aef17da
=======
>>>>>>> c82df02 (界面)
void MainWindow::saveSetting() {
    // Save general settings
    settings->setValue("ip", ui->ip_lin->text());
    settings->setValue("port", ui->port_lin->text());
    settings->setValue("plcType", ui->plcType_cb->currentIndex());
    settings->setValue("traject_x0", ui->traject_x0->text());
    settings->setValue("traject_y0", ui->traject_y0->text());
    settings->setValue("traject_z0", ui->traject_z0->text());
    settings->setValue("traject_r0", ui->traject_r0->text());

    // Update workpiece list
    QStringList pieces = settings->value("WorkpieceList", QStringList()).toStringList();


    for (int i = 0; i < ui->cBworkpiece->count(); ++i) {
        if (!pieces.contains(ui->cBworkpiece->itemText(i))) {
            pieces.append(ui->cBworkpiece->itemText(i));
        }
    }

    // 将所有工作件项保存到设置中
    settings->setValue("WorkpieceList", pieces);

    QString currentPiece = ui->cBworkpiece->currentText();

    // Save per-workpiece settings
    settings->beginGroup(currentPiece);
    settings->setValue("AxleV", ui->AxleVelocity_lin->text());
    settings->setValue("LineV", ui->lineVelocity_lin->text());
    settings->setValue("ArcV", ui->arcVelocity_lin->text());
    settings->setValue("ProcessType", ui->processType_cb->currentIndex());
    settings->setValue("pointV", ui->pointVelocity_lin->text());

    // 打印保存的值
    settings->endGroup();
    settings->sync();  // 强制写入磁盘


}

void MainWindow::initSetting() {
    // Load general settings with defaults
    ui->ip_lin->setText(settings->value("ip", "").toString());
    ui->port_lin->setText(settings->value("port", "").toString());
    ui->plcType_cb->setCurrentIndex(settings->value("plcType", 0).toInt());
    ui->traject_x0->setText(settings->value("traject_x0", "0").toString());
    ui->traject_y0->setText(settings->value("traject_y0", "0").toString());
    ui->traject_z0->setText(settings->value("traject_z0", "0").toString());
    ui->traject_r0->setText(settings->value("traject_r0", "0").toString());

    // Load workpiece list
    QStringList pieces = settings->value("WorkpieceList", QStringList()).toStringList();
    if (pieces.isEmpty()) {
        // 如果没有保存的工件，则使用默认工件（支持中文）
        pieces = QStringList() << QString::fromLocal8Bit("Initialization");
        settings->setValue("WorkpieceList", pieces);
    }


    // Populate workpiece combo box
    ui->cBworkpiece->clear();
    ui->cBworkpiece->addItems(pieces);
    ui->cBworkpiece->setCurrentIndex(0);

    // Determine active workpiece
    QString activePiece = ui->cBworkpiece->currentText();

    // If the workpiece group doesn't exist, use defaults
    QStringList groups = settings->childGroups();
    if (!groups.contains(activePiece)) {
        ui->AxleVelocity_lin->setText("");
        ui->lineVelocity_lin->setText("");
        ui->arcVelocity_lin->setText("");
        ui->processType_cb->setCurrentIndex(0);
    } else {
        settings->beginGroup(activePiece);
        ui->AxleVelocity_lin->setText(settings->value("AxleV", "").toString());
        ui->lineVelocity_lin->setText(settings->value("LineV", "").toString());
        ui->arcVelocity_lin->setText(settings->value("ArcV", "").toString());
        ui->pointVelocity_lin->setText(settings->value("pointV", "").toString());
        ui->processType_cb->setCurrentIndex(settings->value("ProcessType", 0).toInt());
        settings->endGroup();
    }

    // Apply loaded PLC type logic
    cbSelectPlcType(ui->plcType_cb->currentIndex());

    // Initialize table view
    ui->tableView->clearSpans();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    ui->tableView->verticalHeader()->setVisible(false);

    // Update scene if needed
    updateSence();
<<<<<<< HEAD
=======
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize newSize = event->size();
    qDebug() << "oldSize:" << oldSize << " newSize:" << newSize;


//    if (newSize.width() < oldSize.width() || newSize.height() < oldSize.height()) {
//        // 缩小，恢复控件初始状态
//        restoreOriginalWidgetStates(this->centralWidget());
//        oldSize = newSize;  // 更新 oldSize，防止多次缩小触发
//        //QMainWindow::resizeEvent(event);
//        return;
//    }

    double scaleX = static_cast<double>(newSize.width()) / oldSize.width();
    double scaleY = static_cast<double>(newSize.height()) / oldSize.height();

    scaleWidgets(this->centralWidget(), scaleX, scaleY);

    oldSize = newSize;
    QMainWindow::resizeEvent(event);
}

void MainWindow::scaleWidgets(QWidget* parent, double scaleX, double scaleY)
{
    for (QObject* obj : parent->children()) {
        QWidget* w = qobject_cast<QWidget*>(obj);
        if (!w || w->inherits("QLayout"))
            continue;

        // 缓存控件原始位置和大小（只缓存一次）
        if (!originalGeometries.contains(w)) {
            originalGeometries[w] = w->geometry();
        }

        QRect orig = originalGeometries[w];
        int newX = static_cast<int>(orig.x() * scaleX);
        int newY = static_cast<int>(orig.y() * scaleY);
        int newW = static_cast<int>(orig.width() * scaleX);
        int newH = static_cast<int>(orig.height() * scaleY);
        w->setGeometry(newX, newY, newW, newH);

        // 缓存原始字体大小
        if (!originalFontSizes.contains(w)) {
            originalFontSizes[w] = w->font().pointSizeF();
        }

        QFont font = w->font();
        double scale = (scaleX + scaleY) / 2.0;
        font.setPointSizeF(originalFontSizes[w] * scale);
        w->setFont(font);

        // 处理 QTableWidget 的行列缩放
        if (QTableWidget* table = qobject_cast<QTableWidget*>(w)) {
            for (int col = 0; col < table->columnCount(); ++col) {
                int oldWidth = table->columnWidth(col);
                table->setColumnWidth(col, static_cast<int>(oldWidth * scaleX));
            }
            for (int row = 0; row < table->rowCount(); ++row) {
                int oldHeight = table->rowHeight(row);
                table->setRowHeight(row, static_cast<int>(oldHeight * scaleY));
            }
        }

        // 处理 QTableView 的头部缩放
        if (QTableView* view = qobject_cast<QTableView*>(w)) {
            QHeaderView* hHeader = view->horizontalHeader();
            QHeaderView* vHeader = view->verticalHeader();
            if (hHeader) {
                for (int col = 0; col < hHeader->count(); ++col) {
                    int oldWidth = hHeader->sectionSize(col);
                    hHeader->resizeSection(col, static_cast<int>(oldWidth * scaleX));
                }
            }
            if (vHeader) {
                for (int row = 0; row < vHeader->count(); ++row) {
                    int oldHeight = vHeader->sectionSize(row);
                    vHeader->resizeSection(row, static_cast<int>(oldHeight * scaleY));
                }
            }
        }

        // 递归子控件
        scaleWidgets(w, scaleX, scaleY);
    }
>>>>>>> c82df02 (界面)
}



void MainWindow::scaleWidgets(QWidget* parent, double scaleX, double scaleY)
{
    for (QObject* obj : parent->children()) {
        QWidget* w = qobject_cast<QWidget*>(obj);
        if (w && !w->inherits("QLayout")) {
            QRect geom = w->geometry();
            int newX = static_cast<int>(geom.x() * scaleX);
            int newY = static_cast<int>(geom.y() * scaleY);
            int newW = static_cast<int>(geom.width() * scaleX);
            int newH = static_cast<int>(geom.height() * scaleY);
            w->setGeometry(newX, newY, newW, newH);

<<<<<<< HEAD
            // 递归：处理 frame、groupbox 里的控件
            scaleWidgets(w, scaleX, scaleY);
        }
=======
void MainWindow::restoreOriginalWidgetStates(QWidget* parent)
{
    for (QObject* obj : parent->children()) {
        QWidget* w = qobject_cast<QWidget*>(obj);
        if (!w || w->inherits("QLayout"))
            continue;

        if (originalGeometries.contains(w)) {
            w->setGeometry(originalGeometries[w]);
        }
        if (originalFonts.contains(w)) {
            w->setFont(originalFonts[w]);
        }

        // 递归恢复子控件
        restoreOriginalWidgetStates(w);
>>>>>>> c82df02 (界面)
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    static QSize oldSize = size();
    QSize newSize = event->size();

    double scaleX = static_cast<double>(newSize.width()) / oldSize.width();
    double scaleY = static_cast<double>(newSize.height()) / oldSize.height();

<<<<<<< HEAD
    scaleWidgets(this->centralWidget(), scaleX, scaleY);

    oldSize = newSize;
}














=======
void MainWindow::saveOriginalWidgetStates(QWidget* parent)
{
    oldSize=this->size();
    for (QObject* obj : parent->children()) {
        QWidget* w = qobject_cast<QWidget*>(obj);
        if (!w || w->inherits("QLayout"))
            continue;

        originalGeometries[w] = w->geometry();
        originalFonts[w] = w->font();

        // 递归保存子控件
        saveOriginalWidgetStates(w);
    }
}
>>>>>>> c82df02 (界面)


//void MainWindow::pbWriteInPLC()
//{


//    if(!scanDetectCtrl->modbusState()){
//        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
//        return;}

//    // 初始化进度条
//    progressDialog= new QProgressDialog;
//    progressDialog->setLabelText(tr("Writing registers..."));
//    progressDialog->setCancelButton(nullptr);  // 禁用取消按钮
//    //progressDialog->setWindowModality(Qt::WindowModal);  // 设置为模态
//    progressDialog->setRange(0, model->rowCount()); // size 是数据块的数量
//    progressDialog->show();


//    int row_count =model->rowCount();
//    //int column_cout=model->columnCount();
//    float x0,y0,r0,z0,x1,y1,r1,z1,x2,y2,z2,r2;
//    QString name;
//    QVector<QVector<float>> point;
//    QList<QString>list_name;


//    for(int i = 0; i < row_count; ++i)
//    {
//        name=model->data(model->index(i, 1), Qt::DisplayRole).toString();

//        if(name=="arc"){
//            x0=model->data(model->index(i, 2), Qt::DisplayRole).toFloat();
//            y0=model->data(model->index(i, 3), Qt::DisplayRole).toFloat();
//            z0=model->data(model->index(i, 4), Qt::DisplayRole).toFloat();
//            r0=model->data(model->index(i, 5), Qt::DisplayRole).toFloat();

//            x1=model->data(model->index(i, 6), Qt::DisplayRole).toFloat();
//            y1=model->data(model->index(i, 7), Qt::DisplayRole).toFloat();
//            z1=model->data(model->index(i, 8), Qt::DisplayRole).toFloat();
//            r1=model->data(model->index(i, 9), Qt::DisplayRole).toFloat();

//            x2=model->data(model->index(i, 10), Qt::DisplayRole).toFloat();
//            y2=model->data(model->index(i, 11), Qt::DisplayRole).toFloat();
//            z2=model->data(model->index(i, 12), Qt::DisplayRole).toFloat();
//            r2=model->data(model->index(i, 13), Qt::DisplayRole).toFloat();

//            point.push_back({x0, y0, z0, r0});
//            point.push_back({x1, y1, z1, r1});
//            point.push_back({x2, y2, z2, r2});

//        }else if (name=="line") {
//            x0=model->data(model->index(i, 2), Qt::DisplayRole).toFloat();
//            y0=model->data(model->index(i, 3), Qt::DisplayRole).toFloat();
//            z0=model->data(model->index(i, 4), Qt::DisplayRole).toFloat();
//            r0=model->data(model->index(i, 5), Qt::DisplayRole).toFloat();

//            x1=model->data(model->index(i, 6), Qt::DisplayRole).toFloat();
//            y1=model->data(model->index(i, 7), Qt::DisplayRole).toFloat();
//            z1=model->data(model->index(i, 4), Qt::DisplayRole).toFloat();
//            r1=model->data(model->index(i, 8), Qt::DisplayRole).toFloat();
//        }
//        point.push_back({x0, y0, z0, r0});
//        point.push_back({x1, y1, z1, r1});

//    }

//    int i = 0;
//    QEventLoop loop;
//    connect(this, &MainWindow::targetReached, &loop, &QEventLoop::quit);

//    for (const QVector<float>& pt : point) {


//        float x = pt[0];
//        float y = pt[1];
//        float z = pt[2];
//        float r = pt[3];
//        scanDetectCtrl->runTargetPosition(x,y,z,r);
//        currentTargetPos.x=x;
//        currentTargetPos.y=y;
//        currentTargetPos.z=z;
//        currentTargetPos.r=r;

//        progressDialog->setLabelText(tr("Writing registers... (%1/%2)").arg(i + 1).arg(point.count()));
//        progressDialog->setValue(i + 1);

//        qApp->processEvents();
//        {
//        loop.exec();
//        }

//        ++i;

//        qDebug()<<"write in plc" << "x:" << x << "y:" << y << "z:" << z << "r:" << r;
//    }

//    progressDialog->close();


//}

//        //添加轨迹原点-设定坐标原点为轨迹原点
//        model->insertRow(model->rowCount()); //添加一行

//        double o_endX=dcfData.at(0).at(0).x();
//        double o_endY=dcfData.at(0).at(0).y();
//        QPointF o_start= QPointF(0,0);
//        QPointF o_end= QPointF(o_endX,o_endY);
//        model->setData (model->index(model->rowCount(),1),"line");
//        model->setData (model->index(model->rowCount(),2),0);
//        model->setData (model->index(model->rowCount(),3),0);
//        model->setData (model->index(model->rowCount(),5),o_end.x());
//        model->setData (model->index(model->rowCount(),6),o_end.y());
//        model->setData (model->index(model->rowCount(),8),o_end.x());
//        model->setData (model->index(model->rowCount(),9),o_end.y());


//        line_item *itme =new line_item(o_start,o_end,0,scene);
//        scene->addItem(itme);

//        model->submitAll();
//        model->select();
//        scene->update();
//        ui->graphicsView->show();

//QList<QByteArray> MainWindow::splitByFour(const QByteArray &data) {
//    QList<QByteArray> result;
//    for (int i = 0; i < data.size(); i += 4) {
//        result.append(data.mid(i, 4));
//    }
//    return result;
//}
//QList<int> MainWindow::convertToDecimal(const QByteArray &data) {
//    QList<int> result;
//    for (char byte : data) {
//        result.append(static_cast<unsigned char>(byte));
//    }
//    return result;
//}
//QList<float> MainWindow::convertToReal(const QByteArray &data) {
//    QList<float> result;
//    QDataStream stream(data);
//    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
//    while (!stream.atEnd()) {
//        float value;
//        stream >> value;
//        result.append(value);
//    }
//    return result;
//}

//void MainWindow::pbIpLineEdit(const QString &arg1)
//{
//    qDebug()<<"on_ipLineEdit_textChanged";
//    scanDetectCtrl->setModbusTcpIP(arg1);
//}
//void MainWindow::readPendingDatagrams()
//{
//    while (udpSocket->hasPendingDatagrams()) {
//        /*QByteArray datagram;
//        datagram.resize(udpSocket->pendingDatagramSize());
//        QHostAddress sender;
//        quint16 senderPort;

//        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

//        // 处理接收到的数据
//        QString data = parseModbusResponse(datagram);
//        ui->textEdit->append("Received: " + data);*/
//        QByteArray datagram;
//        datagram.resize(udpSocket->pendingDatagramSize());
//        QHostAddress sender;
//        quint16 senderPort;
//        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
//        // char secondData = datagram[6];
//        QString string1 = QString::fromLocal8Bit(datagram);
//        QString str1 = QString::fromLatin1(datagram.toHex(':'));
//        qDebug() << sender.toString();
//        int size = datagram.size();
//        qDebug()<<"****size"<<size << datagram.toHex();
//        //ui->textEdit->append("Received: " + str1);

//        // 解析x坐标
//        float x = *reinterpret_cast<float*>(datagram.mid(0, 4).data());

//        // 解析y坐标
//        float y = *reinterpret_cast<float*>(datagram.mid(4, 4).data());

//        // 解析z坐标
//        float z = *reinterpret_cast<float*>(datagram.mid(8, 4).data());

//        // 解析r坐标
//        float r = *reinterpret_cast<float*>(datagram.mid(12, 4).data());
//        qDebug() << "x:" << x << "y:" << y << "z:" << z << "r:" << r;


//#if 1
//        QList<QByteArray> splittedData = splitByFour(datagram);
//        for ( QByteArray &chunk : splittedData) {
//            //qDebug() << chunk.toHex();

//            if (chunk.size() == sizeof(float)) {
//                // 使用 std::reverse 反转 QByteArray
//                std::reverse(chunk.begin(), chunk.end());

//                double value;
//                QDataStream stream(chunk);
//                stream.setByteOrder(QDataStream::LittleEndian); // 根据实际的字节序选择
//                stream >> value;
//                qDebug() << "Converted value:" << value;
//                /*
//                        float realValue;
//                        QDataStream stream(chunk);
//                        stream.readRawData(reinterpret_cast<char*>(&realValue), sizeof(realValue));
//                        std::cout << "Float value: " << realValue << std::endl;
//                        */
//                /*
//                        // 将 QByteArray 中的数据赋值给 uint32_t
//                        uint32_t uintValue;
//                        std::memcpy(&uintValue, chunk.constData(), sizeof(uint32_t));

//                        // 输出结果，注意大小端问题
//                        std::cout << std::hex << std::showbase << uintValue << std::endl;
//                        */
//                /*
//                        QByteArray byteArray = QByteArray::fromHex("436EE909");
//                        // 检查 QByteArray 的大小是否与 float 的大小匹配
//                        if (chunk.size() != sizeof(float)) {
//                            std::cerr << "Invalid byte array size for float" << std::endl;
//                            return ;
//                        }
//                        // 将 QByteArray 转换为 float
//                        float floatValue;
//                        std::memcpy(&floatValue, chunk.constData(), sizeof(float));


//                        uint32_t hexValue = 0x436EE909;
//                        std::memcpy(&floatValue, &hexValue, sizeof(float));
//                        // 设置输出精度
//                        std::cout << std::setprecision(6) << floatValue << std::endl;
//                        */


//                // 使用 QString::number 将 float 转换为 QString
//                //QString stringValue = QString::number(uintValue);
//                //QString str = QString::number(floatValue, 'f', 6);


//                ui->textEdit->append("Received: " + chunk.toHex());

//            } else {
//                std::cerr << "Invalid byte array size for float" << std::endl;
//            }

//            /*
//                QList<float> realData = convertToReal(chunk);

//                // 打印结果
//                for (float value : realData) {
//                    //std::cout << std::fixed << std::setprecision(3) << value << std::endl;
//                    qDebug() << value;
//                    QString str = QString::number(value, 'f', 3); // 'f'表示浮点数格式，6表示小数点后保留6位


//                }*/
//            // ui->textEdit->append("Received: " + chunk.toHex());
//        }
//#endif
//    }

//}

//*************************************************************8
//QByteArray MainWindow::createModbusRequest(int registerAddress)
//{qDebug()<<"readPendingDatagrams";
//    QByteArray request;

//    // Transaction identifier (2 bytes)
//    request.append(static_cast<char>(0x00));
//    request.append(static_cast<char>(0x00));

//    // Protocol identifier (2 bytes, 0x0000 for Modbus)
//    request.append(static_cast<char>(0x00));
//    request.append(static_cast<char>(0x00));

//    // Length (2 bytes, the length of the remaining bytes in the message)
//    request.append(static_cast<char>(0x00));
//    request.append(0x06);

//    // Unit identifier (1 byte, often called the slave address)
//    request.append(0x01);

//    // Function code (1 byte, 0x03 for Read Holding Registers)
//    request.append(0x03);

//    // Starting address (2 bytes)
//    request.append((registerAddress - 40001) >> 8); // High byte
//    request.append((registerAddress - 40001) & 0xFF); // Low byte

//    // Quantity of registers (2 bytes, number of registers to read)
//    request.append(static_cast<char>(0x00)); // High byte
//    request.append(0x01); // Low byte

//    return request;
//}
//void MainWindow::onStateChanged(QModbusDevice::State state)
//{
//    qDebug()<<"****state=****"<<state<<"**"<<QModbusDevice::ConnectedState;
//    if (state == QModbusDevice::ConnectedState) {
//        ui->textEdit->setText("Connected to PLC.");
//        //ui->connectButton->setText("Disconnect");
//        QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 5000, 10);
//        if (auto *reply = modbusDevice->sendReadRequest(readUnit, 1)) {
//            if (!reply->isFinished())
//                connect(reply, &QModbusReply::finished, this, &MainWindow::readReady);
//            else
//                delete reply;
//        } else {
//            ui->textEdit->setText("Read error: " + modbusDevice->errorString());
//        }
//    } else if (state == QModbusDevice::UnconnectedState) {
//        ui->textEdit->setText("Disconnected from PLC.");
//        //qDebug()<<"****UnconnectedState=****";
//    }
//}

//void MainWindow::onModbusError(QModbusDevice::Error error)
//{qDebug()<<"onModbusError";
//    if (error == QModbusDevice::NoError)
//        return;
//    ui->textEdit->setText("Modbus error: " + modbusDevice->errorString());
//}

//float MainWindow::readModbusFloatData(int v1, int v2)
//{qDebug()<<"readModbusFloatData";
//    uint32_t intValue = (static_cast<uint32_t>(v1) << 16) | static_cast<uint32_t>(v2);
//    return *reinterpret_cast<float*>(&intValue);
//}

//void MainWindow::pbModbusConnect()
//{qDebug()<<"pbModbusConnect";
//    QString address = ui->ipLineEdit->text();
//    int port = ui->portLineEdit->text().toInt();
//    qDebug()<<"****ip"<<address<<"**port"<<port;
//    modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, address);
//    modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, port);
//    modbusDevice->setTimeout(1000);
//    modbusDevice->setNumberOfRetries(3);

//    if (modbusDevice->connectDevice()) {
//        ui->connectButton->setText(" 已连接 ");

//    } else {
//        QMessageBox::critical(this, tr("Connection Failed"),
//                              tr("Connection failed: %1").arg(modbusDevice->errorString()));
//        //this->statusBar()->showMessage("Connection failed:", 0);
//    }
//}

//    void readReady();
//void MainWindow::readReady()
//{qDebug()<<"readReady";
//    auto reply = qobject_cast<QModbusReply *>(sender());
//    if (!reply)
//        return;

//    if (reply->error() == QModbusDevice::NoError) {
//        const QModbusDataUnit unit = reply->result();
//        for (uint i = 0; i < unit.valueCount(); i++) {
//            float xVel = readModbusFloatData(unit.value(+i), unit.value(i));
//            //ui->textEdit->append(QString("Address: %1, Value: %2").arg(unit.startAddress() + i).arg(unit.value(i)));
//            ui->textEdit->append(QString("Address: %1, Value: %2").arg(unit.startAddress() + i).arg(xVel));
//        }
//    } else {
//        ui->textEdit->append("Read response error: " + reply->errorString());
//    }

//    reply->deleteLater();
//}



//connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readPendingDatagrams);

//connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::pbModbusConnect);
//connect(modbusDevice, &QModbusTcpClient::stateChanged, this, &MainWindow::onStateChanged);
//connect(modbusDevice, &QModbusTcpClient::errorOccurred, this, &MainWindow::onModbusError);

//    udpSocket = new QUdpSocket(this);
//    // 绑定本地端口，确保可以接收消息
//    udpSocket->bind(QHostAddress("192.168.1.100"), 12345);
/*while (udpSocket->hasPendingDatagrams())
{
    qDebug()<<"**readudp*** =";
}*/
//qDebug()<<"**LocalHost =";

// 发送读取寄存器4002的Modbus请求
//QByteArray request = createModbusRequest(5000);
//udpSocket->writeDatagram(request, QHostAddress("192.168.1.88"), 502);


//QString MainWindow::parseModbusResponse(const QByteArray &response)
//{
//    if (response.size() < 9) {
//        return "Invalid response";
//    }

//    // 提取数据部分（假设单个寄存器返回2字节数据）
//    int data = (response.at(9) << 8) + static_cast<unsigned char>(response.at(10));
//    return QString::number(data);
//}


//    fdelegate = new floatpointdelegate;
//    ui->tableView->setItemDelegateForColumn(0,fdelegate);
//    ui->tableView->setItemDelegateForColumn(1,fdelegate);
//    ui->tableView->setItemDelegateForColumn(2,fdelegate);
//    ui->tableView->setItemDelegateForColumn(3,fdelegate);
//    ui->tableView->setItemDelegateForColumn(4,fdelegate);
//    ui->tableView->setItemDelegateForColumn(5,fdelegate);
//    ui->tableView->setItemDelegateForColumn(6,fdelegate);
//    ui->tableView->setItemDelegateForColumn(7,fdelegate);
//    ui->tableView->setItemDelegateForColumn(8,fdelegate);
//    ui->tableView->setItemDelegateForColumn(9,fdelegate);
//    ui->tableView->setItemDelegateForColumn(10,fdelegate);
//    ui->tableView->setItemDelegateForColumn(11,fdelegate);
//    ui->tableView->setColumnHidden(0,false);
//    ui->tableView->setColumnHidden(5,true);
//    ui->tableView->setColumnHidden(9,true);
//    ui->tableView->setColumnHidden(10,true);
//    ui->tableView->setColumnHidden(11,true);
//    ui->tableView->setColumnHidden(12,true);
//    ui->tableView->setColumnHidden(13,true);
//    ui->tableView->setColumnHidden(14,true);
//    ui->tableView->setColumnHidden(15,true);
//    model->setHeaderData( 16, Qt::Horizontal,tr("Ser"));
//    ui->tableView->setColumnWidth(1, 60);
//    ui->tableView->setColumnWidth(2, 80);
//    ui->tableView->setColumnWidth(3, 80);
//    ui->tableView->setColumnWidth(4, 80);
//    ui->tableView->setColumnWidth(6, 80);
//    ui->tableView->setColumnWidth(7, 80);
//    ui->tableView->setColumnWidth(8, 80);
//    ui->tableView->setColumnWidth(16, 10);



#if 0
db.transaction();

QItemSelectionModel *select = ui->tableView->selectionModel();
int selectedRow = select->currentIndex().row();

QSqlQuery query(db);
// 1. 更新插入位置之后的行的 sort_order 值
query.prepare("UPDATE default_testdb SET sort_order = sort_order + 1 WHERE sort_order >= :insertOrder");
query.bindValue(":insertOrder", selectedRow);
if (!query.exec()) {
    qDebug() << "Failed to update sort_order: " << query.lastError();
    return;
}
// 检查是否有选中的行
if (selectedRow >= 0) {
    // 在选中行的下一行插入新行
    int newRow = selectedRow ;
    qDebug() << "newRow: " <<newRow ;
    //ui->tableView->setSortingEnabled(false); // 禁用排序
    model->insertRow(newRow);
    model->setData (model->index(newRow,1),"10");
    model->setData (model->index(newRow,2),"10");
    model->setData (model->index(newRow,3),"10");
    model->setData (model->index(newRow,4),"10");
    model->setData (model->index(newRow,16),newRow);

    // 如果需要，可以为新行设置初始数据

    // 提交所有数据
    model->submitAll();
    //ui->tableView->setSortingEnabled(true);  // 提交后重新启用排序
    // 选中新插入的行（可选）
    QModelIndex newIndex = model->index(newRow, 0); // 选中新行的第一个单元格
    ui->tableView->setCurrentIndex(newIndex);
} else {
// 没有选中的行时，在表格末尾插入
model->insertRow(model->rowCount());
model->submitAll();
}
if (!model->submitAll()) {
    qDebug() << "Submit failed: " << model->lastError().text();
    db.rollback();
}
else
{
db.commit();
}


//void MainWindow::pbDXFimportBut()
//{qDebug()<<"pbDXFimportBut";
//    db.transaction();

//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DXF File"), "", tr("DXF Files (*.dxf)"));

//    if (fileName.isEmpty()) {

//        return;  // 没有选择文件时直接返回
//    }


//    scene->clear();
//    //model->clear();
//    if(model->rowCount()>0){
//        for(int i=0; i< model->rowCount();i++){
//            model->removeRow(i);
//        }
//    }

//    QGraphicsLineItem *line_x = new QGraphicsLineItem(0, 0, 100, 0);
//    QGraphicsLineItem *line_y = new QGraphicsLineItem(0, 0, 0, 100);
//    scene->addItem(line_x);
//    scene->addItem(line_y);

//    DxfHelper dxfHelper;
//    if(dxfHelper.generateDxf(fileName.toStdString().c_str())) {
//        QVector<QVector<QPointF> >dcfData=dxfHelper.dxfPaths_LA;//line_acr_lines  acr01
//        if(dcfData.count()<0 ){return;}
//            qDebug()<<"***paths.count()="<<dcfData.count();

//            double _x=50-dcfData.at(0).at(0).x();
//            double _y=50-(-dcfData.at(0).at(0).y());
//            double o_endX,o_endY;
//            //添加轨迹原点-设定坐标原点为轨迹原点
//            model->insertRow(0); //添加一行
//            o_endX=std::round((dcfData.at(0).at(0).x()+_x) * 1000.0) / 1000.0;
//            o_endY=std::round((-dcfData.at(0).at(0).y()+_y) * 1000.0) / 1000.0;
////            o_endX=dcfData.at(0).at(0).x();
////            o_endY=-dcfData.at(0).at(0).y();
//            QPointF o_start= QPointF(0,0);
//            QPointF o_end= QPointF(o_endX,o_endY);
//            model->setData (model->index(0,1),"line");
//            model->setData (model->index(0,2),0);
//            model->setData (model->index(0,3),0);
//            model->setData (model->index(0,5),o_end.x());
//            model->setData (model->index(0,6),o_end.y());
//            model->setData (model->index(0,8),o_end.x());
//            model->setData (model->index(0,9),o_end.y());


//            line_item *itme =new line_item(o_start,o_end,0,scene);
//            scene->addItem(itme);
//#if 1
//            for (int i=0; i<dcfData.count();i++) {
//                model->insertRow(i+1); //添加一行
//                QVector<QPointF>points=dcfData.at(i);
//                if(points.count()==2)
//                {
//                    double l_startX,l_startY,l_endX,l_endY;
//                    l_startX=std::round((points.at(0).x()+_x) * 1000.0) / 1000.0;
//                    l_startY=std::round((-points.at(0).y()+_y) * 1000.0) / 1000.0;
//                    l_endX=std::round((points.at(1).x()+_x) * 1000.0) / 1000.0;
//                    l_endY=std::round((-points.at(1).y()+_y) * 1000.0) / 1000.0;
////                    l_startX= points.at(0).x();
////                    l_startY=points.at(0).y();
////                    l_endX=points.at(1).x();
////                    l_endY=points.at(1).y();


//                    QPointF start= QPointF(l_startX,l_startY);
//                    QPointF end= QPointF(l_endX,l_endY);
//                    model->setData (model->index(i,1),"line");
//                    model->setData (model->index(0,2),start.x());
//                    model->setData (model->index(0,3),start.y());
//                    model->setData (model->index(0,5),o_end.x());
//                    model->setData (model->index(0,6),o_end.y());
//                    model->setData (model->index(0,8),o_end.x());
//                    model->setData (model->index(0,9),o_end.y());

//                    line_item *itme =new line_item(start,end,i+1,scene);
//                    scene->addItem(itme);
//                }
//                else if(points.count()==3){
//                    double start_x,start_y,end_x,end_y;
//                    double i_start_x=std::round(points.at(0).x() * 1000.0) / 1000.0;
//                    double pre_end_x=std::round(dcfData.at(i-1).at(1).x() * 1000.0) / 1000.0;
//                    qDebug()<<"*****i.start.x"<<i_start_x<<"i-1.end.x="<<pre_end_x;
//                    if(i!=0 && i_start_x== pre_end_x ){
//                        //qDebug()<<"*****=****";
//                        start_x=std::round(points.at(0).x() * 1000.0) / 1000.0;
//                        start_y=std::round(points.at(0).y() * 1000.0) / 1000.0;
//                        end_x=std::round(points.at(1).x() * 1000.0) / 1000.0;
//                        end_y=std::round(points.at(1).y() * 1000.0) / 1000.0;
////                        start_x= points.at(0).x();
////                        start_y=points.at(0).y();
////                        end_x=points.at(1).x();
////                        end_y=points.at(1).y();
//                    }else{
//                        //qDebug()<<"*****!=****";
//                        start_x= points.at(1).x();
//                        start_y=points.at(1).y();
//                        end_x=points.at(0).x();
//                        end_y=points.at(0).y();
//                    }
//                    QPointF start_arc= QPointF(start_x+_x,-start_y+_y);
//                    QPointF end_arc= QPointF(end_x+_x,-end_y+_y);
//                    QPointF trans_arc= QPointF(points.at(2).x()+_x,-points.at(2).y()+_y);

//                    model->setData (model->index(i,1),"arc");
//                    model->setData (model->index(i,2),end_arc.x());
//                    model->setData (model->index(i,3),end_arc.y());


//                    model->setData (model->index(i,5),trans_arc.x());
//                    model->setData (model->index(i,6),trans_arc.y());

//                    model->setData (model->index(i,8),end_arc.x());
//                    model->setData (model->index(i,9),end_arc.y());

//                    qDebug()<<"***arc:*****start_arc="<<start_arc<<"trans_arc="<<trans_arc<<"end_arc="<<end_arc;
//                    arc_item *itme =new arc_item(start_arc,trans_arc,end_arc,i+1,scene);
//                    scene->addItem(itme);
//                }
//                model->submitAll();
//                scene->update();
//                ui->graphicsView->show();
//            }
//#endif


//    }
//    else{
//        qDebug()<<"***dxf file do not open*****";
//        return;
//    }

//    db.commit();
//    //updateSence();
//}
#endif
