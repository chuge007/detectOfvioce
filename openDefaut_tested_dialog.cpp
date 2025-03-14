#include "openDefaut_tested_dialog.h"
#include "ui_openDefaut_tested_dialog.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QListWidgetItem>
#include <QList>
#include <QMessageBox>
#include <QKeyEvent>

void openDefaut_tested_dialog::list_testdata_table()
{
    ui->route_tableWidget->clear();
    ui->route_tableWidget->setRowCount(0);
    QSqlQuery query(opendb);
    QString tablestr;
  //bool isTableExist = query.exec(QObject::tr("select count(*) from sqlite_master where type='table' and name like '%1'").arg("default_route"));    //关键的判断
    bool isTableExist = query.exec(QObject::tr("SELECT name FROM sqlite_master WHERE type='table' order by name"));   //关键的判断

    if(!isTableExist)
   {
       qDebug() << "table does not exist";
   }
   else
   {
       // ui->route_tableWidget->setRowCount(1);
       int i =0;
       while(query.next())
       {

          tablestr = query.value(0).toString();//qDebug()<<"current_test_route_name="<<current_test_route_name<<"tablestr="<<tablestr;
          if(/*tablestr!= "sqlite_sequence" &&*/ tablestr!= current_test_route_name)
          {
            //ui->route_tableWidget->setRowCount(i+1);
            QStringList listname = tablestr.split(tr("$"));
            if(listname.count()>8)
            {
                ui->route_tableWidget->setRowCount(i+1);
                ui->route_tableWidget->setItem(i ,0,new QTableWidgetItem(listname.at(1)) );
                //ui->route_tableWidget->setItem(i ,0,new QTableWidgetItem(tablestr) );
                ui->route_tableWidget->setItem(i ,1,new QTableWidgetItem(listname.at(2)+"/"+listname.at(3)+"/"+ listname.at(4)+" "+listname.at(5)+":"+ listname.at(6)+":"+ listname.at(7)+":"+ listname.at(8)) );
                i++;
            }
            else
            {
                if(tablestr=="default_testdb")
                {
                    ui->route_tableWidget->setRowCount(i+1);
                    ui->route_tableWidget->setItem(i ,0,new QTableWidgetItem(tablestr) );
                }
            }


            //qDebug() << "table add "<<tablestr;
          }
       }
       qDebug() << "******set item OK";

       //if(ui->route_tableWidget->rowCount()>0)
       {
           //ui->route_tableWidget->selectRow(0);
           //current_test_route_name = ui->route_tableWidget->item(0,0)->text();
       }
   }
}



