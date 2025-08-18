#include "addroute_dialog.h"
#include "ui_addroute_dialog.h"
#include "widgetDefin/setStyleSheet.h"

#include <QDebug>
#include <QList>
#include<QMessageBox>
#include <QCloseEvent>
#include <QDoubleValidator>

addRoute_dialog::addRoute_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addRoute_dialog)
{
    ui->setupUi(this);

    connect(ui->RxAdd_btn, &QPushButton::pressed, this, &addRoute_dialog::addBut_x_pressed);
    connect(ui->RxSub_btn, &QPushButton::pressed, this, &addRoute_dialog::subBut_x_pressed);
    connect(ui->RyAdd_btn, &QPushButton::pressed, this, &addRoute_dialog::addBut_y_pressed);
    connect(ui->RySub_btn, &QPushButton::pressed, this, &addRoute_dialog::subBut_y_pressed);
    connect(ui->RrAdd_btn, &QPushButton::pressed, this, &addRoute_dialog::addBut_r_pressed);
    connect(ui->RrSub_btn, &QPushButton::pressed, this, &addRoute_dialog::subBut_r_pressed);
    connect(ui->RzAdd_btn, &QPushButton::pressed, this, &addRoute_dialog::addBut_z_pressed);
    connect(ui->RzSub_Btn, &QPushButton::pressed, this, &addRoute_dialog::subBut_z_pressed);
    connect(ui->RxAdd_btn, &QPushButton::released, this, &addRoute_dialog::addBut_x_released);
    connect(ui->RxSub_btn, &QPushButton::released, this, &addRoute_dialog::subBut_x_released);
    connect(ui->RyAdd_btn, &QPushButton::released, this, &addRoute_dialog::addBut_y_released);
    connect(ui->RySub_btn, &QPushButton::released, this, &addRoute_dialog::subBut_y_released);
    connect(ui->RrAdd_btn, &QPushButton::released, this, &addRoute_dialog::addBut_r_released);
    connect(ui->RrSub_btn, &QPushButton::released, this, &addRoute_dialog::subBut_r_released);
    connect(ui->RzAdd_btn, &QPushButton::released, this, &addRoute_dialog::addBut_z_released);
    connect(ui->RzSub_Btn, &QPushButton::released, this, &addRoute_dialog::subBut_z_released);
    connect(ui->setCurposToEnd_but, &QPushButton::pressed, this, &addRoute_dialog::pbSetCurposToEndPos);
    connect(ui->setCursPosToTrans_but, &QPushButton::pressed, this, &addRoute_dialog::pbSetCurposToTransPos);
    connect(ui->setCurposToStart_but, &QPushButton::pressed, this, &addRoute_dialog::pbSetCurposToStartPos);
    connect(ui->pb_accept, &QPushButton::clicked, this, &addRoute_dialog::pB_accept);
    connect(ui->pb_reject, &QPushButton::clicked, this, &addRoute_dialog::pB_reject);


    QDoubleValidator *xStart_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    xStart_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->xStart_lin->setValidator(xStart_lin);

    QDoubleValidator *yStart_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    yStart_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->yStart_lin->setValidator(yStart_lin);

    QDoubleValidator *zStart_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    zStart_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->zStart_lin->setValidator(zStart_lin);

    QDoubleValidator *rStart_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    rStart_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->rStart_lin->setValidator(rStart_lin);



    QDoubleValidator *xTrans_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    xTrans_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->xTrans_lin->setValidator(xTrans_lin);

    QDoubleValidator *yTrans_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    yTrans_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->yTrans_lin->setValidator(yTrans_lin);

    QDoubleValidator *zTrans_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    zTrans_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->zTrans_lin->setValidator(zTrans_lin);

    QDoubleValidator *rTrans_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    rTrans_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->rTrans_lin->setValidator(rTrans_lin);



    QDoubleValidator *xEnd_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    xEnd_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->xEnd_lin->setValidator(xEnd_lin);

    QDoubleValidator *yEnd_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    yEnd_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->yEnd_lin->setValidator(yEnd_lin);

    QDoubleValidator *zEnd_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    zEnd_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->zEnd_lin->setValidator(zEnd_lin);

    QDoubleValidator *rEnd_lin = new QDoubleValidator(0, 9999, 3, this);  // 0~9999，最多2位小数
    rEnd_lin->setNotation(QDoubleValidator::StandardNotation);
    ui->rEnd_lin->setValidator(rEnd_lin);

    this->setStyleSheet(styleMcSheet);  // 在构造函数里给当前窗口用

}

addRoute_dialog::~addRoute_dialog()
{
    delete ui;
}

void addRoute_dialog::pB_accept()
{

    qDebug()<<"accept";
    accept();
}

void addRoute_dialog::closeEvent(QCloseEvent *event)
{

    ui->xCurPos_lab->clear();
    ui->yCurPos_lab->clear();
    ui->zCurPos_lab->clear();
    ui->rCurPos_lab->clear();
    // …… 根据需要重置其它控件

    // 不真正关闭，而是隐藏对话框
    isReject=true;
    isOpen=false;
    event->ignore();
    hide();
}

