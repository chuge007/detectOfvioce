#include "export_db_dialog.h"
#include "ui_export_db_dialog.h"
#include "sqltablemodelalternativebackground.h"
#include "HardwareOpp.h"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QListView>
#include <QMessageBox>
#include <QFileDialog>
#include <QSqlError>

QSqlDatabase tested_db = QSqlDatabase::addDatabase("QSQLITE","tested_db");//
export_db_dialog::export_db_dialog(QWidget *parent,QSqlDatabase db,QString db_name, QString route_name) :
    QDialog(parent),
    ui(new Ui::export_db_dialog)
{
    //if(current_db_name=="weld_check_data.db" ||current_route_name=="default_testdb")
    ui->setupUi(this);
    ui->warning_lable->setText("");
    ui->filter_label->setText("");
    user_name_lst.clear();
    route_name_lst.clear();
    date_value_lst.clear();
//qDebug()<<"export_db_dialog88888";
    current_db=db;
    current_route_name =route_name;
    current_db_name= db_name;
    ui->start_date->setDate(QDate::currentDate());
    ui->filish_date->setDate(QDate::currentDate());
#if 0
    model = new SqlTableModelAlternativeBackground(this,db);
    model->setTable("tested_route_namelst");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
    model->select();
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    b_delegate = new BooleanDelegate(this);
    ui->tableView->setItemDelegateForColumn(7,b_delegate);
    ui->tableView->setColumnHidden(0,true);// 隐藏列*/
    ui->tableView->setColumnHidden(4,true);// 隐藏列*/
    ui->tableView->setColumnHidden(5,true);// 隐藏列*/
    ui->tableView->setColumnHidden(6,true);// 隐藏列*/

    //ui->tableView->resizeColumnsToContents();
    //ui->tableView->resizeColumnToContents(1);
    ui->tableView->setColumnWidth(1, 310);
#endif
    //if(current_db_name=="weld_check_data.db" ||current_route_name=="default_testdb")
    {
        //ui->groupBox->setEnabled(false);
    }
    //else
    {
        ui->groupBox->setEnabled(true);
        QSqlQuery query_user(db);
        if(query_user.exec("select * from adduser") )
        {
            while(query_user.next())
            {
                QString username=query_user.value(1).toString();
                ui->user_comboBox->addItem(username);
            }
        }
        ui->user_comboBox->setStyleSheet("QComboBox { min-height: 25px; min-width: 60px; }"
                                                        "QComboBox QAbstractItemView::item { min-height: 25px; min-width: 60px; }");
        ui->user_comboBox->setView(new QListView());

        b_delegate = new BooleanDelegate(this);
        ui->tableWidget->setItemDelegateForColumn(3,b_delegate);
        ui->tableWidget->setColumnWidth(0, 310);
        QSqlQuery query_tested_route_name(current_db);
        query_tested_route_name.exec("select * from tested_route_namelst " );
        int i=0;
        while(query_tested_route_name.next())
        {
            ui->tableWidget->setRowCount(i+1);
            QString route_name = query_tested_route_name.value(1).toString();
            QString user_name = query_tested_route_name.value(2).toString();
            QString date_value = query_tested_route_name.value(3).toString();//qDebug()<<"route_name="<<route_name;
            user_name_lst.append(user_name);
            route_name_lst.append(route_name);
            date_value_lst.append(date_value);
            QStringList listname = route_name.split(tr("$"));
            if(current_db_name=="weld_check_data.db")
            {
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(listname.at(1)));
            }
            else
            {
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(route_name));
            }
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(user_name));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(date_value));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(0));
            ui->tableWidget->item(i,3)->setData(Qt::DisplayRole, 1);
            //int selected =query_tested_route_name.value(4).toInt();//qDebug()<<"selected="<<selected;
            i++;

        }
        for(int j=0;j<i;j++)
        {
            query_tested_route_name.exec(tr("UPDATE  tested_route_namelst SET slected='%1' WHERE id ='%2'").arg(1).arg(j+1) );
        }
        ui->start_date->setEnabled(false);
        ui->filish_date->setEnabled(false);
        ui->user_comboBox->setEnabled(false);
        ui->filter_but->setEnabled(false);
    }

    connect(this,SIGNAL(accepted()),this,SLOT(export_information()));

}

