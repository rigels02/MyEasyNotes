#include "impoexpotxtfiles.h"

ImpoExpoTxtFiles::ImpoExpoTxtFiles(QStringList files)
{
    this->files= files;
}
/**
 * throws Exception
 * @brief ImpoExpoTxtFiles::getNotes
 * @return
 */
QList<Note> ImpoExpoTxtFiles::getNotes()
{
    QList<Note> notes;
    foreach (QString fn, files) {
        QFile fi(fn);
        bool ok =fi.open(QIODevice::ReadOnly);
        if(!ok) throw QString("Can not open file: %0").arg(fn);

        Note note;
        note.setTitle(stripFileName(fn));
        QTextStream ts(&fi);
        QString txt = ts.readAll();

        note.setNote(txt);
        notes.append(note);
        fi.close();
    }
    return notes;
}

QString ImpoExpoTxtFiles::stripFileName(QString filePath)
{

  QString result, result1;
  result= filePath.section('/',-1,-1);
  result1= result.mid(0,result.lastIndexOf('.'));
  return result1;
}
