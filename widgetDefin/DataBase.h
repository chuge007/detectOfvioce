#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QMessageBox>
#include <QBuffer>
#include <QDebug>
#include <QSqlError>
#include <QFile>
#include <QtSql>
//#include "C:/Qt/Qt5.5.0/5.5/Src/qtbase/src/3rdparty/sqlite/sqlite3.h"

/*void qtregexp(sqlite3_context* ctx, int argc, sqlite3_value** argv)
{
    QRegExp regex;
    QString str1((const char*)sqlite3_value_text(argv[0]));
    QString str2((const char*)sqlite3_value_text(argv[1]));

    regex.setPattern(str1);
    regex.setCaseSensitivity(Qt::CaseInsensitive);

    bool b = str2.contains(regex);

    if (b)
    {
        sqlite3_result_int(ctx, 1);
    }
    else
    {
        sqlite3_result_int(ctx, 0);
    }
}*/

QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//,"nextsptdb"


static bool opendb (QString db_name)
{
    db.setDatabaseName(db_name);
    if(!db.open())
    {
        QMessageBox::warning(NULL, "database", "open db fail!!");
        //this->close();
        return false;
    }
    db.exec("PRAGMA synchronous = OFF");
    db.exec("PRAGMA journal_mode = MEMORY");
    db.exec("PRAGMA page_size=32768");
    db.exec("PRAGMA cache_size = 8000 ");
    return true;
}

static bool createnewdb(QString dbfilename)//QSqlDatabase * db
{

    db.setDatabaseName(dbfilename);
    if(!db.open())
    {
        QMessageBox::warning(NULL, "database",
                             dbfilename+
                             "creat new db fail !!");
        return false;
    }
    /*db.exec("PRAGMA synchronous = OFF");
    db.exec("PRAGMA journal_mode = MEMORY");
    db.exec("PRAGMA page_size=32768");
    db.exec("PRAGMA cache_size = 8000 ");*/
#if 1
    QPixmap objPixmap("://img/user_lucas.png");
    QByteArray value;
    QBuffer buffer(&value);
    buffer.open(QIODevice::WriteOnly);
    objPixmap.scaled(QSize(64,64)).save(&buffer, "PNG"); // writes pixmap into bytes
    QSqlQuery query;
    if( ! query.exec("select * from adduser"))
    {
        query.exec("create table adduser(id INTEGER PRIMARY KEY autoincrement,Name TEXT,icon BLOB,Password TEXT,Despoter INTEGER,Respoter INTEGER,Instru_Setup INTEGER,Instrument INTEGER)");
        query.prepare("insert into adduser values (?, ?,?, ?,?, ?,?,?)");
        query.bindValue(1, "Admin");
        query.bindValue(2, value);
        query.bindValue(3, "123456");
        query.bindValue(4, 1);
        query.bindValue(5, 1);
        query.bindValue(6, 1);
        query.bindValue(7, 1);
        query.exec();
    }
    //qDebug()<<"****create database ok****"<<query.lastError();
    QSqlQuery query_r;
    if( ! query_r.exec("select * from reason_pass"))
    {
        query_r.exec("create table reason_pass(id INTEGER PRIMARY KEY autoincrement,Method TEXT, Reasons TEXT)");
        query_r.prepare("insert into reason_pass values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_r.bindValue(1, "Visual");
        query_r.bindValue(2, "");
        query_r.exec();qDebug()<<"****create database ok****"<<query.lastError();
        query_r.prepare("insert into reason_pass values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_r.bindValue(1, "Chisel");
        query_r.bindValue(2, "");
        query_r.exec();
        query_r.prepare("insert into reason_pass values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_r.bindValue(1, "Other Ultrasonic Test");
        query_r.bindValue(2, "");
        query_r.exec();
    }

    QSqlQuery query_f;
    if( ! query_f.exec("select * from reason_fail"))
    {
        query_f.exec("create table reason_fail(id INTEGER PRIMARY KEY autoincrement,Method TEXT, Reasons TEXT)");
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "RSWA");
        query_f.bindValue(2, "Undersized");
        query_f.exec();
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "Visual");
        query_f.bindValue(2, "Missing");
        query_f.exec();
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "Visual");
        query_f.bindValue(2, "Off Location");
        query_f.exec();
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "Visual");
        query_f.bindValue(2, "Edge");
        query_f.exec();
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "Visual");
        query_f.bindValue(2, "Excessive Indentation");
        query_f.exec();
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "Visual");
        query_f.bindValue(2, "Pinhole");
        query_f.exec();
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "Visual");
        query_f.bindValue(2, "Crack");
        query_f.exec();
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "Visual");
        query_f.bindValue(2, "Distorted");
        query_f.exec();
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "Visual");
        query_f.bindValue(2, "Stick");
        query_f.exec();
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "Visual");
        query_f.bindValue(2, "Stick (No Attenuation)");
        query_f.exec();
        query_f.prepare("insert into reason_fail values (?, ?, ?)");
        //query.bindValue(0, 0);
        query_f.bindValue(1, "Other Ultrasonic Test");
        query_f.bindValue(2, "Distorted");
        query_f.exec();
    }

    QSqlQuery query_weld;

    query_weld.exec("CREATE TABLE IF NOT EXISTS spot (id INTEGER PRIMARY KEY AUTOINCREMENT,name TEXT,x0 REAL,y0 REAL,r0 REAL,z0 REAL,"
                           "x1 REAL,y1 REAL,r1 REAL,z1 REAL,x3 REAL,y3 REAL,"
                           "r3 REAL,z3 REAL,line_v REAL,arc_v REAL"
                        ")"
                        );// ",robot TEXT,group TEXT,part TEXT,comment TEXT"
    if(query_weld.exec())
    {
        //qDebug()<<"****create database  ****"<<query_weld.lastError();
    }
    else
    {
        //qDebug()<<"****create database  ****"<<query_weld.lastError();
    }
    query_weld.prepare("insert into spot values (?, ?, ?, ?, ? ,? ,? ,? ,? ,?, ? ,? ,? , ? ,? ,?)");
    query_weld.bindValue(1, "line");
    query_weld.bindValue(2, 1.0);
    query_weld.bindValue(3, 2.0);
    query_weld.bindValue(4, 3.0);
    query_weld.bindValue(5, 4.0);
    query_weld.bindValue(6, 1.0);
    query_weld.bindValue(7, 2.0);
    query_weld.bindValue(8, 3.0);
    query_weld.bindValue(9, 4.0);
    query_weld.bindValue(10, 1.0);
    query_weld.bindValue(11, 2.0);
    query_weld.bindValue(12, 3.0);
    query_weld.bindValue(13, 4.0);
    query_weld.bindValue(14, 0.0);
    query_weld.bindValue(15, 0.0);

    QSqlQuery query_imglst;
    if( ! query_imglst.exec("select * from img_list"))
    {
        query_imglst.exec("create table img_list(id INTEGER PRIMARY KEY autoincrement,img BLOB,img_icon BLOB,weldgroup TEXT,weldpart TEXT,parent_img_id INTEGER)");
        /*query_imglst.prepare("insert into img_list values (?, ?,?, ?,?, ?)");
        //query_imglst.bindValue(0, 0);
        query_imglst.bindValue(1, value);
        query_imglst.bindValue(2, value);
        query_imglst.bindValue(3, "123456");
        query_imglst.bindValue(4, "112");
        query_imglst.bindValue(5, 1);
        query_imglst.exec();*/
    }
    QSqlQuery query_spt_pos;
    if(!query_spt_pos.exec("CREATE TABLE IF NOT EXISTS spotpos_list (id INTEGER PRIMARY KEY autoincrement,img_id INTEGER ,spot_id INTEGER,pos_x REAL,pos_y REAL,weldname TEXT)"))
    qDebug()<<"****create spotpos_list  ****"<<query_spt_pos.lastError();

    QSqlQuery query_routlst;
    if( ! query_routlst.exec("select * from rout_list"))
    {
        query_routlst.exec("create table rout_list(id INTEGER PRIMARY KEY autoincrement,img BLOB,img_icon BLOB,rout_id INTEGER,rout_name TEXT,weldgroup TEXT,weldpart TEXT)");
    }

    QSqlQuery query_routname_lst;
    if( ! query_routname_lst.exec("select * from routname_list"))
    {
        query_routname_lst.exec("create table routname_list(id INTEGER PRIMARY KEY autoincrement,img BLOB,img_icon BLOB,rout_id INTEGER,rout_name TEXT,weldgroup TEXT,weldpart TEXT)");
    }

    QSqlQuery query_spt_route;
    if(!query_spt_route.exec("CREATE TABLE IF NOT EXISTS spotroute_list (route1_spot_id INTEGER,route2_spot_id INTEGER,route3_spot_id INTEGER,route4_spot_id INTEGER,route5_spot_id INTEGER,route6_spot_id INTEGER,route7_spot_id INTEGER,route8_spot_id INTEGER)"))
    qDebug()<<"****create spotroute_list  ****"<<query_spt_route.lastError();

    QSqlQuery query_test_routelst;
    if(!query_test_routelst.exec("CREATE TABLE IF NOT EXISTS test_routelst (id INTEGER PRIMARY KEY autoincrement, route_name TEXT,weldgroup TEXT,weldpart TEXT) " ) )
    {}