export_db_dialog::~export_db_dialog()
{
    delete ui;
}

void export_db_dialog::on_cancel_but_clicked()
{
    reject();
}

void export_db_dialog::on_export_but_clicked()
{
#ifdef Q_OS_LINUX
    QString _szUsb = HardwareOpp::GetUsbPath() ;
    if(_szUsb.isEmpty())
    {
        //QMessageBox::information(this,tr("Export"),tr("Usb Storage Not Found"),QMessageBox::Yes) ;
        ui->warning_lable->setText("Usb Storage Not Found!");
    }
    else
    {
        if(ui->dbname_lineEdit->text().isEmpty())
        {
            ui->warning_lable->setText("Please input db name!");
            return;
        }
        current_tested_db =this->get_db_name();

        tested_db.setDatabaseName(current_tested_db);//"tested_routes.db"
        if(!tested_db.open())
        {
            QMessageBox::warning(NULL, "database", "error!!");
            this->close();
            return ;
        }
        tested_db.exec("PRAGMA synchronous = OFF");
        tested_db.exec("PRAGMA journal_mode = MEMORY");
        tested_db.exec("PRAGMA page_size=32768");
        tested_db.exec("PRAGMA cache_size = 8000 ");
        current_db.transaction();
        //select   *   into   b数据库.dbo.a表   from   a数据库.dbo.a表   where   条件

        QList <QString> current_route_name_lst;
        QSqlQuery query_tested_route_name(current_db);
        query_tested_route_name.exec("select * from tested_route_namelst " );
        while(query_tested_route_name.next())
        {
            int selected =query_tested_route_name.value(4).toInt();
            if(selected==1)
            {
                QString route_name =query_tested_route_name.value(1).toString();
                current_route_name_lst.append(route_name);
            }
        }
        if(current_route_name_lst.count()>0)
        {
            for(int i=0; i<current_route_name_lst.count(); i++)
            {
                QSqlQuery query_new_route(tested_db);
                if(query_new_route.exec(QObject::tr("CREATE TABLE IF NOT EXISTS '%1'(id INTEGER PRIMARY KEY autoincrement,img BLOB,img_icon BLOB,weld_id_row INTEGER,weld_id INTEGER,"
                                              //   5              6            7             8              9        10                 11              12                13
                                                "weldgroup TEXT,weldpart TEXT,weldname TEXT,ok_nok INTEGER,icon BLOB,raw_wave_data BLOB,gate_th INTEGER,gate_start INTEGER,gate_end INTEGER ,"
                                              //   14          15                  16            17         18                  19               20        21
                                                "gain INTEGER,set_velocity INTEGER,d_mes REAL ,i_mes REAL,checktime TEXT, Selected INTEGER, dmin REAL,dmax REAL,"
                                              //   22         23          24
                                                "imin REAL, imax REAL, reasons TEXT)").arg(current_route_name_lst.at(i))) )
                {}

                QSqlQuery query_route(current_db);
                if(query_route.exec(tr("select * from '%1'").arg(current_route_name_lst.at(i))))
                {
                    while( query_route.next())
                    {
                        int weld_id_row  =query_route.value(3).toInt();
                        int weld_id  =query_route.value(4).toInt();
                        QString weldgroup  =query_route.value(5).toString();
                        QString weldpart  =query_route.value(6).toString();
                        QString weldname  =query_route.value(7).toString();
                        int ok_nok  =query_route.value(8).toInt();
                        QByteArray icon = query_route.value(9).toByteArray();
                        QByteArray raw_wave_data = query_route.value(10).toByteArray();
                        int gate_th  =query_route.value(11).toInt();
                        int gate_start  =query_route.value(12).toInt();
                        int gate_end  =query_route.value(13).toInt();
                        int gain  =query_route.value(14).toInt();
                        int set_velocity  =query_route.value(15).toInt();
                        float d_mes  =query_route.value(16).toFloat();
                        float i_mes  =query_route.value(17).toFloat();
                        QString checktime  =query_route.value(18).toString();
                        int Selected  =query_route.value(19).toInt();
                        float dmin  =query_route.value(20).toFloat();
                        float dmax  =query_route.value(21).toFloat();
                        float imin  =query_route.value(22).toFloat();
                        float imax  =query_route.value(23).toFloat();
                        QString reasons  =query_route.value(24).toString();//qDebug()<<"***checktime="<<checktime;

                        {                                                      //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
                            query_new_route.prepare(tr("insert into '%1' values (?,?,?,?,?,?,?,?,?,?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)").arg(current_route_name_lst.at(i)));
                            query_new_route.bindValue(3, weld_id_row);
                            query_new_route.bindValue(4, weld_id);
                            query_new_route.bindValue(5, weldgroup);
                            query_new_route.bindValue(6, weldpart);
                            query_new_route.bindValue(7, weldname);
                            query_new_route.bindValue(8, ok_nok);
                            query_new_route.bindValue(9, icon);
                            query_new_route.bindValue(10, raw_wave_data);
                            query_new_route.bindValue(11, gate_th);
                            query_new_route.bindValue(12, gate_start);
                            query_new_route.bindValue(13, gate_end);
                            query_new_route.bindValue(14, gain);
                            query_new_route.bindValue(15, set_velocity);
                            query_new_route.bindValue(16, d_mes);
                            query_new_route.bindValue(17, i_mes);
                            query_new_route.bindValue(18, checktime);
                            query_new_route.bindValue(19, Selected);
                            query_new_route.bindValue(20, dmin);
                            query_new_route.bindValue(21, dmax);
                            query_new_route.bindValue(22, imin);
                            query_new_route.bindValue(23, imax);
                            query_new_route.bindValue(24, reasons);
                            query_new_route.exec();
                        }
                    }
                }

            }
            QSqlQuery query_newroute_namelst(tested_db);
            if(query_newroute_namelst.exec(QObject::tr("CREATE TABLE IF NOT EXISTS tested_route_namelst(id INTEGER PRIMARY KEY autoincrement, route_name TEXT, user TEXT, date TEXT, slected INTEGER)") ) )
            {
                //qDebug()<<"create query_newroute_namelst ok";
            }
            //int count=ui->tableWidget->rowCount();
            for(int i=0;i<current_route_name_lst.count();i++)
            {
                QString route_name =current_route_name_lst.at(i);
                QString user_name= ui->tableWidget->item(i,1)->text();
                QString date= ui->tableWidget->item(i,2)->text();
                query_newroute_namelst.prepare("insert into tested_route_namelst values (?,?,?,?,?)");
                query_newroute_namelst.bindValue(1, route_name );
                query_newroute_namelst.bindValue(2, user_name);
                query_newroute_namelst.bindValue(3, date);
                query_newroute_namelst.bindValue(4, 0);
                query_newroute_namelst.exec();
            }
        }
        else
        {
            ui->warning_lable->setText("Please select tested routes to export!");
            return;
        }

        QString _szDest = _szUsb + current_tested_db;
        QFile::copy( current_tested_db , _szDest) ;
        int _ret ;
        _ret = system("sync");
        _ret = system("sync");
        Q_UNUSED(_ret) ;
        QMessageBox::information(this,tr("Export"),tr("Export OK"),QMessageBox::Yes) ;
    }
#else

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save DB File"),
                                             QDir::currentPath(),tr("DB Files ( *.ntdb)"));

    QString croped_fileName=fileName.section(".",0,0);
    if (fileName.isEmpty())
    return;
