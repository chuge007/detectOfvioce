#include "ascan.h"
#include "ui_ascan.h"

ascan::ascan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ascan)
{
    ui->setupUi(this);
}

ascan::~ascan()
{
    delete ui;
}
