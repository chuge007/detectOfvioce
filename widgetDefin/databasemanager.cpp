#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    // 初始化时不打开数据库，调用 openDb 或 createNewDb 时才打开
}

DatabaseManager::~DatabaseManager()
{
    closeDb();
}

bool DatabaseManager::openDb(const QString &db_name)
{
    // 如果连接已存在，关闭并移除旧连接
    if (QSqlDatabase::contains(connName)) {
        QSqlDatabase oldDb = QSqlDatabase::database(connName, false);
        if (oldDb.isOpen()) oldDb.close();
        QSqlDatabase::removeDatabase(connName);
    }

    db = QSqlDatabase::addDatabase("QSQLITE", connName);
    db.setDatabaseName(db_name);

    if (!db.open()) {
        QMessageBox::warning(nullptr, "Database", "Failed to open database! Error: " + db.lastError().text());
        return false;
    }

    // 优化项
    db.exec("PRAGMA synchronous = OFF");
    db.exec("PRAGMA journal_mode = MEMORY");
    db.exec("PRAGMA page_size = 32768");
    db.exec("PRAGMA cache_size = 8000");

    QStringList connections = QSqlDatabase::connectionNames();
    qDebug() << "Current connections:";
    for (const QString &name : connections) {
        qDebug() << "  - " << name;
    }
    return true;
}

bool DatabaseManager::createNewDb(const QString &dbfilename)
{
    // 关闭并移除旧连接
    if (db.isOpen()) {
        db.close();
    }
    QSqlDatabase::removeDatabase(connName);

    db = QSqlDatabase::addDatabase("QSQLITE", connName);
    db.setDatabaseName(dbfilename);

    if (!db.open()) {
        QMessageBox::warning(nullptr, "Database", dbfilename + " create new db failed! Error: " + db.lastError().text());
        qDebug() << "Database error: " << db.lastError().text();
        return false;
    }

    qDebug() << "Database opened successfully!";
    return true;
}

bool DatabaseManager::execQuery(const QString &queryStr)
{
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    if (!query.exec(queryStr)) {
        qDebug() << "Query failed: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::createTable()
{
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS test_table ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "name TEXT, "
                               "age INTEGER)";
    return execQuery(createTableQuery);
}

bool DatabaseManager::insertData(const QString &name, int age)
{
    QString insertQuery = QString("INSERT INTO test_table (name, age) VALUES ('%1', %2)").arg(name).arg(age);
    return execQuery(insertQuery);
}

bool DatabaseManager::getData()
{
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
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

void DatabaseManager::closeDb()
{
    if (!db.isValid())
        return;

    if (db.isOpen()) {
        db.close();
    }

    // 延迟移除连接，确保所有QSqlQuery/QSqlTableModel等对象销毁完毕
    QTimer::singleShot(0, [this]() {
        QSqlDatabase::removeDatabase(connName);
    });

    QStringList connections = QSqlDatabase::connectionNames();
    qDebug() << "Current connections:";
    for (const QString &name : connections) {
        qDebug() << "  - " << name;
    }

}
