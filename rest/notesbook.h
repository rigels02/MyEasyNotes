#ifndef NOTESBOOK_H
#define NOTESBOOK_H


#include <QDebug>

#include "header.h"
#include "note.h"

class NotesBook : public Header
{
public:
    NotesBook();
    NotesBook(QString title);
    NotesBook(QString title,QDateTime time);

    QList<Note> getNotes() const;
    void setNotes(const QList<Note> &value);
    static QJsonDocument toJsonDoc(const NotesBook notesBook);
    static NotesBook   fromJsonDoc(const QJsonDocument doc);

private:
    QList<Note> notes;
};

#endif // NOTESBOOK_H