void addRoute_dialog::pB_reject()
{
    qDebug()<<"reject";
    isReject=true;
    reject();
}




QList <QString> addRoute_dialog::getStartPos()
{
    QString cur_xEnd=ui->xStart_lin->text();
    QString cur_yEnd=ui->yStart_lin->text();
    QString cur_zEnd=ui->zStart_lin->text();
    QString cur_rEnd=ui->rStart_lin->text();
    QList<QString> Pos_list; // 创建一个存储字符串;
    Pos_list.append(cur_xEnd);
    Pos_list.append(cur_yEnd);
    Pos_list.append(cur_zEnd);
    Pos_list.append(cur_rEnd);
    return Pos_list;
}

QList <QString> addRoute_dialog::getEndPos()
{

    QString cur_xEnd=ui->xEnd_lin->text();
    QString cur_yEnd=ui->yEnd_lin->text();
    QString cur_zEnd=ui->zEnd_lin->text();
    QString cur_rEnd=ui->rEnd_lin->text();
    QList<QString> Pos_list; // 创建一个存储字符串;
    Pos_list.append(cur_xEnd);
    Pos_list.append(cur_yEnd);
    Pos_list.append(cur_zEnd);
    Pos_list.append(cur_rEnd);
    return Pos_list;
}


QList <QString> addRoute_dialog::getTransPos()
{

    QString cur_xTrans_lin=ui->xTrans_lin->text();
    QString cur_yTrans_lin=ui->yTrans_lin->text();
    QString cur_zTrans_lin=ui->zTrans_lin->text();
    QString cur_rTrans_lin=ui->rTrans_lin->text();
    QList<QString> Pos_list; // 创建一个存储字符串;
    Pos_list.append(cur_xTrans_lin);
    Pos_list.append(cur_yTrans_lin);
    Pos_list.append(cur_zTrans_lin);
    Pos_list.append(cur_rTrans_lin);
    return Pos_list;
}

void addRoute_dialog::pbSetCurposToEndPos()
{
    ui->xEnd_lin->setText(ui->xCurPos_lab->text());
    ui->yEnd_lin->setText(ui->yCurPos_lab->text());
    ui->zEnd_lin->setText(ui->zCurPos_lab->text());
    ui->rEnd_lin->setText(ui->rCurPos_lab->text());
}

void addRoute_dialog::pbSetCurposToStartPos()
{
    ui->xStart_lin->setText(ui->xCurPos_lab->text());
    ui->yStart_lin->setText(ui->yCurPos_lab->text());
    ui->zStart_lin->setText(ui->zCurPos_lab->text());
    ui->rStart_lin->setText(ui->rCurPos_lab->text());
}

void addRoute_dialog::set_Xcurpos(QString curX)
{
    ui->xCurPos_lab->setText(curX);
}

void addRoute_dialog::set_Ycurpos(QString curY)
{
    ui->yCurPos_lab->setText(curY);
}

void addRoute_dialog::set_Rcurpos(QString curR)
{
    ui->rCurPos_lab->setText(curR);
}


void addRoute_dialog::set_Zcurpos(QString curZ)
{
    ui->zCurPos_lab->setText(curZ);
}


void addRoute_dialog::pbSetCurposToTransPos()
{
    ui->xTrans_lin->setText(ui->xCurPos_lab->text());
    ui->yTrans_lin->setText(ui->yCurPos_lab->text());
    ui->zTrans_lin->setText(ui->zCurPos_lab->text());
    ui->rTrans_lin->setText(ui->rCurPos_lab->text());
}

void addRoute_dialog::pbSetStartPos(QString x,QString y,QString z,QString r)
{
    ui->xStart_lin->setText(x);
    ui->yStart_lin->setText(y);
    ui->zStart_lin->setText(z);
    ui->rStart_lin->setText(r);
}

void addRoute_dialog::update_Ui(int state,QString xEnd,QString yEnd,QString zEnd,QString rEnd,QString xTrans_lin,QString yTrans_lin,QString zTrans_lin,QString rTrans_lin)
{


    if(state==0)
    {
        ui->frame_trans->hide();
        ui->setCursPosToTrans_but->hide();
        ui->xEnd_lin->setText(xEnd);
        ui->yEnd_lin->setText(yEnd);
        ui->zEnd_lin->setText(zEnd);
        ui->rEnd_lin->setText(rEnd);

    }
    else if (state==1) {
        ui->frame_trans->show();
        ui->setCursPosToTrans_but->show();
        ui->xEnd_lin->setText(xEnd);
        ui->yEnd_lin->setText(yEnd);
        ui->rEnd_lin->setText(rEnd);
        ui->zEnd_lin->setText(zEnd);
        ui->xTrans_lin->setText(xTrans_lin);
        ui->yTrans_lin->setText(yTrans_lin);
        ui->zTrans_lin->setText(zTrans_lin);
        ui->rTrans_lin->setText(rTrans_lin);
    }
}
