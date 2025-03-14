#ifndef NEWTEST_DIALOG_H
#define NEWTEST_DIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QTreeWidgetItem>

namespace Ui {
class Newtest_Dialog;
}

class Newtest_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Newtest_Dialog(QWidget *parent = 0,QSqlDatabase db=QSqlDatabase(),QString db_name= QString());
    ~Newtest_Dialog();
    QString get_route_name();
    QString get_part_name();
    QString get_group_name();
    void mkeyPressEvent(QKeyEvent *event){keyPressEvent(event);}
private slots:

    
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_gp_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::Newtest_Dialog *ui;
    QString current_part;
    QString current_group;
    QString current_route;
    void init_interface();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // NEWTEST_DIALOG_H
