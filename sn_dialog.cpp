#include "sn_dialog.h"
#include "ui_sn_dialog.h"
#include <QKeyEvent>
#include <QDebug>

SN_Dialog::SN_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SN_Dialog)
{
    ui->setupUi(this);

    connect(ui->b9,SIGNAL(clicked()),SLOT(press()));
    connect(ui->b8,SIGNAL(clicked()),SLOT(press()));
    connect(ui->b7,SIGNAL(clicked()),SLOT(press()));
    connect(ui->b6,SIGNAL(clicked()),SLOT(press()));
    connect(ui->b5,SIGNAL(clicked()),SLOT(press()));
    connect(ui->b4,SIGNAL(clicked()),SLOT(press()));
    connect(ui->b3,SIGNAL(clicked()),SLOT(press()));
    connect(ui->b2,SIGNAL(clicked()),SLOT(press()));
    connect(ui->b1,SIGNAL(clicked()),SLOT(press()));
    connect(ui->b0,SIGNAL(clicked()),SLOT(press()));
    connect(ui->bdel,SIGNAL(clicked()),SLOT(press()));
    connect(ui->bback,SIGNAL(clicked()),SLOT(press()));

}

SN_Dialog::~SN_Dialog()
{
    delete ui;
}

QString SN_Dialog::get_SN()
{
    QString SN_name =ui->SN_lineEdit->text();
    return SN_name;
}
void SN_Dialog::on_ok_but_clicked()
{
    accept();
}

void SN_Dialog::on_cancel_but_clicked()
{
    reject();
}

void SN_Dialog::press(void)
{
    QPushButton* button = dynamic_cast<QPushButton*>(sender());
    QString bs = button->text();
    bs.replace('&',""); /* fix some weirdness */
    button->setText(bs);

    bool press_button = true;
    bool do_op = false;

    if (button->text() == "DEL") {
        press_button = false;
        ui->SN_lineEdit->setText("");
    }
    if (button->text() == "BACK")
    {
        press_button = false;
        if (ui->SN_lineEdit->text() != "")
        {
            ui->SN_lineEdit->setText(ui->SN_lineEdit->text().mid(0,ui->SN_lineEdit->text().length()-1));
        }
    }
    if (press_button)
    {
        ui->SN_lineEdit->setText(ui->SN_lineEdit->text()+button->text());
    }
    if (do_op)
    {
        ui->SN_lineEdit->setText("");
    }

    //qDebug() << button->text();
}
void SN_Dialog::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"keypress****SN_Dialog";
    if(event->key()==Qt::Key_F9)
    {

        ui->ok_but->click();
        qDebug("keypress****otherkey=%x",event->key());
    }

}
