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
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtCore/QFile>
#include <QtCore/QBuffer>
#include <QtCore/QByteArray>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPixmap>
#include <QDebug>

static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "unique_connection_name");

// 打开数据库
static bool openDb(const QString &db_name) {
    // 确保关闭并移除数据库连接
    if (db.isOpen()) {
        db.close();
    }
    QSqlDatabase::removeDatabase("unique_connection_name");

    db = QSqlDatabase::addDatabase("QSQLITE", "unique_connection_name");
    db.setDatabaseName(db_name);

    if (!db.open()) {
        QMessageBox::warning(nullptr, "Database", "Failed to open database! Error: " + db.lastError().text());
        return false;
    }

    // 配置优化项
    db.exec("PRAGMA synchronous = OFF");
    db.exec("PRAGMA journal_mode = MEMORY");
    db.exec("PRAGMA page_size = 32768");
    db.exec("PRAGMA cache_size = 8000");
    return true;
}

// 创建新数据库
static bool createNewDb(const QString &dbfilename) {
    // 如果已有数据库连接，则先关闭并移除
    if (db.isOpen()) {
        db.close();
    }
    QSqlDatabase::removeDatabase("unique_connection_name");

    // 创建新的数据库连接
    db = QSqlDatabase::addDatabase("QSQLITE", "unique_connection_name");
    db.setDatabaseName(dbfilename);

    if (!db.open()) {
        QMessageBox::warning(nullptr, "Database", dbfilename + " create new db failed! Error: " + db.lastError().text());
        qDebug() << "Database error: " << db.lastError().text();
        return false;
    }

    qDebug() << "Database opened successfully!";
    return true;
}

// 执行数据库查询
static bool execQuery(const QString &queryStr) {
    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "Query failed: " << query.lastError().text();
        return false;
    }
    return true;
}

// 创建表格
static bool createTable() {
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS test_table ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "name TEXT, "
                               "age INTEGER)";
    return execQuery(createTableQuery);
}

// 插入数据
static bool insertData(const QString &name, int age) {
    QString insertQuery = QString("INSERT INTO test_table (name, age) VALUES ('%1', %2)").arg(name).arg(age);
    return execQuery(insertQuery);
}

// 获取数据
static bool getData() {
    QSqlQuery query;
    if (!query.exec("SELECT * FROM test_table")) {
        qDebug() << "Select failed: " << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        int age = query.value(2).toInt();
        qDebug() << "ID: " << id << ", Name: " << name << ", Age: " << age;
    }

    return true;
}

// 关闭数据库
static void closeDb() {
<<<<<<< HEAD
=======

    // 关闭数据库连接
    QSqlDatabase db = QSqlDatabase::database("unique_connection_name");
>>>>>>> c82df02 (界面)
    if (db.isOpen()) {
        db.close();
    }
    QSqlDatabase::removeDatabase("unique_connection_name");
}

#endif // DATABASE_H
