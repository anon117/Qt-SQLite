#ifndef DBHANDLER_H
#define DBHANDLER_H


#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>

class dbhandler : public QObject
{
    Q_OBJECT
public:
    explicit dbhandler(QObject *parent = 0);

    bool openSQLiteDB();
    void closeSQLiteDB();
    bool createTable();
    bool insertRow(QString name, int age);
    bool selectAll();
    QSqlError lastError();

private:
    QSqlDatabase dbLink;

signals:

public slots:

};

#endif // DBHANDLER_H
