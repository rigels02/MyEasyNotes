#include "notesbook.h"

NotesBook::NotesBook()
{

}

NotesBook::NotesBook(QString title)
{
    this->setTitle(title);
    this->setModTime(QDateTime::currentDateTime());
}

NotesBook::NotesBook(QString title, QDateTime time)
{
    this->setTitle(title);
    this->setModTime(time);
}

QList<Note> NotesBook::getNotes() const
{
    return notes;
}

void NotesBook::setNotes(const QList<Note> &value)
{
    notes = value;
}

const QString id_str="id";
const QString title_str="title";
const QString modTime_str="modTime";
const QString notes_str="notes";

QJsonDocument NotesBook::toJsonDoc(const NotesBook notesBook)
{
    QJsonArray note_array;
    QJsonObject jbook;
    jbook.insert(title_str,notesBook.getTitle());

    jbook.insert(modTime_str,Header::makeMSecSinceEpochDT(notesBook.getModTime()));
    QList<Note> notes= notesBook.getNotes();
    note_array= Header::toJsonArray(notes);
    jbook.insert(notes_str,note_array);
    //QJsonObject finalObj;
    //finalObj.insert("notes",QJsonValue(headers_array));
    QJsonDocument jdoc;
   // QTextCodec
    jdoc.setObject(jbook);
    qDebug()<<jdoc.toJson();
    return jdoc;
}

NotesBook NotesBook::fromJsonDoc(const QJsonDocument doc)
{
    NotesBook book;
    //QJsonObject rootObj = doc.object();
    //QJsonValue av = rootObj.value("notes");
    QJsonObject jbook= doc.object();
    book.setTitle(jbook.value(title_str).toString());
    book.setModTime(Header::makeQDateTimeFromEpoch(jbook.value(modTime_str).toDouble()));
    QJsonArray jnotes= jbook.value(notes_str).toArray();
    QList<Note> notes = Header::fromJsonArray(jnotes);
    book.setNotes(notes);
    return book;

}
