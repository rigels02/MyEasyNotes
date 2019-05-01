#include "sqlmodel.h"

SqlModel::SqlModel()
{
    isDBOK= false;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("mydb");
    db.setUserName("APP");
    db.setPassword("app");
    isDBOK = db.open();
}

QList<Header> SqlModel::getHeaders()
{
    if(!isDBOK)
        throw QString("DB not opened...");
    QList<Header> headers;
       QSqlTableModel model;
       model.setTable(dHeader);
       bool ok= model.select();
       if(!ok) return headers;
       for(int i=0; i< model.rowCount(); i++){
           Header header;

           header.setId(model.record(i).value(SHeader.id).toLongLong());
           header.setTitle(model.record(i).value(SHeader.title).toString());
           headers.append(header);
       }
   return headers;
}
