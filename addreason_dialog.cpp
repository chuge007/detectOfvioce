#include "addreason_dialog.h"
#include "ui_addreason_dialog.h"

addreason_dialog::addreason_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addreason_dialog)
{
    ui->setupUi(this);
}

addreason_dialog::~addreason_dialog()
{
    delete ui;
}

QString addreason_dialog::GetMethod()
{
    return ui->methodLine->text() ;
}

void addreason_dialog::SetMethod(QString mt)
{
    ui->methodLine->setText(mt);
}
void addreason_dialog::SetDescription(QString ds)
{

    ui->des_textEdit->setText(ds);
}


QString addreason_dialog::GetDescription()
{
    return ui->des_textEdit->toPlainText(); ;
}

void addreason_dialog::on_applyButton_clicked()
{
    accept();
}

void addreason_dialog::on_cancelButton_clicked()
{
    reject();
}
