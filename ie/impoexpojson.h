#ifndef IMPOEXPOJSON_H
#define IMPOEXPOJSON_H

#include <QString>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

//#include "note.h"
#include "rest/notesbook.h"

#include <QDebug>

class ImpoExpoJson
{
public:
    ImpoExpoJson();
    void expoJson(const QString filePath, const QList<Note> notes);
    QList<Note> impoJson(const QString filePath);
    void expoNotesBookJson(const QString filePath, const NotesBook book);
    NotesBook impoNotesBookJson(const QString filePath);
    static QJsonDocument toJsonArrayDoc(const QList<Note> notes);
    static QList<Note>   fromJsonArrayDoc(const QJsonDocument doc);
    static QJsonDocument toJsonNoteBookDoc(const QList<Note> notes);

private:
    QList<Note> notes;

    static QDate makeQDateFromEpoch(qint64 msec);
    static qint64 makeMSecSinceEpoch(QDate date);
    static QDateTime makeQDateTimeFromEpoch(qint64 msec);
    static qint64 makeMSecSinceEpochDT(QDateTime date);
};

#endif // IMPOEXPOJSON_H