//    QFile file(fileName);
//    if (!file.open(QFile::WriteOnly | QFile::Text))
//    {
//        QMessageBox::warning(this, tr("Save DB File"),tr("Cannot Save DB File %1:\n%2.")
//                                      .arg(fileName).arg(file.errorString()));
//        return;
//    }

    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_time = current_date_time.toString("yyyy-MM-dd,hh-mm-ss");
    current_tested_db=croped_fileName+"(" + current_time + ")"+".ntdb";

    tested_db.setDatabaseName(current_tested_db);//"tested_routes.db"
    if(!tested_db.open())
    {
        QMessageBox::warning(NULL, "database", "error!!");
        this->close();
        return ;
    }
    tested_db.exec("PRAGMA synchronous = OFF");
    tested_db.exec("PRAGMA journal_mode = MEMORY");
    tested_db.exec("PRAGMA page_size=32768");
    tested_db.exec("PRAGMA cache_size = 8000 ");
    current_db.transaction();
    //select   *   into   b数据库.dbo.a表   from   a数据库.dbo.a表   where   条件

    QList <QString> current_route_name_lst;
    QSqlQuery query_tested_route_name(current_db);
    query_tested_route_name.exec("select * from tested_route_namelst " );
    while(query_tested_route_name.next())
    {
        int selected =query_tested_route_name.value(4).toInt();
        if(selected==1)
        {
            QString route_name =query_tested_route_name.value(1).toString();
            current_route_name_lst.append(route_name);
            qDebug()<<route_name<<"!!!";
        }
    }
    if(current_route_name_lst.count()>0)
    {
        for(int i=0; i<current_route_name_lst.count(); i++)
        {
            QSqlQuery query_new_route(tested_db);
            if(query_new_route.exec(QObject::tr("CREATE TABLE IF NOT EXISTS '%1'(id INTEGER PRIMARY KEY autoincrement,img BLOB,img_icon BLOB,weld_id_row INTEGER,weld_id INTEGER,"
                                          //   5              6            7             8              9        10                 11              12                13
                                            "weldgroup TEXT,weldpart TEXT,weldname TEXT,ok_nok INTEGER,icon BLOB,raw_wave_data BLOB,gate_th INTEGER,gate_start INTEGER,gate_end INTEGER ,"
                                          //   14          15                  16            17         18                  19               20        21
                                            "gain INTEGER,set_velocity INTEGER,d_mes REAL ,i_mes REAL,checktime TEXT, Selected INTEGER, dmin REAL,dmax REAL,"
                                          //   22         23          24
                                            "imin REAL, imax REAL, reasons TEXT)").arg(current_route_name_lst.at(i))) )
            {}

            QSqlQuery query_route(current_db);
            if(query_route.exec(tr("select * from '%1'").arg(current_route_name_lst.at(i))))
            {
                while( query_route.next())
                {
                    int weld_id_row  =query_route.value(3).toInt();
                    int weld_id  =query_route.value(4).toInt();
                    QString weldgroup  =query_route.value(5).toString();
                    QString weldpart  =query_route.value(6).toString();
                    QString weldname  =query_route.value(7).toString();
                    int ok_nok  =query_route.value(8).toInt();
                    QByteArray icon = query_route.value(9).toByteArray();
                    QByteArray raw_wave_data = query_route.value(10).toByteArray();
                    int gate_th  =query_route.value(11).toInt();
                    int gate_start  =query_route.value(12).toInt();
                    int gate_end  =query_route.value(13).toInt();
                    int gain  =query_route.value(14).toInt();
                    int set_velocity  =query_route.value(15).toInt();
                    float d_mes  =query_route.value(16).toFloat();
                    float i_mes  =query_route.value(17).toFloat();
                    QString checktime  =query_route.value(18).toString();
                    int Selected  =query_route.value(19).toInt();
                    float dmin  =query_route.value(20).toFloat();
                    float dmax  =query_route.value(21).toFloat();
                    float imin  =query_route.value(22).toFloat();
                    float imax  =query_route.value(23).toFloat();
                    QString reasons  =query_route.value(24).toString();//qDebug()<<"***checktime="<<checktime;

                    {                                                      //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
                        query_new_route.prepare(tr("insert into '%1' values (?,?,?,?,?,?,?,?,?,?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)").arg(current_route_name_lst.at(i)));
                        query_new_route.bindValue(3, weld_id_row);
                        query_new_route.bindValue(4, weld_id);
                        query_new_route.bindValue(5, weldgroup);
                        query_new_route.bindValue(6, weldpart);
                        query_new_route.bindValue(7, weldname);
                        query_new_route.bindValue(8, ok_nok);
                        query_new_route.bindValue(9, icon);
                        query_new_route.bindValue(10, raw_wave_data);
                        query_new_route.bindValue(11, gate_th);
                        query_new_route.bindValue(12, gate_start);
                        query_new_route.bindValue(13, gate_end);
                        query_new_route.bindValue(14, gain);
                        query_new_route.bindValue(15, set_velocity);
                        query_new_route.bindValue(16, d_mes);
                        query_new_route.bindValue(17, i_mes);
                        query_new_route.bindValue(18, checktime);
                        query_new_route.bindValue(19, Selected);
                        query_new_route.bindValue(20, dmin);
                        query_new_route.bindValue(21, dmax);
                        query_new_route.bindValue(22, imin);
                        query_new_route.bindValue(23, imax);
                        query_new_route.bindValue(24, reasons);
                        query_new_route.exec();
                    }
                }
            }

        }
        QSqlQuery query_newroute_namelst(tested_db);
        if(query_newroute_namelst.exec(QObject::tr("CREATE TABLE IF NOT EXISTS tested_route_namelst(id INTEGER PRIMARY KEY autoincrement, route_name TEXT, user TEXT, date TEXT, slected INTEGER)") ) )
        {
            //qDebug()<<"create query_newroute_namelst ok";
        }
        //int count=ui->tableWidget->rowCount();
        for(int i=0;i<current_route_name_lst.count();i++)
        {
            QString route_name =current_route_name_lst.at(i);
            QString user_name= ui->tableWidget->item(i,1)->text();
            QString date= ui->tableWidget->item(i,2)->text();
            query_newroute_namelst.prepare("insert into tested_route_namelst values (?,?,?,?,?)");
            query_newroute_namelst.bindValue(1, route_name );
            query_newroute_namelst.bindValue(2, user_name);
            query_newroute_namelst.bindValue(3, date);
            query_newroute_namelst.bindValue(4, 0);
            query_newroute_namelst.exec();
        }
    }
    else
    {
        ui->warning_lable->setText("Please select tested routes to export!");
        return;
    }
