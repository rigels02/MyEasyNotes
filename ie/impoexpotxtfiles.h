#ifndef IMPOEXPOTXTFILES_H
#define IMPOEXPOTXTFILES_H

#include <QString>
#include <QList>
#include "note.h"

#include <QDebug>

class ImpoExpoTxtFiles
{
public:
    ImpoExpoTxtFiles(QStringList files);
    QList<Note> getNotes();
private:
    QStringList files;

    QString stripFileName(QString filePath);
};

#endif // IMPOEXPOTXTFILES_H
