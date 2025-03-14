#ifndef EXPORT_DB_DIALOG_H
#define EXPORT_DB_DIALOG_H

#include "sqltablemodelalternativebackground.h"
#include "booleandelegate.h"

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>


namespace Ui {
class export_db_dialog;
}

class export_db_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit export_db_dialog(QWidget *parent = 0,QSqlDatabase db=QSqlDatabase(),QString db_name =QString(),QString route_name =QString());
    ~export_db_dialog();

    QString get_db_name();

private slots:


    void on_cancel_but_clicked();

    void on_export_but_clicked();

    void on_filter_but_clicked();

    void on_all_checkBox_clicked();

    void on_filter_radioButton_clicked();

    void on_radioButton_clicked();
    void export_information();

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::export_db_dialog *ui;
    SqlTableModelAlternativeBackground *model;
    BooleanDelegate *b_delegate;
    QList <QDate> date_lst;
    QList <QString> user_name_lst;
    QList <QString> route_name_lst;
    QList <QString> date_value_lst;
    QSqlDatabase current_db;
    QString current_tested_db,current_route_name,current_db_name;

};

#endif // EXPORT_DB_DIALOG_H