#endif
    current_db.commit();
    tested_db.close();
    accept();
}

void export_db_dialog::on_filter_but_clicked()
{
    QString user= ui->user_comboBox->currentText();
    /*
    QString sel_stardate= ui->start_date->text();
    QString sel_enddate= ui->filish_date->text();//qDebug()<<"user="<<user<<"stardate="<<stardate<<"enddate="<<enddate;
    bool ok;
    QStringList list_start = sel_stardate.split("/", QString::SkipEmptyParts);
    int sel_start_year = list_start.at(0).toInt(&ok,10);//qDebug()<<"sel_start_year="<<sel_start_year<<"ok"<<ok;
    int sel_start_month = list_start.at(1).toInt(&ok,10);
    int sel_start_date = list_start.at(2).toInt(&ok,10);
    QStringList list_end = sel_enddate.split("/", QString::SkipEmptyParts);
    int sel_end_year = list_end.at(0).toInt(&ok,10);
    int sel_end_month = list_end.at(1).toInt(&ok,10);
    int sel_end_date = list_end.at(2).toInt(&ok,10);
    if(sel_start_year <sel_end_year)
    {
      //int seconds = start.secTo(end);
    }*/

    QDate start_date =ui->start_date->date();
    QDate end_date =ui->filish_date->date();
    QDate current_date = QDate::currentDate();
    //QDate before_date=  end_date.addDays(-1);//获取前一天时间toString("yyyy-mm-dd")
    if(start_date > current_date)
    {
        ui->filter_label->setText("Starting time before the current time!");
        //QMessageBox::warning(this,tr("Warning"),tr("Starting time before the current time\n"
        //                                                          "To choose time again."),QMessageBox::Yes,QMessageBox::No);
    }
    else
    {
        if(start_date > end_date)
        {
            ui->filter_label->setText("End time before the starting time!");
            //QMessageBox::warning(this,tr("Warning"),tr("End time before the starting time\n"
            //                                                          "To choose time again."),QMessageBox::Yes,QMessageBox::No);
        }
        else
        {
            ui->filter_label->setText("");
            date_lst.clear();
            user_name_lst.clear();
            date_value_lst.clear();
            route_name_lst.clear();
            QSqlQuery query_tested_route_name(current_db);
            query_tested_route_name.exec(tr("select * from tested_route_namelst  WHERE user = '%1' ").arg(user) );
            while(query_tested_route_name.next())
            {
                QString route_name = query_tested_route_name.value(1).toString();
                QString user_name = query_tested_route_name.value(2).toString();
                QString date_value = query_tested_route_name.value(3).toString();
                route_name_lst.append(route_name);
                user_name_lst.append(user_name);
                date_value_lst.append(date_value);

                bool ok;
                QStringList list_date = date_value.split("-", QString::SkipEmptyParts);
                int year = list_date.at(0).toInt(&ok,10);
                int month = list_date.at(1).toInt(&ok,10);
                int date = list_date.at(2).toInt(&ok,10);
                QDate sel_date = QDate ( year, month, date );
                date_lst.append(sel_date);
            }

           ui->tableWidget->clear();
           ui->tableWidget->setRowCount(0);
           ui->tableWidget->setColumnCount(4);
           QStringList header;
           header.append("Route name");
           header.append("User");
           header.append("Date");
           header.append("Slected");
           ui->tableWidget->setHorizontalHeaderLabels(header);
           int j=0;
           for(int i=0;i<date_lst.count();i++)
           {

               if((start_date < date_lst.at(i)||start_date == date_lst.at(i)) && ( date_lst.at(i)<end_date||date_lst.at(i)==end_date) )
               {
                    ui->tableWidget->setRowCount(j+1);
                    ui->tableWidget->setItem(j,0,new QTableWidgetItem(route_name_lst.at(i)));
                    ui->tableWidget->setItem(j,1,new QTableWidgetItem(user_name_lst.at(i)));
                    ui->tableWidget->setItem(j,2,new QTableWidgetItem(date_value_lst.at(i)));
                    ui->tableWidget->setItem(j,3,new QTableWidgetItem(0));
                    ui->tableWidget->item(j,3)->setData(Qt::DisplayRole, 1);
                    j++;
               }
                //qDebug()<<"user_name_lst.at(0)="<<user_name_lst.at(i)<<"date_value_lst="<<date_value_lst.at(i);

           }

        }
    }

}

