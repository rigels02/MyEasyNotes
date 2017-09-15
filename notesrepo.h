
#ifndef NOTESREPO_H
#define NOTESREPO_H


#include <QList>
#include "inote.h"
#include "io/iofileimpl.h"
#include "filter/wordfilter.h"

/**
 * @brief The NotesRepo class
 * This class works with classes INote and Note
 * INote is extension of Note (Derived: INote-->Note)
 * INote has only one additional member int Id ;
 * This id is assigned by this NotesRepo and
 * is used as key index to find Note object in the list.
 * This Id must be used by user when he wants to modify or
 * find the Note object by calling functions like edit(int id,..)
 * find(int id), remove(int id,INote inote) etc.
 */
class NotesRepo
{
public:
    NotesRepo();
    const QList<INote> finaAll() const;
    int count();
    const INote findById(int id) const;
    void edit(int id, INote& note);
    void edit(int id, Note& note);
    void remove(int id);
    const INote add(INote note);
     const INote add(Note note);
    void append(QList<INote> inotes);
    void append(QList<Note> anotes);
    void saveAll(QDateTime time,QList<Note> anotes);
    QDateTime getLastModifyTime();
    void removeAll();
    void importData(const QList<Note> nnotes);
    void importData(const QList<INote> inotes);
    QList<INote> inotesFromNotes(const QList<Note> notes);
    QList<Note> notesFromINotes(const QList<INote> inotes);


    void setFilter(const QString &value);

private:
    QList<INote> notes;
    IOFileImpl io;
    QStringList searchWords;
};

#endif // NOTESREPO_H
