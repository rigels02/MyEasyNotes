#ifndef HEADER_H
#define HEADER_H

#include <QString>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "inote.h"


class Header {

public:
    long getId() const {return id;}
    void setId(long value){id= value;}

    QString getTitle() const {return title;}
    void setTitle(const QString &value){ title= value;}

    QDateTime getModTime() const {return modTime;}
    void setModTime(const QDateTime &value) { modTime =value;}

    QString toString();
    static QJsonDocument toJsonArrayDoc(const QList<Header> headers);
    static QList<Header>   fromJsonArrayDoc(const QJsonDocument doc);
    static QJsonDocument toJsonArrayNotesDoc(const QList<Note> notes);
    static QList<INote>   fromJsonArrayNotesDoc(const QJsonDocument doc);
    static QJsonArray toJsonArray(const QList<Note> notes);
    static QList<Note> fromJsonArray(const QJsonArray jnotes);


    static QDateTime makeQDateTimeFromEpoch(qint64 msec);

    static qint64 makeMSecSinceEpochDT(QDateTime date);

    static QDate makeQDateFromEpoch(qint64 msec);

    static qint64 makeMSecSinceEpoch(QDate date);

    static QList<Note> convertINotesList(QList<INote> inotes);

    static QList<INote> convertNotesList(QList<Note> notes);

private:
    long id;
    QString title;
    QDateTime modTime;


};


#endif // HEADER_H