void export_db_dialog::on_all_checkBox_clicked()
{
    current_db.transaction();
    if(ui->all_checkBox->isChecked()==true)
    {
        for(int i=0;i<ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->item(i,3)->setData(Qt::DisplayRole, 1);
            QSqlQuery query_tested_route_name(current_db);
            if(query_tested_route_name.exec(tr("UPDATE  tested_route_namelst SET slected='%1' WHERE id ='%2'").arg(1).arg(i+1) ))
            {
                //qDebug()<<"update tested_route_namelst ok ";
            }

        }
    }
    else
    {
        for(int i=0;i<ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->item(i,3)->setData(Qt::DisplayRole, 0);
            QSqlQuery query_tested_route_name(current_db);
            if(query_tested_route_name.exec(tr("UPDATE  tested_route_namelst SET slected='%1' WHERE id ='%2'").arg(0).arg(i+1) ))
            {
                //qDebug()<<"update tested_route_namelst ok ";
            }

        }
    }
    current_db.commit();
}

void export_db_dialog::on_filter_radioButton_clicked()
{
    if(ui->filter_radioButton->isChecked()==true)
    {
        ui->start_date->setEnabled(true);
        ui->filish_date->setEnabled(true);
        ui->user_comboBox->setEnabled(true);
        ui->filter_but->setEnabled(true);
        ui->filter_but->click();
    }
    else
    {
        ui->start_date->setEnabled(false);
        ui->filish_date->setEnabled(false);
        ui->user_comboBox->setEnabled(false);
        ui->filter_but->setEnabled(false);
    }
}

