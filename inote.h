#ifndef INOTE_H
#define INOTE_H

#include <QString>
#include <QDate>

#include "note.h"

class INote : public Note
{
int mid;

public:
    INote();
    INote(const int id, const QString ctitle,const QDate cdate, const QString ccontent);
     INote(const int id, const QString ctitle, const QString ccontent);
    INote(const int id,const Note note);
    int getId() const;
    void setId(int value);
    Note getNoteObj() const;
    QString toString() override;
};

#endif // INOTE_H
