#include "note.h"

Note::Note():title(""),note(""),modTime(QDate::currentDate())
{

}

Note::Note(QString stitle, QString snote):title(stitle),note(snote),modTime(QDate::currentDate()){
   // modTime=QDate().currentDate();
}

Note::Note(QString stitle, QDate cdate, QString snote):
    title(stitle),note(snote),modTime(cdate)
{

}


QString Note::toString(){

   return QString("%1:%2:%3").arg( this->title).arg(QDate(this->modTime).toString("dd/MM/yyyy")).arg(this->note);
}

QString Note::getTitle() const
{
    return title;
}

void Note::setTitle(const QString &value)
{
    title = value;
}

QString Note::getNote() const
{
    return note;
}

void Note::setNote(const QString &value)
{
    note = value;
}

QDate Note::getModTime() const
{
    return modTime;
}

void Note::setModTime(const QDate &value)
{
    modTime = value;
}

void Note::writeData(QDataStream &ds)
{
    ds<<this->getTitle();
    ds<<this->getModTime();
    ds<<this->getNote();
}

void Note::readData(QDataStream &ds)
{
    QString title;
    ds>> title;
    this->setTitle(title);
    QDate dd;
    ds>> dd;
    this->setModTime(dd);
    QString note;
    ds>>note;
    this->setNote(note);
}
