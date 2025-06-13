#include "gcodemodulation.h"
#include "ui_gcodemodulation.h"

gCodeModulation::gCodeModulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gCodeModulation)
{
    ui->setupUi(this);
}

gCodeModulation::~gCodeModulation()
{
    delete ui;
}
