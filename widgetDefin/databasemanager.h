#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool openDb(const QString &db_name);
    bool createNewDb(const QString &dbfilename);
    bool execQuery(const QString &queryStr);
    bool createTable();
    bool insertData(const QString &name, int age);
    bool getData();
    void closeDb();
    QSqlDatabase db;
private:

    const QString connName = "unique_connection_name";
};

#endif // DATABASEMANAGER_H
