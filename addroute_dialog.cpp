#include "addroute_dialog.h"
#include "ui_addroute_dialog.h"
#include <QDebug>
#include <QList>
#include<QMessageBox>
addRoute_dialog::addRoute_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addRoute_dialog)
{
    ui->setupUi(this);

    connect(ui->xAddBtn_2, &QPushButton::pressed, this, &addRoute_dialog::addBut_x_pressed);
    connect(ui->xSubBtn_2, &QPushButton::pressed, this, &addRoute_dialog::subBut_x_pressed);
    connect(ui->yAddBtn_2, &QPushButton::pressed, this, &addRoute_dialog::addBut_y_pressed);
    connect(ui->ySubBtn_2, &QPushButton::pressed, this, &addRoute_dialog::subBut_y_pressed);
    connect(ui->rAddBtn_2, &QPushButton::pressed, this, &addRoute_dialog::addBut_r_pressed);
    connect(ui->rSubBtn_2, &QPushButton::pressed, this, &addRoute_dialog::subBut_r_pressed);
    connect(ui->zAddBtn_2, &QPushButton::pressed, this, &addRoute_dialog::addBut_z_pressed);
    connect(ui->zSubBtn_2, &QPushButton::pressed, this, &addRoute_dialog::subBut_z_pressed);
    connect(ui->xAddBtn_2, &QPushButton::released, this, &addRoute_dialog::addBut_x_released);
    connect(ui->xSubBtn_2, &QPushButton::released, this, &addRoute_dialog::subBut_x_released);
    connect(ui->yAddBtn_2, &QPushButton::released, this, &addRoute_dialog::addBut_y_released);
    connect(ui->ySubBtn_2, &QPushButton::released, this, &addRoute_dialog::subBut_y_released);
    connect(ui->rAddBtn_2, &QPushButton::released, this, &addRoute_dialog::addBut_r_released);
    connect(ui->rSubBtn_2, &QPushButton::released, this, &addRoute_dialog::subBut_r_released);
    connect(ui->zAddBtn_2, &QPushButton::released, this, &addRoute_dialog::addBut_z_released);
    connect(ui->zSubBtn_2, &QPushButton::released, this, &addRoute_dialog::subBut_z_released);
    connect(ui->setCurposToEnd_but, &QPushButton::released, this, &addRoute_dialog::pbSetCurposToEndPos);
    connect(ui->setCursPosToTrans_but, &QPushButton::released, this, &addRoute_dialog::pbSetCurposToTransPos);



}

addRoute_dialog::~addRoute_dialog()
{
    delete ui;
}

void addRoute_dialog::on_pushButton_clicked()
{
//    if(){
//        QMessageBox::information(this," 提示 "," 有至少两个点重合，请检查 ");return;}

    accept();
}

void addRoute_dialog::closeEvent(QCloseEvent *event)
{

    ui->xCurPos->clear();
    ui->yCurPos->clear();
    ui->zCurPos->clear();
    ui->rCurPos->clear();
    // …… 根据需要重置其它控件

    // 不真正关闭，而是隐藏对话框
    event->ignore();
    hide();
}

void addRoute_dialog::on_pushButton_2_clicked()
{
    reject();
}




QList <QString> addRoute_dialog::getStartPos()
{
    QString cur_xEnd=ui->xCurPos->text();
    QString cur_yEnd=ui->yCurPos->text();
    QString cur_zEnd=ui->zCurPos->text();
    QString cur_rEnd=ui->rCurPos->text();
    QList<QString> Pos_list; // 创建一个存储字符串;
    Pos_list.append(cur_xEnd);
    Pos_list.append(cur_yEnd);
    Pos_list.append(cur_zEnd);
    Pos_list.append(cur_rEnd);
    return Pos_list;
}

QList <QString> addRoute_dialog::getEndPos()
{

    QString cur_xEnd=ui->xEnd->text();
    QString cur_yEnd=ui->yEnd->text();
    QString cur_zEnd=ui->zEnd->text();
    QString cur_rEnd=ui->rEnd->text();
    QList<QString> Pos_list; // 创建一个存储字符串;
    Pos_list.append(cur_xEnd);
    Pos_list.append(cur_yEnd);
    Pos_list.append(cur_zEnd);
    Pos_list.append(cur_rEnd);
    return Pos_list;
}


QList <QString> addRoute_dialog::getTransPos()
{

    QString cur_xTrans=ui->xTrans->text();
    QString cur_yTrans=ui->yTrans->text();
    QString cur_zTrans=ui->zTrans->text();
    QString cur_rTrans=ui->rTrans->text();
    QList<QString> Pos_list; // 创建一个存储字符串;
    Pos_list.append(cur_xTrans);
    Pos_list.append(cur_yTrans);
    Pos_list.append(cur_zTrans);
    Pos_list.append(cur_rTrans);
    return Pos_list;
}

void addRoute_dialog::pbSetCurposToEndPos()
{
    ui->xEnd->setText(ui->xCurPos->text());
    ui->yEnd->setText(ui->yCurPos->text());
    ui->zEnd->setText(ui->zCurPos->text());
    ui->rEnd->setText(ui->rCurPos->text());
}

void addRoute_dialog::set_Xcurpos(QString curX)
{
    ui->xCurPos->setText(curX);
}

void addRoute_dialog::set_Ycurpos(QString curY)
{
    ui->yCurPos->setText(curY);
}

void addRoute_dialog::set_Rcurpos(QString curR)
{
    ui->rCurPos->setText(curR);
}


void addRoute_dialog::set_Zcurpos(QString curZ)
{
    ui->zCurPos->setText(curZ);
}


void addRoute_dialog::pbSetCurposToTransPos()
{
    ui->xTrans->setText(ui->xCurPos->text());
    ui->yTrans->setText(ui->yCurPos->text());
    ui->zTrans->setText(ui->zCurPos->text());
    ui->rTrans->setText(ui->rCurPos->text());
}

void addRoute_dialog::update_Ui(int state,QString xEnd,QString yEnd,QString zEnd,QString rEnd,QString xTrans,QString yTrans,QString zTrans,QString rTrans)
{


    if(state==0)
    {
        ui->frame_trans->hide();
        ui->setCursPosToTrans_but->hide();
        ui->xEnd->setText(xEnd);
        ui->yEnd->setText(yEnd);
        ui->zEnd->setText(zEnd);
        ui->rEnd->setText(rEnd);

    }
    else if (state==1) {
        ui->frame_trans->show();
        ui->setCursPosToTrans_but->show();
        ui->xEnd->setText(xEnd);
        ui->yEnd->setText(yEnd);
        ui->rEnd->setText(rEnd);
        ui->zEnd->setText(zEnd);
        ui->xTrans->setText(xTrans);
        ui->yTrans->setText(yTrans);
        ui->zTrans->setText(zTrans);
        ui->rTrans->setText(rTrans);
    }
}
