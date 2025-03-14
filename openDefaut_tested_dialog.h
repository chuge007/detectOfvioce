#ifndef OPENDEFAUT_TESTED_DIALOG_H
#define OPENDEFAUT_TESTED_DIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QTreeWidgetItem>

namespace Ui {
class openDefaut_tested_dialog;
}

class openDefaut_tested_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit openDefaut_tested_dialog(QWidget *parent = 0,QSqlDatabase db=QSqlDatabase(),QString def_routename= QString() );//,QString test_route_name
    ~openDefaut_tested_dialog();
    QString get_route_name();
    void list_testdata_table();
   QString current_test_route_name;
   // QString get_group_name();
   void mkeyPressEvent(QKeyEvent *event){keyPressEvent(event);}

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

  //  void on_gp_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_route_tableWidget_clicked(const QModelIndex &index);

    void on_pushButton_del_clicked();

private:
    Ui::openDefaut_tested_dialog *ui;
    QSqlDatabase opendb;
    QString get_def_routename;

  //  QString current_part;
  //  QString current_group;
protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // OPENDEFAUT_TESTED_DIALOG_H
