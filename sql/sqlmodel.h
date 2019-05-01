#ifndef SQLMODEL_H
#define SQLMODEL_H


#include <QString>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>

#include <QDebug>

#include "header.h"
#include "note.h"

#define dHeader "header"
#define dHeaderNotes "header_notes"
#define dNote "note"

struct {
    const QString id="id";
    const QString modtime="mod_time";
    const QString title="title";

}SHeader;

struct {
    const QString notesBookid="notes_book_id";
    const QString notesid="notes_id";
}SHeaderNotes;

struct {
    const QString id="id";
    const QString modtime="mod_time";
    const QString title="title";
    const QString note="note";

}SNote;

class SqlModel
{

public:
    SqlModel();
    QList<Header> getHeaders();

private:
    QSqlDatabase db;
    bool isDBOK;
};

#endif // SQLMODEL_H
