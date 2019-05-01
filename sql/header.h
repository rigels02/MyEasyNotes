#ifndef HEADER_H
#define HEADER_H

#include <QString>
#include <QDateTime>



class Header {

public:
    long getId() const {return id;}
    void setId(long value){id= value;}

    QString getTitle() const {return title;}
    void setTitle(const QString &value){ title= value;}

    QDateTime getModTime() const {return modTime;}
    void setModTime(const QDateTime &value) { modTime =value;}

private:
    long id;
    QString title;
    QDateTime modTime;


};
#endif // HEADER_H

