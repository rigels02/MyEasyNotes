#include "notesrepo.h"

NotesRepo::NotesRepo()
{
    /**
    notes = QList<Note>();
    notes.append(Note("Note_1","Content_1"));
    notes.append(Note("Note_2","Content_2"));
    notes.append(Note("Note_3","Content_3"));
    **/
   io= IOFileImpl();
   QList<Note> nnotes;
   nnotes= io.loadAll();
   notes= inotesFromNotes(nnotes);
   //io.saveAll(notes);
  //QList<Note> noots= io.loadAll();
}

const QList<INote> NotesRepo::finaAll() const
{
    QList<INote> filtered = WordFilter::doFilter(notes,searchWords);
    return filtered;
}

int NotesRepo::count()
{
    QList<INote> filtered = WordFilter::doFilter(notes,searchWords);
    return filtered.size();
}

const INote NotesRepo::findById(int id) const
{
  return notes.at(id);
}

/**
  *Uses Exception
 * @brief NotesRepo::edit
 * @param id
 * @param note
 */
void NotesRepo::edit(int id, INote& note)
{   if(id!= note.getId())
          throw "Illegal index used!";
     note.setModTime(QDate().currentDate());
    notes.replace(id,note);
    QList<Note> nnotes;
    nnotes= notesFromINotes(notes);
    io.saveAll(nnotes);
}

void NotesRepo::edit(int id, Note& note)
{
    INote inote(0,note);
    inote.setId(id);
    edit(id,inote);
}

void NotesRepo::remove(int id)
{

   notes.removeAt(id);
   QList<Note> nnotes;
   nnotes= notesFromINotes(notes);
   io.saveAll(nnotes);
}

const INote NotesRepo::add(INote note)
{
    note.setModTime(QDate().currentDate());
    note.setId(notes.size());
    notes.append(note);
    QList<Note> nnotes;
    nnotes= notesFromINotes(notes);
    io.saveAll(nnotes);
    return note;
}

const INote NotesRepo::add(Note note)
{
    INote inote(0,note);
    inote.setId(notes.size());
    add(inote);
    return inote;
}

void NotesRepo::append(QList<INote> inotes)
{
    int idx=notes.size();
    foreach (INote inote, inotes) {
        inote.setModTime(QDate().currentDate());
        inote.setId(idx);
        notes.append(inote);
        idx++;
    }
    io.saveAll(notesFromINotes(notes));
}

void NotesRepo::append(QList<Note> anotes)
{
    int idx=notes.size();
    foreach (Note note, anotes) {
        note.setModTime(QDate().currentDate());
        INote inote(idx,note);
        notes.append(inote);
        idx++;
    }
    io.saveAll(notesFromINotes(notes));
}

void NotesRepo::saveAll(QDateTime time, QList<Note> anotes)
{
    int idx=0;
    foreach (Note note, anotes) {
        //note.setModTime(QDate().currentDate());
        INote inote(idx,note);
        notes.append(inote);
        idx++;
    }
    io.saveAllWithTime(time,notesFromINotes(notes));
}

QDateTime NotesRepo::getLastModifyTime()
{
   return io.getModTime();
}

void NotesRepo::removeAll()
{
    notes.clear();
    io.saveAll(notesFromINotes(notes));
}

void NotesRepo::importData(const QList<Note> nnotes)
{
    notes.clear();
    int idx=0;
    foreach (Note note, nnotes) {
        //note.setModTime(QDate().currentDate());
        INote inote(idx,note);
        notes.append(inote);
        idx++;
    }
    io.saveAll(nnotes);
}

void NotesRepo::importData(const QList<INote> inotes)
{
    notes.clear();

    int idx=0;
    foreach (INote inote, inotes) {
        //note.setModTime(QDate().currentDate());
        inote.setId(idx);
        notes.append(inote);
        idx++;
    }

    io.saveAll(notesFromINotes(notes));
}

QList<INote> NotesRepo::inotesFromNotes(const QList<Note> notes)
{
    QList<INote> inotes;
    int idx=0;
    foreach (Note note, notes) {
        INote inote(idx,note);
        inotes.append(inote);
        idx++;
    }
    return inotes;
}

QList<Note> NotesRepo::notesFromINotes(const QList<INote> inotes)
{
    QList<Note> nnotes;
    foreach (INote inote, inotes) {
        Note note;
        note= inote.getNoteObj();
        nnotes.append(note);
    }
    return nnotes;
}


void NotesRepo::setFilter(const QString &value)
{
    searchWords = WordFilter::prepareWords(value);
}
