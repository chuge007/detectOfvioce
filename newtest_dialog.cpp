#include "newtest_dialog.h"
#include "ui_newtest_dialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QTime>
#include <QKeyEvent>

Newtest_Dialog::Newtest_Dialog(QWidget *parent, QSqlDatabase db,QString db_name) :
    QDialog(parent),
    ui(new Ui::Newtest_Dialog)
{
    ui->setupUi(this);
    ui->gp_treeWidget->clear();
    ui->route_tableWidget->clear();
    qDebug()<<"111111"<<"db_name"<<db_name<<"db"<<db.tables().count();
#if 0
    QSettings settings_gp("nextspot", "group_new");   // 写入与读取的 settings 要一致
    QString recent_group =settings_gp.value("recent_group_new").toString();
    QSettings settings_pt("nextspot", "part_new");   // 写入与读取的 settings 要一致
    QString recent_part =settings_pt.value("recent_part_new").toString();
    QSettings settings_route("nextspot", "route_new");   // 写入与读取的 settings 要一致
    QString recent_route =settings_route.value("recent_route_new").toString();
    current_route = recent_route;
qDebug()<<"rencent_route="<<recent_route;
    if(!recent_group.isEmpty() && !recent_part.isEmpty()&& !recent_route.isEmpty())
    {
        qDebug()<<"no  isempty=";
        QTreeWidgetItem * gpall_item = new QTreeWidgetItem(QStringList()<<db_name);
        gpall_item->setSizeHint(0,QSize(100,25));
        ui->gp_treeWidget->addTopLevelItem(gpall_item);
        QSqlQuery querygp(db);
        QSqlQuery querypt(db);
        querygp.exec("select DISTINCT wdgroup  from spot");
        QString gpstr,ptstr;
        while(querygp.next())
        {
            //qDebug() <<  querygp.value(0).toString();
            gpstr = querygp.value(0).toString();
            QTreeWidgetItem * gpitem = new QTreeWidgetItem(QStringList()<<gpstr);
            gpitem->setIcon(0,QIcon("://img/Folder.png"));
            gpitem->setSizeHint(0,QSize(100,25));
            gpall_item->addChild(gpitem);
            querypt.exec(tr("select DISTINCT wdpart from spot  WHERE wdgroup='%1'").arg(gpstr));
            while(querypt.next())
            {
                  ptstr = querypt.value(0).toString();
                  QTreeWidgetItem * ptitem = new QTreeWidgetItem(QStringList()<<ptstr);
                  ptitem->setIcon(0,QIcon("://img/part_A.png"));
                  ptitem->setSizeHint(0,QSize(100,25));
                  gpitem->addChild(ptitem);
                  if(ptstr==recent_part && gpstr==recent_group)
                  {
                      ui->gp_treeWidget->setCurrentItem(ptitem,0);
                  }
            }
        }
        ui->gp_treeWidget->expandAll();

        QList<QString> db_namelst;
        QSqlQuery  query_routelst;
        if( query_routelst.exec(QObject::tr("select * from rout_list where weldgroup ='%1' and weldpart ='%2' ").arg(recent_group).arg(recent_part)))
        {
            while( query_routelst.next() )
            {
                QString db_name = query_routelst.value(4).toString();
                db_namelst.append(db_name);
            }
        }
        ui->route_tableWidget->setRowCount(db_namelst.count());
        ui->route_tableWidget->setColumnCount(1);
        for(int i=0; i<db_namelst.count(); i++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(db_namelst.at(i));
            ui->route_tableWidget->setItem(i ,0,item );
        }

        for(int i=0;i<ui->route_tableWidget->rowCount();i++)
        {
            //qDebug()<<"rencent_route="<<recent_route<<"route_tableWidget.item.text="<<ui->route_tableWidget->item(i,0)->text()<<"i="<<i;
            if(ui->route_tableWidget->item(i,0)->text()==recent_route)
            {
                ui->route_tableWidget->selectRow(i);
                ui->route_tableWidget->setFocus();
            }
            break;
        }
        current_group=recent_group;
        current_part =recent_part;
    }
    else
#endif
    {
        qDebug()<<"isempty";
        QList<QString> gp_lst;
        QList<QString> pt_lst;
        QTreeWidgetItem * gpall_item = new QTreeWidgetItem(QStringList()<<db_name);
        gpall_item->setSizeHint(0,QSize(100,25));
        ui->gp_treeWidget->addTopLevelItem(gpall_item);
        QSqlQuery querygp(db);
        QSqlQuery querypt(db);
        querygp.exec("select DISTINCT wdgroup  from spot");
        QString gpstr,ptstr;
        while(querygp.next())
        {
            //qDebug() <<  querygp.value(0).toString();
            gpstr = querygp.value(0).toString();
            gp_lst.append(gpstr);
            QTreeWidgetItem * gpitem = new QTreeWidgetItem(QStringList()<<gpstr);
            gpitem->setIcon(0,QIcon("://img/Folder.png"));
            gpitem->setSizeHint(0,QSize(100,25));
            gpall_item->addChild(gpitem);
            querypt.exec(tr("select DISTINCT wdpart from spot  WHERE wdgroup='%1'").arg(gpstr));
            if(querypt.next())
            {
                ptstr = querypt.value(0).toString();
                QTreeWidgetItem * ptitem = new QTreeWidgetItem(QStringList()<<ptstr);
                ptitem->setIcon(0,QIcon("://img/part_A.png"));
                ptitem->setSizeHint(0,QSize(100,25));
                gpitem->addChild(ptitem);
                ui->gp_treeWidget->setCurrentItem(ptitem,0);
                pt_lst.append(ptstr);
            }
            while(querypt.next())
            {
                  ptstr = querypt.value(0).toString();
                  pt_lst.append(ptstr);
                  QTreeWidgetItem * ptitem = new QTreeWidgetItem(QStringList()<<ptstr);
                  ptitem->setIcon(0,QIcon("://img/part_A.png"));
                  ptitem->setSizeHint(0,QSize(100,25));
                  gpitem->addChild(ptitem);
            }
        }
        ui->gp_treeWidget->expandAll();

#if 1
        QList<QString> db_namelst;//qDebug()<<"222######"<<gp_lst.count();
        if(gp_lst.count()>0 && pt_lst.count()>0)
        {
            current_group=gp_lst.at(0);
            current_part =pt_lst.at(0);
            QSqlQuery  query_routelst;qDebug()<<"current_group="<<current_group<<"current_part="<<current_part;
            if( query_routelst.exec(QObject::tr("select * from rout_list where weldgroup ='%1' and weldpart ='%2' ").arg(current_group).arg(current_part)))
            {
                while( query_routelst.next() )
                {
                    QString db_name = query_routelst.value(4).toString();
                    db_namelst.append(db_name);
                }
            }

            ui->route_tableWidget->setRowCount(db_namelst.count());
            ui->route_tableWidget->setColumnCount(1);
            for(int i=0; i<db_namelst.count(); i++)
            {

                ui->route_tableWidget->setItem(i ,0,new QTableWidgetItem(db_namelst.at(i)) );
            }
            if(ui->route_tableWidget->rowCount()>0)
            {
                ui->route_tableWidget->selectRow(0);
            }
        }

        //current_route =ui->route_tableWidget->item(0,0)->text();
#endif

    }
}