openDefaut_tested_dialog::openDefaut_tested_dialog(QWidget *parent, QSqlDatabase db ,QString def_routename) ://,QString test_route_name
    QDialog(parent),
    ui(new Ui::openDefaut_tested_dialog)
{
    ui->setupUi(this);//qDebug()<<"query_test_routelst***db.tables="<<db.tables();

    ui->gp_treeWidget->hide();
    opendb =db;
    /*
    QTreeWidgetItem * gpall_item = new QTreeWidgetItem(QStringList()<<db_name);
    gpall_item->setSizeHint(0,QSize(100,25));
    ui->gp_treeWidget->addTopLevelItem(gpall_item);
    QSqlQuery querygp(db);
    QSqlQuery querypt(db);
    querygp.exec("select DISTINCT weldgroup  from test_routelst");
    QString gpstr,ptstr;
    while(querygp.next())
    {
        //qDebug() <<  querygp.value(0).toString();
        gpstr = querygp.value(0).toString();
        QTreeWidgetItem * gpitem = new QTreeWidgetItem(QStringList()<<gpstr);
        gpitem->setIcon(0,QIcon("://img/Folder.png"));
        gpitem->setSizeHint(0,QSize(100,25));
        gpall_item->addChild(gpitem);
        querypt.exec(tr("select DISTINCT weldpart from test_routelst  WHERE weldgroup='%1'").arg(gpstr));
        while(querypt.next())
        {
              ptstr = querypt.value(0).toString();
              QTreeWidgetItem * ptitem = new QTreeWidgetItem(QStringList()<<ptstr);
              ptitem->setIcon(0,QIcon("://img/part_A.png"));
              ptitem->setSizeHint(0,QSize(100,25));
              gpitem->addChild(ptitem);;
        }

    }
    ui->gp_treeWidget->expandAll();
    */

    ui->route_tableWidget->setColumnCount(2);
    ui->route_tableWidget->resizeColumnToContents(1);
    /*
    QSqlQuery query(db);
        QString tablestr;
   //bool isTableExist = query.exec(QObject::tr("select count(*) from sqlite_master where type='table' and name like '%1'").arg("default_route"));    //关键的判断
    bool isTableExist = query.exec(QObject::tr("SELECT name FROM sqlite_master WHERE type='table' order by name"));    //关键的判断

    if(!isTableExist)
   {
       qDebug() << "table does not exist";
   }
   else
   {

          // ui->route_tableWidget->setRowCount(1);
           int i =0;
       while(query.next())
       {

          tablestr = query.value(0).toString();
          if(tablestr!= "sqlite_sequence")
          {
            ui->route_tableWidget->setRowCount(i+1);
            ui->route_tableWidget->setItem(i ,0,new QTableWidgetItem(tablestr) );
            i++;
            //qDebug() << "table add "<<tablestr;
          }
       }
   }*/
    //list_testdata_table();
    get_def_routename=def_routename;
    qDebug() << "get_def_routename= "<<get_def_routename;

}

openDefaut_tested_dialog::~openDefaut_tested_dialog()
{
    delete ui;
}

void openDefaut_tested_dialog::on_pushButton_clicked()
{
    QTableWidgetItem* item =ui->route_tableWidget->currentItem();
    if(item)
    {
        accept();
    }
    else
    {
        reject();
        qDebug("on_pushButton_clicked item error ");
        //QMessageBox::information(NULL, QString("Open"), QString("No route select!"));

    }

}

void openDefaut_tested_dialog::on_pushButton_2_clicked()
{
    reject();
}

QString openDefaut_tested_dialog::get_route_name()
{
    QString route_name;
    QList<QTableWidgetItem*>items = ui->route_tableWidget->selectedItems();
    route_name=get_def_routename ;
    if(items.count() >0)
    {
            int currentrow = items.at(0)->row();
            qDebug() <<currentrow;
            QTableWidgetItem* itemname =ui->route_tableWidget->item(currentrow,0);
            if(ui->route_tableWidget->item(currentrow,1))
            {
                QTableWidgetItem* itemtime =ui->route_tableWidget->item(currentrow,1);
                QStringList listdatetime = itemtime->text().split(tr(" "));
                QStringList datestr = listdatetime.at(0).split(tr("/"));
                QStringList timestr = listdatetime.at(1).split(tr(":"));
                route_name = "$"+itemname->text()+"$"+datestr.at(0)+"$"+datestr.at(1)+"$"+datestr.at(2)+"$"+timestr.at(0)+"$"+timestr.at(1)+"$"+timestr.at(2)+"$"+timestr.at(3);
                route_name = "default_route"+route_name;
                current_test_route_name =route_name;
                qDebug() <<current_test_route_name;
            }
            else
            {
                 route_name = itemname->text();
                 current_test_route_name =route_name;
                 qDebug() <<current_test_route_name;
            }
     }
    else
    {
        route_name=get_def_routename ;
    }
//qDebug() <<" return  route_name="<<route_name;
     return route_name;
}
/*
void openDefaut_tested_dialog::on_gp_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    if( (item->parent()== NULL)){
    }
    else
    {
        if ((item->parent()->parent()== NULL)){
        }
        else
        {
            current_part = item->text(0);
            current_group = item->parent()->text(0);
            QList<QString> route_namelst;
            QSqlQuery  query_routelst;
            if( query_routelst.exec(QObject::tr("select * from test_routelst where weldgroup ='%1' and weldpart ='%2' ").arg(current_group).arg(current_part)))
            {
                while( query_routelst.next() )
                {
                    QString route_name = query_routelst.value(1).toString();
                    route_namelst.append(route_name);
                }
            }
            ui->route_tableWidget->setRowCount(route_namelst.count());
            ui->route_tableWidget->setColumnCount(1);
            for(int i=0; i<route_namelst.count(); i++)
            {
                ui->route_tableWidget->setItem(i ,0,new QTableWidgetItem(route_namelst.at(i)) );
            }
        }
    }
}

QString openDefaut_tested_dialog::get_group_name()
{
    return current_group;
}

QString openDefaut_tested_dialog::get_part_name()
{
    return current_part;
}
*/