void export_db_dialog::on_radioButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    QStringList header;
    header.append("Route name");
    header.append("User");
    header.append("Date");
    header.append("Slected");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    if(ui->filter_radioButton->isChecked()==false)
    {
        ui->start_date->setEnabled(false);
        ui->filish_date->setEnabled(false);
        ui->user_comboBox->setEnabled(false);
        ui->filter_but->setEnabled(false);
        ui->all_checkBox->setChecked(true);
    }
    QSqlQuery query_tested_route_name(current_db);
    query_tested_route_name.exec("select * from tested_route_namelst " );
    int i=0;
    while(query_tested_route_name.next())
    {
        ui->tableWidget->setRowCount(i+1);
        QString route_name = query_tested_route_name.value(1).toString();
        QString user_name = query_tested_route_name.value(2).toString();
        QString date_value = query_tested_route_name.value(3).toString();
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(route_name));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(user_name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(date_value));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(0));
        ui->tableWidget->item(i,3)->setData(Qt::DisplayRole, 1);
        i++;
    }
    for(int j=0;j<i;j++)
    {
        query_tested_route_name.exec(tr("UPDATE  tested_route_namelst SET slected='%1' WHERE id ='%2'").arg(1).arg(j+1) );
    }

}

QString  export_db_dialog::get_db_name()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_time = current_date_time.toString("yyyy-MM-dd,hh-mm-ss");
    QString db_name =ui->dbname_lineEdit->text()+"(" + current_time + ")"+".ntdb";
    return db_name;
}

