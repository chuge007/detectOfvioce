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

    return true;
}
#endif // DATABASE_H