Newtest_Dialog::~Newtest_Dialog()
{
    delete ui;
}


void Newtest_Dialog::on_pushButton_clicked()
{
    QTableWidgetItem* item =ui->route_tableWidget->currentItem();
    if(item)
    {
        QString part =ui->gp_treeWidget->currentItem()->text(0);
        QString group =ui->gp_treeWidget->currentItem()->parent()->text(0);
        QString route =ui->route_tableWidget->currentItem()->text();qDebug()<<"*****route="<<route;
#if 0
        QSettings settings_gp("nextspot", "group_new");   // 写入与读取的 settings 要一致
        settings_gp.setValue("recent_group_new", group);
        QSettings settings_pt("nextspot", "part_new");   // 写入与读取的 settings 要一致
        settings_pt.setValue("recent_part_new", part);
        QSettings settings_route("nextspot", "route_new");   // 写入与读取的 settings 要一致
        settings_route.setValue("recent_route_new", route);
#endif

        accept();
    }
    else
    {
        reject();
        //QMessageBox::information(NULL, QString("New"), QString("No route select!"));
    }

}

void Newtest_Dialog::on_pushButton_2_clicked()
{
    reject();
}

void Newtest_Dialog::on_gp_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    if( (item->parent()== NULL)){
    }
    else
    {
        if ((item->parent()->parent()== NULL)){
            ui->route_tableWidget->clear();
            ui->route_tableWidget->setRowCount(0);
        }
        else
        {
            current_part = item->text(0);
            current_group = item->parent()->text(0);
            QList<QString> db_namelst;
            QSqlQuery  query_routelst;
            if( query_routelst.exec(QObject::tr("select * from rout_list where weldgroup ='%1' and weldpart ='%2' ").arg(current_group).arg(current_part)))
            {
                while( query_routelst.next() )
                {
                    QString db_name = query_routelst.value(4).toString();
                    db_namelst.append(db_name);
                }
            }
            ui->route_tableWidget->setRowCount(db_namelst.count());
            ui->route_tableWidget->setColumnCount(1);
            for(int i=0; i<db_namelst.count(); i++)
            {
                ui->route_tableWidget->setItem(i ,0,new QTableWidgetItem(db_namelst.at(i)) );
            }
        }
    }
}