void openDefaut_tested_dialog::on_route_tableWidget_clicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        ui->pushButton->setEnabled(true);
        ui->pushButton_del->setEnabled(true);
    }
}

void openDefaut_tested_dialog::on_pushButton_del_clicked()
{
   // int ok = QMessageBox::warning(this,tr("Delete Data!"),tr("Sure delete?"),QMessageBox::Yes,QMessageBox::No);
    //if(ok == QMessageBox::Yes)
    {
        QSqlQuery query_del(opendb);

        QString route_name;
        QList<QTableWidgetItem*>items = ui->route_tableWidget->selectedItems();
        if(items.count()> 0)
        {
            for(int i=0;i<ui->route_tableWidget->rowCount();i++)
            {
                QTableWidgetItem* itemname =ui->route_tableWidget->item(i,0);
                if(itemname->isSelected())
                {
                    if(ui->route_tableWidget->item(i,1))
                    {
                        QTableWidgetItem* itemtime =ui->route_tableWidget->item(i,1);
                        QStringList listdatetime = itemtime->text().split(tr(" "));
                        QStringList datestr = listdatetime.at(0).split(tr("/"));
                        QStringList timestr = listdatetime.at(1).split(tr(":"));
                        route_name = "$"+itemname->text()+"$"+datestr.at(0)+"$"+datestr.at(1)+"$"+datestr.at(2)+"$"+timestr.at(0)+"$"+timestr.at(1)+"$"+timestr.at(2)+"$"+timestr.at(3);
                        route_name = "default_route"+route_name;
                    }
                    else
                    {
                         route_name = itemname->text();
                    }
                    if(route_name=="default_testdb")
                    {
                        //QMessageBox::warning(this,tr("Warning!"),tr("default_route can not be deleted!"),QMessageBox::Yes);
                        ui->warning_lab->setText("default_route can not be deleted!");
                    }
                    else
                    {
                        bool isTabledel = query_del.exec(QObject::tr("DROP TABLE %1").arg(route_name));    //关键的判断
                        if(isTabledel)
                        {
                            list_testdata_table();
                        }
                        else
                        {
                          qDebug() <<query_del.lastError();
                        }
                    }

                }
            }
        }



      /*
        foreach(QTableWidgetItem * item, items)
        {
            route_name=item->text();//
            if(route_name == "weld_check_data")
            {
                QMessageBox::information(NULL, QString("wornning"), QString("default test table can not del!"));
            }
            else
            {
                if(route_name == current_test_route_name)
                {
                    QMessageBox::information(NULL, QString("wornning"), QString("use test table can not del!"));
                }
                else
                {
                    bool isTabledel = query_del.exec(QObject::tr("DROP TABLE %1").arg(route_name));    //关键的判断
                    if(isTabledel)
                    {
                        list_testdata_table();
                    }
                    else
                    {
                      qDebug() <<query_del.lastError();
                    }
                }
            }
        }*/
    }
}
void openDefaut_tested_dialog::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"keypress****openDefaut_tested_dialog";
    if(event->key()==Qt::Key_F9)
    {
        ui->pushButton->click();
        qDebug("openDefaut_tested_dialog****key=F9 enter");
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