#endif

    QSqlQuery query_default_test;
/*
    if(!query_default_test.exec("CREATE TABLE IF NOT EXISTS default_testdb(id INTEGER PRIMARY KEY autoincrement,img BLOB,img_icon BLOB,weld_id_row INTEGER,weld_id INTEGER,"
                                //   5              6            7             8              9        10                 11              12                13
                                  "weldgroup TEXT,weldpart TEXT,weldname TEXT,ok_nok INTEGER,icon BLOB,raw_wave_data BLOB,gate_th INTEGER,gate_start INTEGER,gate_end INTEGER ,"
                                //   14          15                  16            17         18                  19               20        21
                                  "gain INTEGER,set_velocity INTEGER,d_mes REAL ,i_mes REAL,checktime DATETIME, Selected INTEGER, dmin REAL,dmax REAL,"
                                //   22         23          24
                                  "imin REAL, imax REAL, reasons TEXT)" ) )
*/

    if(!query_default_test.exec("CREATE TABLE IF NOT EXISTS default_testdb(id INTEGER PRIMARY KEY autoincrement,name TEXT,x0 REAL,y0 REAL,r0 REAL,z0 REAL,"
                                //   5              6            7             8              9        10                 11              12                13
                                "x1 REAL,y1 REAL,r1 REAL,z1 REAL,x2 REAL,y2 REAL,r2 REAL,z2 REAL,"
                                //   22         23          24
                                 "line_v REAL,arc_v REAL,sort_order INTEGER)" ) )
    {

    }

    QSqlQuery query_tested_route_name;
    if(!query_tested_route_name.exec("CREATE TABLE IF NOT EXISTS tested_route_namelst (id INTEGER PRIMARY KEY autoincrement, route_name TEXT, user TEXT, date TEXT, slected INTEGER) " ) )
    qDebug()<<"****create tested_routenamelst  ****"<<query_tested_route_name.lastError();

    return true;
}
#endif // DATABASE_H
