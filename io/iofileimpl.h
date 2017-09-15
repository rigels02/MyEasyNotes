#ifndef IOFILEIMPL_H
#define IOFILEIMPL_H

#include <QDataStream>
#include <QString>
#include <QList>
#include <QDate>
#include <QMessageBox>
#include <QException>

#include "note.h"

#include <QDebug>

class IOFileImpl
{
public:
    IOFileImpl();
    void saveAll(QList<Note> data);

    QList<Note> loadAll();

    QDateTime getModTime() const;

    void saveAllWithTime(QDateTime time, QList<Note> data);
private:
    void createDataFile(QFile &fi);
    void openDataFile(QFile &fi);
    void writeHeader(QDataStream &ds);
    void readHeader(QDataStream &ds);
    QString composeFileName();

private:
    //file modification time stamp
    QDateTime modTime;
};

#endif // IOFILEIMPL_H
