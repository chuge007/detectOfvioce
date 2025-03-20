#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DataBase.h"
#include "graphicTool.h"
#include "arc_item.h"
#include "CoustomGraphicsView.h"
#include "dxfhelper.h"

//#include <drw_objects.h>
//#include "libdxfrw.h"
//#include "drw_interface.h"

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
#include <cmath>
#include <iostream>
#include <stdexcept>

#include <QAxObject>
#include <QProcess>
#include <QDir>
#include <QProcessEnvironment>
#include <QWaitCondition>


void MainWindow::initDb()
{
    // 使用用户数据目录存放数据库文件
    QString appDataPath = QCoreApplication::applicationDirPath();
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
        opendb(targetPath);

    }
    else {
        // 不存在则先创建再初始化
        createnewdb(targetPath);
        opendb(targetDb);
    }
    settings=new QSettings(appDataPath+"/settings.ini", QSettings::IniFormat);

    settings->setValue("targetDb", targetDb);
    settings->setValue("targetPath", targetPath);


    // 创建一个表名为 "2d" 的表，包含主键 id，其他字段可以根据需要添加
    QSqlQuery query(db);
    QString createTableSQL =  QString::fromLocal8Bit(R"(
                                                     CREATE TABLE IF NOT EXISTS table2d (
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
    model->setTable("table2d");
    ui->tableView->setModel(model);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();


    if (!db.transaction()) {
        qDebug() << "Failed to start transaction:" << db.lastError().text();
        QMessageBox::critical(this, "Error", "无法开启数据库事务");
        return;
    }
    ui->tableView->clearSpans();
    ui->tableView->setSelectionBehavior( QAbstractItemView::SelectRows ) ;
    ui->tableView->setEditTriggers (QAbstractItemView::NoEditTriggers ) ;
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);  // 第 4 列是 sort_order
    ui->tableView->verticalHeader()->setVisible(false);

    config.loadConfig(appDataPath+"/settings.ini");

    QVariant axleV = settings->value("AxleV");
    QVariant ip = settings->value("ip");
    QVariant port = settings->value("port");

    ui->AxleVelocity_lin->setText(axleV.toString());
    ui->ip_lin->setText(ip.toString());
    ui->port_lin->setText(port.toString());

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , modbusDevice(new QModbusTcpClient(this))
    , config(NdtCfgMachine::getInstance())
{
    ui->setupUi(this);

    initDb();


    scanCtrlHunChuan = new ScanControlHuiChuan();
    scanCtrlHunChuan->Rsettings=settings;
    scanCtrlHunChuan->isUseScanDetect=ui->isUseScanDetect->checkState();


    connect(scanCtrlHunChuan, &ScanControlAbstract::modbusStateChange,this, &MainWindow::modbusStateChange);
    connect(ui->xAdd_but, &QPushButton::pressed, scanCtrlHunChuan, &ScanControlAbstract::on_xAddBtn_pressed);
    connect(ui->xAdd_but, &QPushButton::released, scanCtrlHunChuan, &ScanControlAbstract::on_xAddBtn_released);
    connect(ui->xSub_but, &QPushButton::pressed, scanCtrlHunChuan, &ScanControlAbstract::on_xSubBtn_pressed);
    connect(ui->xSub_but, &QPushButton::released, scanCtrlHunChuan, &ScanControlAbstract::on_xSubBtn_released);
    connect(ui->yAdd_but, &QPushButton::pressed, scanCtrlHunChuan, &ScanControlAbstract::on_yAddBtn_pressed);
    connect(ui->yAdd_but, &QPushButton::released, scanCtrlHunChuan, &ScanControlAbstract::on_yAddBtn_released);
    connect(ui->ySub_but, &QPushButton::pressed, scanCtrlHunChuan, &ScanControlAbstract::on_ySubBtn_pressed);
    connect(ui->ySub_but, &QPushButton::released, scanCtrlHunChuan, &ScanControlAbstract::on_ySubBtn_released);
    connect(ui->zAdd_but, &QPushButton::pressed, scanCtrlHunChuan, &ScanControlAbstract::on_zAddBtn_pressed);
    connect(ui->zAdd_but, &QPushButton::released, scanCtrlHunChuan, &ScanControlAbstract::on_zAddBtn_released);
    connect(ui->zSub_but, &QPushButton::pressed, scanCtrlHunChuan, &ScanControlAbstract::on_zSubBtn_pressed);
    connect(ui->zSub_but, &QPushButton::released, scanCtrlHunChuan, &ScanControlAbstract::on_zSubBtn_released);
    connect(ui->rAdd_but, &QPushButton::pressed, scanCtrlHunChuan, &ScanControlAbstract::on_rAddBtn_pressed);
    connect(ui->rAdd_but, &QPushButton::released, scanCtrlHunChuan, &ScanControlAbstract::on_rAddBtn_released);
    connect(ui->rSub_but, &QPushButton::pressed, scanCtrlHunChuan, &ScanControlAbstract::on_rSubBtn_pressed);
    connect(ui->rSub_but, &QPushButton::released, scanCtrlHunChuan, &ScanControlAbstract::on_rSubBtn_released);

    connect(ui->writeInPLC_but, &QPushButton::clicked, this, &MainWindow::pbWriteInPLC);
    connect(scanCtrlHunChuan, &ScanControlAbstract::positionChange, this, &MainWindow::updatePosition);
    connect(ui->alarmReset_but, &QPushButton::clicked, scanCtrlHunChuan, &ScanControlAbstract::on_alarmResetBtn_clicked);
    connect(ui->startScan_But, &QPushButton::clicked, scanCtrlHunChuan, &ScanControlAbstract::on_startScanBtn_clicked);
    connect(ui->stopScan_but, &QPushButton::clicked, scanCtrlHunChuan, &ScanControlAbstract::on_stopScanBtn_clicked);
    connect(ui->endScan_but, &QPushButton::clicked, scanCtrlHunChuan, &ScanControlAbstract::on_endScanBtn_clicked);

    connect(ui->AxleVelocity_lin, &QLineEdit::editingFinished, this, &MainWindow::PbAxleVelocity_lin);
    connect(ui->setOrigin_but, &QPushButton::clicked, this, &MainWindow::PbSetOrigin);
    connect(ui->insertArcPos_but, &QPushButton::clicked, this, &MainWindow::pbAddArcPos);
    connect(ui->insertLinePos_but, &QPushButton::clicked, this, &MainWindow::pbAddLinePos);
    connect(ui->DXFimport_but, &QPushButton::clicked, this, &MainWindow::pbDXFimportBut);
    connect(ui->creatG_but, &QPushButton::clicked, this, &MainWindow::PbCreatGcode);
    connect(ui->cleanTable_but, &QPushButton::clicked, this, &MainWindow::cleanTable);
    connect(ui->connect_but, &QPushButton::clicked, this, &MainWindow::PbModbusConnectBtn);
    connect(ui->moveToPosition_but, &QPushButton::clicked, this, &MainWindow::PbMoveToPosition);
    connect(ui->isUseScanDetect, &QCheckBox::toggled, this, &MainWindow::isUseScanDetect);

    addRoute = new addRoute_dialog(this);

    connect(addRoute, &addRoute_dialog::addBut_x_pressed, scanCtrlHunChuan, &ScanControlAbstract::on_xAddBtn_pressed);
    connect(addRoute, &addRoute_dialog::addBut_x_released, scanCtrlHunChuan, &ScanControlAbstract::on_xAddBtn_released);
    connect(addRoute, &addRoute_dialog::subBut_x_pressed, scanCtrlHunChuan, &ScanControlAbstract::on_xSubBtn_pressed);
    connect(addRoute, &addRoute_dialog::subBut_x_released, scanCtrlHunChuan, &ScanControlAbstract::on_xSubBtn_released);
    connect(addRoute, &addRoute_dialog::addBut_y_pressed, scanCtrlHunChuan, &ScanControlAbstract::on_yAddBtn_pressed);
    connect(addRoute, &addRoute_dialog::addBut_y_released, scanCtrlHunChuan, &ScanControlAbstract::on_yAddBtn_released);
    connect(addRoute, &addRoute_dialog::subBut_y_pressed, scanCtrlHunChuan, &ScanControlAbstract::on_ySubBtn_pressed);
    connect(addRoute, &addRoute_dialog::subBut_y_released, scanCtrlHunChuan, &ScanControlAbstract::on_ySubBtn_released);
    connect(addRoute, &addRoute_dialog::addBut_z_pressed, scanCtrlHunChuan, &ScanControlAbstract::on_zAddBtn_pressed);
    connect(addRoute, &addRoute_dialog::subBut_z_pressed, scanCtrlHunChuan, &ScanControlAbstract::on_zSubBtn_pressed);
    connect(addRoute, &addRoute_dialog::addBut_z_released, scanCtrlHunChuan, &ScanControlAbstract::on_zAddBtn_released);
    connect(addRoute, &addRoute_dialog::subBut_z_released, scanCtrlHunChuan, &ScanControlAbstract::on_zSubBtn_released);
    connect(addRoute, &addRoute_dialog::subBut_r_pressed, scanCtrlHunChuan, &ScanControlAbstract::on_rSubBtn_pressed);
    connect(addRoute, &addRoute_dialog::subBut_r_released, scanCtrlHunChuan, &ScanControlAbstract::on_rSubBtn_released);


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

    updateSence();
}

MainWindow::~MainWindow()
{


    delete model;
    delete addRoute;
    delete scene;
    delete zomm_gview;
    delete scanCtrlHunChuan;
    delete settings;
    delete ui;

}

void MainWindow::updatePosition(QPointF pos,float cur_r,float cur_z)
{
//        qDebug()<<"updatePosition"<<static_cast<double>(pos.x()-scanCtrlHunChuan->virtualOrigin().x())
//               <<"y"<<static_cast<double>(pos.y()-scanCtrlHunChuan->virtualOrigin().y())
//              <<"z"<<cur_z
//             <<"r"<<cur_r;

    ui->xCurPos_lab->setText(QString::number(static_cast<double>(pos.x()), 'f', 3));
    ui->yCurPos_lab->setText(QString::number(static_cast<double>(pos.y()), 'f', 3));
    ui->zCurPos_lab->setText(QString::number(static_cast<double>(cur_z), 'f', 3));
    ui->rCurPos_lab->setText(QString::number(static_cast<double>(cur_r), 'f', 3));

    addRoute->set_Xcurpos(QString::number(static_cast<double>(pos.x()), 'f', 3));
    addRoute->set_Ycurpos(QString::number(static_cast<double>(pos.y()), 'f', 3));
    addRoute->set_Zcurpos(QString::number(static_cast<double>(cur_z), 'f', 3));
    addRoute->set_Rcurpos(QString::number(static_cast<double>(cur_r), 'f', 3));


}



void MainWindow::updateAddRoute(int arc,int edit,int curRow)
{
    qDebug()<<"updateAddRoute";
    db.transaction();

    QList<QString> curStartPos_list = {ui->xCurPos_lab->text(),ui->yCurPos_lab->text(),ui->zCurPos_lab->text(),ui->rCurPos_lab->text()};
    int route_rowNum=model->rowCount();

    if (addRoute->exec()) {

        if (edit == 1) {
            route_rowNum = route_rowNum-1;
            if (route_rowNum < 0) {
                QMessageBox::information(this," warning ",QString::fromLocal8Bit(" 请先选择要编辑的行 "));
                return;
            }
            QString x0=QString::number(model->data(model->index(route_rowNum, 2), Qt::DisplayRole).toFloat(), 'f', 3);
            QString y0=QString::number(model->data(model->index(route_rowNum, 3), Qt::DisplayRole).toFloat(), 'f', 3);
            QString z0=QString::number(model->data(model->index(route_rowNum, 4), Qt::DisplayRole).toFloat(), 'f', 3);
            QString r0=QString::number(model->data(model->index(route_rowNum, 5), Qt::DisplayRole).toFloat(), 'f', 3);

            curStartPos_list={x0,y0,z0,r0};
            model->removeRow(route_rowNum);
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

        // 插入新行
        if (!model->insertRow(route_rowNum)) {
            qDebug() << "Failed to insert row at" << route_rowNum;
            db.rollback();
            QMessageBox::critical(this, "Error", QString::fromLocal8Bit(" 插入新行失败 "));
            return;
        }

        // 根据 arc 标志判断，设置类型及转换位置信息
        if (arc == 1) {



            model->setData(model->index(route_rowNum, 1), "arc");
            model->setData(model->index(route_rowNum, 2), curStartPos_list.at(0));
            model->setData(model->index(route_rowNum, 3), curStartPos_list.at(1));
            model->setData(model->index(route_rowNum, 4), curStartPos_list.at(2));
            model->setData(model->index(route_rowNum, 5), curStartPos_list.at(3));

            model->setData(model->index(route_rowNum, 6), curTransPos_list.at(0));
            model->setData(model->index(route_rowNum, 7), curTransPos_list.at(1));
            model->setData(model->index(route_rowNum, 8), curTransPos_list.at(2));
            model->setData(model->index(route_rowNum, 9), curTransPos_list.at(3));

            model->setData(model->index(route_rowNum, 10), curEndPos_list.at(0));
            model->setData(model->index(route_rowNum, 11), curEndPos_list.at(1));
            model->setData(model->index(route_rowNum, 12), curEndPos_list.at(2));
            model->setData(model->index(route_rowNum, 13), curEndPos_list.at(3));
            qDebug()<<"***arc:*****start="<< curStartPos_list <<"trans"<<curTransPos_list<<
                      " end"<<curEndPos_list;
        } else {


            model->setData(model->index(route_rowNum, 1), "line");
            model->setData(model->index(route_rowNum, 2), curStartPos_list.at(0));
            model->setData(model->index(route_rowNum, 3), curStartPos_list.at(1));
            model->setData(model->index(route_rowNum, 4), curStartPos_list.at(2));
            model->setData(model->index(route_rowNum, 5), curStartPos_list.at(3));

            model->setData(model->index(route_rowNum, 10), curEndPos_list.at(0));
            model->setData(model->index(route_rowNum, 11), curEndPos_list.at(1));
            model->setData(model->index(route_rowNum, 12), curEndPos_list.at(2));
            model->setData(model->index(route_rowNum, 13), curEndPos_list.at(3));
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

    scanCtrlHunChuan->setModbusTcpIP(ui->ip_lin->text());
    scanCtrlHunChuan->setModbusPort(ui->port_lin->text().toInt());

    scanCtrlHunChuan->on_connectBtn_clicked();


    settings->setValue("ip", ui->ip_lin->text());
    settings->setValue("port", ui->port_lin->text());
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
    if(!scanCtrlHunChuan->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;
    }
    addRoute->update_Ui(1,ui->xCurPos_lab->text(),ui->yCurPos_lab->text(),ui->zCurPos_lab->text(),ui->rCurPos_lab->text(),NULL,NULL,NULL,NULL);
    updateAddRoute(1,0,1);

}

void MainWindow::pbAddLinePos()
{
    if(!scanCtrlHunChuan->modbusState()){
        QMessageBox::warning(nullptr, "error",QString::fromLocal8Bit( " 通讯未连接   "));
        return;
    }
    addRoute->update_Ui(0,ui->xCurPos_lab->text(),ui->yCurPos_lab->text(),ui->zCurPos_lab->text(),ui->rCurPos_lab->text(),NULL,NULL,NULL,NULL);
    updateAddRoute(0,0,1);
}

void MainWindow::on_editPos_but_clicked()
{
    db.transaction();
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
        addRoute->update_Ui(0,xEnd,yEnd,zEnd,rEnd,xTrans,yTrans,zTrans,rTrans);
        updateAddRoute(0,1,0);
    }
    else if(curName=="arc")
    {
        addRoute->update_Ui(1,xEnd,yEnd,zEnd,rEnd,xTrans,yTrans,zTrans,rTrans);
        updateAddRoute(1,1,0);
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


    int ok = QMessageBox::warning(this,tr("删除选中的行!"),tr("你确定删除当前选取中的行吗?"),QMessageBox::Yes,QMessageBox::No);
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


    if(!scanCtrlHunChuan->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;}

    if(!scanCtrlHunChuan->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;}



    int row_count =model->rowCount();
    //int column_cout=model->columnCount();

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



    scanCtrlHunChuan->writeRegisterGroup(3000,modelDates,1);


}



void MainWindow::updateSence()//on_testRout_but_clicked()
{

    scene->clear();
    rownum_itme_lst.clear();
    int row_count =model->rowCount();
    float x0,y0,z0,r0,x1,y1,z1,r1,x2,y2,z2,r2;
    QString type;
    QList<float>list_x0,list_y0,list_r0,list_x1,list_y1,list_r1;
    QList<QString>list_name;
    QPointF start_pos,end_pos,trans_pos ;
    float factor=ui->graphicsView->transform().m11();;


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

            line_item* line = new line_item(start_pos,end_pos,row,scene);
            scene->addItem(line);
            rownum_itme_lst.append(row);
        }else if(type=="arc"){


            arc_item* arc = new arc_item(start_pos,trans_pos,end_pos,row,scene);
            scene->addItem(arc);
            rownum_itme_lst.append(row);

        }
    }


    scene->update();
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



void MainWindow::pbDXFimportBut()
{



    QString fileName = QFileDialog::getOpenFileName(this, tr("Open DXF File"), "", tr("DXF Files (*.dxf)"));

    if (fileName.isEmpty()) {

        return;  // 没有选择文件时直接返回
    }

    db.transaction();
    scene->clear();
    model->removeRows(0, model->rowCount());
    model->submitAll();
    model->select();



    DxfHelper dxfHelper;
    if(dxfHelper.generateDxf(fileName.toStdString().c_str())) {
        QVector<QVector<QPointF> >dcfData=dxfHelper.dxfPaths_LA;//line_acr_lines  acr01
        if(dcfData.count()<=0 ){return;}
        qDebug()<<"***paths.count()="<<dcfData.count();

        double translationX=dcfData.at(0).at(0).x();
        double translationY=dcfData.at(0).at(0).y();

        for (int i=0; i<dcfData.count();i++) {
            model->insertRow(i); //添加一行
            QVector<QPointF>points=dcfData.at(i);
            if(points.count()==2)
            {
                double l_startX,l_startY,l_endX,l_endY;

                l_startX= points.at(0).x()-translationX;
                l_startY=points.at(0).y()-translationY;
                l_endX=points.at(1).x()-translationX;
                l_endY=points.at(1).y()-translationY;


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

                line_item *itme =new line_item(start,end,i+1,scene);
                scene->addItem(itme);

                qDebug()<<"***lin:*****start_x="<<start.x()<<"   start_y"<<start.y()<<"    end_x="<<end.x()<<"end_y:"<<end.y()<<" i "<<i;

            }
            else if(points.count()==3){

                double c_start_x,c_start_y,c_end_x,c_end_y,c_trans_x,c_trans_y;
                c_start_x= points.at(0).x()-translationX;
                c_start_y=points.at(0).y()-translationY;
                c_end_x=points.at(1).x()-translationX;
                c_end_y=points.at(1).y()-translationY;
                c_trans_x=points.at(2).x()-translationX;
                c_trans_y=points.at(2).y()-translationY;
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

                qDebug()<<"***arc:*****start_arc="<<start_arc<<"trans_arc="<<trans_arc<<"end_arc="<<end_arc<<" i "<<i;;
                arc_item *itme =new arc_item(start_arc,trans_arc,end_arc,i+1,scene);
                scene->addItem(itme);
            }

        }


    }
    else{
        qDebug()<<"***dxf file do not open*****";
        return;
    }

    if (!db.commit()) {
        qDebug() << "Failed to commit transaction:" << db.lastError().text();
        QMessageBox::critical(this, "Error", "事务提交失败:" + db.lastError().text());
        db.rollback();
    }

}



void MainWindow::on_setTrajec_start_clicked()
{
    db.transaction();
    bool ok;
    double _x0= ui->traject_x0->text().toDouble(&ok);
    double _y0= ui->traject_y0->text().toDouble(&ok);
    double _z0= ui->traject_z0->text().toDouble(&ok);
    double _r0= ui->traject_r0->text().toDouble(&ok);


    double x2 =model->data(model->index(0, 10), Qt::DisplayRole).toFloat();
    double y2 =model->data(model->index(0, 11), Qt::DisplayRole).toFloat();
    double z2 =model->data(model->index(0, 12), Qt::DisplayRole).toFloat();
    double r2 =model->data(model->index(0, 13), Qt::DisplayRole).toFloat();


    model->setData(model->index(0, 1), "line");
    model->setData(model->index(0, 2), _x0);
    model->setData(model->index(0, 3), _y0);
    model->setData(model->index(0, 4), _z0);
    model->setData(model->index(0, 5), _r0);


    model->setData(model->index(0, 10), x2);
    model->setData(model->index(0, 11), y2);
    model->setData(model->index(0, 12), z2);
    model->setData(model->index(0, 13), r2);

    model->submitAll();

    updateSence();

    db.commit();

    settings->setValue("startX", _x0);
    settings->setValue("startY", _y0);
}


QString MainWindow::generateGCode(/*const QVector<TrackSegment>& segments*/)
{

    QString gCode;
    gCode += "N0 G21\n";//设置为毫米单位\n
    gCode += "N10 G90\n";//绝对坐标模式\n

    int row_count =model->rowCount();
    float x0,y0,z0,r0,x1,y1,z1,r1;
    QString name;
    QPointF start_pos,end_pos,trans_pos ;
    int firstNum=10;
    if(row_count>0){
        for(int i = 0; i < row_count; ++i)
        {
            name=model->data(model->index(i, 1), Qt::DisplayRole).toString();
            x0=model->data(model->index(i, 2), Qt::DisplayRole).toFloat();
            y0=model->data(model->index(i, 3), Qt::DisplayRole).toFloat();
            r0=model->data(model->index(i, 4), Qt::DisplayRole).toFloat();
            x1=model->data(model->index(i, 6), Qt::DisplayRole).toFloat();
            y1=model->data(model->index(i, 7), Qt::DisplayRole).toFloat();
            r1=model->data(model->index(i, 8), Qt::DisplayRole).toFloat();
            //int row= model->data(model->index(i, 16), Qt::DisplayRole).toInt();

            if(i==0){
                start_pos = QPointF( 0,0 );
            }else{
                float start_x=model->data(model->index(i-1, 2), Qt::DisplayRole).toFloat();
                float start_y=model->data(model->index(i-1, 3), Qt::DisplayRole).toFloat();
                start_pos = QPointF( start_x,start_y);
            }
            if(name=="line"){
                end_pos = QPointF( x0,y0 );
                gCode += QString("N%1 G01 X%2 Y%3\n").arg(firstNum).arg(end_pos.x()).arg(end_pos.y());

            }else{
                end_pos = QPointF( x0,y0 );
                trans_pos= QPointF( x1,y1 );
                QPointF A, B, C;
                A=start_pos;
                B=trans_pos;
                C=end_pos;
                double area = (B.x() - A.x()) * (C.y() - A.y()) - (B.y() - A.y()) * (C.x() - A.x());
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
                double det = d1.x() * d2.y() - d1.y() * d2.x();
                if (fabs(det) < 1e-9) {
                    //throw std::runtime_error("计算中垂线交点失败");
                    qDebug()<<"Failed to calculate the intersection point of the perpendicular line in the middle";
                }

                double t = ((M2.x() - M1.x()) * d2.y() - (M2.y() - M1.y()) * d2.x()) / det;
                QPointF center(M1.x() + t * d1.x(), M1.y() + t * d1.y());

                // 计算半径
                //double radius = std::hypot(center.x() - A.x(), center.y() - A.y());

                // 判断旋转方向
                double crossProduct = (B.x() - A.x()) * (C.y() - B.y()) - (B.y() - A.y()) * (C.x() - B.x());
                QString direction = crossProduct > 0 ? "CCW" : "CW";

                double i = center.x() - A.x();
                double j = center.y() - A.y();
                if(direction=="CW"){
                    gCode += QString("N%1 G02 X%2 Y%3 I%4 J%5\n")
                            .arg(firstNum)
                            .arg(C.x())
                            .arg(C.y())
                            .arg(i)
                            .arg(j);
                }
                else if(direction=="CCW"){
                    gCode += QString("N%1 G03 X%2 Y%3 I%4 J%5\n")
                            .arg(firstNum)
                            .arg(C.x())
                            .arg(C.y())
                            .arg(i)
                            .arg(j);
                }

            }
            firstNum+=10;
        }
    }
    gCode += "M30";//程序结束
    return gCode;
}


void MainWindow::exportGCodeToFile(const QString& filePath, const QString& gCode)
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << gCode;
        file.close();
    } else {
        //qDebug() << "无法打开文件：" << filePath;
        qDebug()<<"can not open file:"<<filePath;
    }
}


void MainWindow::PbCreatGcode()
{
    QString filePath = QFileDialog::getSaveFileName(
                this, "导出 G 代码", "", "G Code Files (*.gcode);;All Files (*)");

    if (!filePath.isEmpty()) {
        QString gCode = generateGCode(/*trackSegments*/); // 假设 trackSegments 存储了轨迹
        exportGCodeToFile(filePath, gCode);
        QMessageBox::information(this, "导出成功", "G 代码已成功导出！");
    }
}


void MainWindow::cleanTable(){

    db.transaction();
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

    if(!scanCtrlHunChuan->modbusState()){
        QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 通讯未连接   "));
        return;
    }

    qDebug()<<"AxleV"<<ui->AxleVelocity_lin->text().toFloat();
    scanCtrlHunChuan->on_x_velocity_editingFinished(ui->AxleVelocity_lin->text().toFloat());
    scanCtrlHunChuan->on_y_velocity_editingFinished(ui->AxleVelocity_lin->text().toFloat());
    settings->setValue("AxleV", ui->AxleVelocity_lin->text());
    //QMessageBox::warning(nullptr, "error", QString::fromLocal8Bit(" 速度已设置   "));
    ui->messText_lin->setText(QString::fromLocal8Bit(" 速度已设置   "));


}


void MainWindow::PbImageProcess()
{
    /*
    try {
                // 创建 COM 对象
                QAxObject visionPro("Cognex.VisionPro.Application");
                if (!visionPro.isNull()) {
                    // 调用 VisionPro 方法 (假设方法名为 RunTask)
                    visionPro.dynamicCall("RunTask()");
                    QMessageBox::information(nullptr, "Success", "VisionPro Task Triggered!");
                } else {
                    QMessageBox::warning(nullptr, "Error", "Failed to load VisionPro COM object.");
                }
            } catch (...) {
                QMessageBox::critical(nullptr, "Exception", "An error occurred while accessing VisionPro.");
            }
            */
    /*QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        "Select VisionPro Task File",
        "C:/",
        "VisionPro Files (*.vpp)"
    );

    if (!filePath.isEmpty()) {
        QAxObject visionPro("Cognex.VisionPro.Application");
        visionPro.dynamicCall("Open(const QString&)", filePath);

        // 检查加载状态
        if (visionPro.property("FileLoaded").toBool()) {
            qDebug() << "Task file loaded:" << filePath;
        } else {
            qDebug() << "Failed to load task file.";
        }
    }*/


    //    QString programPath = "C:/Program Files/Cognex/VisionPro/bin/Cognex.VisionPro.QuickBuild.exe";
    //    QString workingDir = "C:/Program Files/Cognex/VisionPro/bin";

    //    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    //    env.insert("PATH", env.value("PATH") + ";C:/Program Files/Cognex/VisionPro/bin");

    //    QProcess process;
    //    process.setProcessEnvironment(env);
    //    process.setWorkingDirectory(workingDir);


    //    // 检查文件是否存在
    //    if (QFile::exists(programPath)) {
    //        // 启动 QuickBuild
    //        if (!QProcess::startDetached(programPath)) {
    //            QMessageBox::warning(nullptr, "Error", "Failed to start VisionPro QuickBuild.");
    //        }
    //    } else {
    //        QMessageBox::critical(nullptr, "Error", "QuickBuild executable not found. Check the path.");
    //    }

}

void MainWindow::pbAscan()
{

    //ui->Scanimage->addWidget(config.getScanWidget(A_SCAN,0));
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
    double z = ui->zCurPos_lab->text().toDouble();
    double r = ui->rCurPos_lab->text().toDouble();

    qDebug()<<"x"<<x<<"y"<<y;
    // 调用运动控制，设置目标位置
    scanCtrlHunChuan->runTargetPosition(x, y, z, r);

}
void MainWindow::PbSetOrigin(){


    scanCtrlHunChuan->on_setOriginBtn_clicked(0,0,true);



}



void MainWindow::isUseScanDetect(bool isUseScanMove){


    scanCtrlHunChuan->isUseScanDetect=scanCtrlHunChuan;


}




//void MainWindow::pbWriteInPLC()
//{


//    if(!scanCtrlHunChuan->modbusState()){
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
//        scanCtrlHunChuan->runTargetPosition(x,y,z,r);
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
//    scanCtrlHunChuan->setModbusTcpIP(arg1);
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