void export_db_dialog::export_information()
{
    //qDebug()<<"***export_information***current_tested_db="<<current_tested_db;
#ifdef Q_OS_LINUX
    //QString db_name= this->get_db_name();
    /*bool ok_delete = QFile::remove(current_tested_db);
    if(ok_delete){
        qDebug()<<"delete ok******";
    }
    else{
        qDebug()<<"delete Nok******";
    }
    QMessageBox::information(NULL, QString("Export"), QString(tr("Export '%1' sucessfully!").arg(current_tested_db)));*/
#else
    QMessageBox::information(NULL, QString("Export"), QString(tr("Export '%1' sucessfully!").arg(current_tested_db)));
#endif
}

void export_db_dialog::on_tableWidget_cellClicked(int row, int column)
{
    //qDebug()<<"row="<<row<<"colum="<<column;
    if(column==3)
    {
        int selected=0;
        QString route_name=ui->tableWidget->item(row,0)->text();
        QSqlQuery query_tested_route_name(current_db);
        if(query_tested_route_name.exec(tr("select * from tested_route_namelst WHERE route_name ='%1' ").arg(route_name) ) )
        {
            if(query_tested_route_name.next())
            {
                selected= query_tested_route_name.value(4).toInt();
            }
        }
        if(selected==0)
        {
            query_tested_route_name.exec(tr("UPDATE  tested_route_namelst SET slected='%1' WHERE route_name ='%2'").arg(1).arg(route_name) );
        }
        else
        {
            query_tested_route_name.exec(tr("UPDATE  tested_route_namelst SET slected='%1' WHERE route_name ='%2'").arg(0).arg(route_name) );
        }
    }
}
