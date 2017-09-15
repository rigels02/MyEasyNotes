#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QDate>
#include <QDataStream>

class Note
{
public:
    Note();
    Note(QString stitle,QString snote);
    Note(QString stitle, QDate cdate,QString snote);
    virtual ~Note(){}
    virtual QString toString();

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getNote() const;
    void setNote(const QString &value);

    QDate getModTime() const;
    void setModTime(const QDate &value);
    void writeData(QDataStream &ds);
    void readData(QDataStream &ds);

private:
    QString title;
    QString note;
    QDate modTime;
};

#endif // NOTE_H