QString  Newtest_Dialog::get_route_name()
{
    QString route_name;
    QList<QTableWidgetItem*>items = ui->route_tableWidget->selectedItems();
    if(items.count() >0)
    {
        QTableWidgetItem* item =ui->route_tableWidget->currentItem();
        QString name = item->text();
        QStringList name_lst;
        name_lst << current_group << current_part<<name ;
        route_name = name_lst.join(",");
    }
    else
    {
        QStringList name_lst;
        name_lst << current_group << current_part<<current_route ;
        route_name = name_lst.join(",");
    }
    return route_name;
}

QString  Newtest_Dialog::get_part_name()
{
    return current_part;
}

QString  Newtest_Dialog::get_group_name()
{
    return current_group;
}

void Newtest_Dialog::init_interface()
{

}

void Newtest_Dialog::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"keypress****Opentested_Dialog";
    if(event->key()==Qt::Key_F9)
    {
        ui->pushButton->click();qDebug("keypress****otherkey=%x",event->key());
    }
    else
    {
        if(event->key()==Qt::Key_F10)
        {
            QList<QTableWidgetItem*>items = ui->route_tableWidget->selectedItems();
            if(items.count() >0)
            {
                //QListWidgetItem* item =ui->route_tableWidget->currentItem();
                int row =ui->route_tableWidget->currentRow();
                if(row > 0)
                {
                    ui->route_tableWidget->selectRow(row-1);
                }
                else
                {
                    return;
                }
            }
            else
            {
                return;
            }

        }
        else
        {
            if(event->key()==Qt::Key_F11)
            {
                QList<QTableWidgetItem*>items = ui->route_tableWidget->selectedItems();
                if(items.count() >0)
                {
                    //QListWidgetItem* item =ui->route_tableWidget->currentItem();
                    int row =ui->route_tableWidget->currentRow();
                    if(row < ui->route_tableWidget->rowCount()-1)
                    {
                        ui->route_tableWidget->selectRow(row+1);
                    }
                    else
                    {
                        return;
                    }
                }
                else
                {
                    return;
                }
            }
        }
    }

}
