#include <QCoreApplication>
#include <dbhandler.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    dbhandler handler;
    if (handler.openSQLiteDB()) qDebug() << "Nyitva";
    if (!handler.createTable()) qDebug() << "Nem hoztam létre táblát";
    if (!handler.insertRow("Apád", 22)) qDebug() << "Nen szúrtam be sort";
    handler.selectAll();
    handler.closeSQLiteDB();

    return a.exec();
}
