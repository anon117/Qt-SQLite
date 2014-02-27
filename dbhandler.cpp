#include "dbhandler.h"

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QDir>
#include <QDebug>

dbhandler::dbhandler(QObject *parent) :
    QObject(parent)
{
}

bool dbhandler::openSQLiteDB()
{
    // SQL Driver kiválasztása
    dbLink = QSqlDatabase::addDatabase("QSQLITE");

    // ha szükséges létrehozzuk az adatbázist (file)
    QString dbPath(QDir::home().path());
    dbPath.append(QDir::separator()).append("proba").append(QDir::separator()).append("cute-db.sqlite");
    dbPath = QDir::toNativeSeparators(dbPath);

    // egy kis debug
    qDebug() << dbPath;

    // adatbázis beállítása
    dbLink.setDatabaseName(dbPath);

    // adatbázis megnyítása
    return dbLink.open();
}

void dbhandler::closeSQLiteDB()
{
    // adatbázis lezárása
    dbLink.close();
}

bool dbhandler::createTable()
{
    bool ret = false;

    // Nyitva van-e az adatbázis?
    if (dbLink.isOpen())
    {
        QSqlQuery query;
        query.prepare(QString("CREATE TABLE person (name varchar(50), age integer)"));
        if (!query.exec())
            qDebug() << "Create table: " << dbLink.lastError().text();
        else
            ret = 1;
    }

    return ret;
}

bool dbhandler::insertRow(QString name, int age)
{
    bool ret = false;

    // Nyitva van-e az adatbázis?
    if (dbLink.isOpen())
    {
        QSqlQuery query;
        query.prepare(QString("insert into person values ('%0', %1)").arg(name).arg(age));
        if (!query.exec())
            qDebug() << "Insert: " << ret << this->lastError();
        else
            ret = 1;
    }

    return ret;
}

bool dbhandler::selectAll()
{
    bool ret = false;

    // Nyitva van-e az adatbázis?
    if (dbLink.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("SELECT name, age FROM person"));
        qDebug() << dbLink.lastError().text();

        while (query.next())
        {
            qDebug() << "Név:" << query.value(0).toString() << " Kor: " << query.value(1).toString();
        }
    }

    return ret;
}

QSqlError dbhandler::lastError()
{
    return dbLink.lastError();
}
