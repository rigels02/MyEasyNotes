#include "inote.h"

int INote::getId() const
{
    return mid;
}

void INote::setId(int value)
{
    mid = value;
}

Note INote::getNoteObj() const
{
    Note note(this->getTitle(),this->getModTime(),this->getNote());

    return note;
}

QString INote::toString()
{
    return QString("%0:%1").arg(mid).arg(Note::toString());
}

INote::INote()
{

}

INote::INote(const int id, const QString ctitle, const QDate cdate, const QString ccontent):
    Note(ctitle,cdate,ccontent),mid(id)
{

}

INote::INote(const int id, const QString ctitle, const QString ccontent):
    Note(ctitle,QDate().currentDate(),ccontent),mid(id)
{

}

INote::INote(const int id, const Note note):
    Note(note.getTitle(),note.getModTime(),note.getNote()), mid(id)
{

}
