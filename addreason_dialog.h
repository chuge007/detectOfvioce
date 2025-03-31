#ifndef ADDREASON_DIALOG_H
#define ADDREASON_DIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class addreason_dialog;
}

class addreason_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit addreason_dialog(QWidget *parent = 0);
    ~addreason_dialog();
    QString  GetMethod() ;
    QString  GetDescription() ;
    void SetMethod(QString mt) ;
    void SetDescription(QString ds) ;

private slots:
    void on_applyButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::addreason_dialog *ui;
    //QSqlTableModel *pr_model;

};

#endif // ADDREASON_DIALOG_H
