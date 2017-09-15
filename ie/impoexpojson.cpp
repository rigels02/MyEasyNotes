#include "impoexpojson.h"

ImpoExpoJson::ImpoExpoJson()
{

}

void ImpoExpoJson::expoJson(const QString filePath, const QList<Note> notes)
{
    QFile fi(filePath);
    fi.open(QFile::WriteOnly);

   QJsonDocument doc= toJsonArrayDoc(notes);
    fi.write(doc.toJson(QJsonDocument::Compact));
    fi.close();
}
/**
 * throws Exception
 * @brief ImpoExpoJson::impoJson
 * @param filePath
 * @return
 */
QList<Note> ImpoExpoJson::impoJson(const QString filePath)
{
    QFile fi(filePath);
    fi.open(QFile::ReadOnly);
   QJsonDocument jdoc = QJsonDocument::fromJson(fi.readAll());

   if(jdoc.isNull()){
       fi.close();
       throw "JSON Doc parsing error!";
   }

    fi.close();
    return fromJsonArrayDoc(jdoc);
}

void ImpoExpoJson::expoNotesBookJson(const QString filePath, const NotesBook book)
{
    QFile fi(filePath);
    fi.open(QFile::WriteOnly);

   QJsonDocument doc= NotesBook::toJsonDoc(book);
    fi.write(doc.toJson(QJsonDocument::Compact));
    fi.close();
}
/**
 * throws Exception
 * @brief ImpoExpoJson::impoJson
 * @param filePath
 * @return
 */
NotesBook ImpoExpoJson::impoNotesBookJson(const QString filePath)
{
    QFile fi(filePath);
    fi.open(QFile::ReadOnly);
   QJsonDocument jdoc = QJsonDocument::fromJson(fi.readAll());

   if(jdoc.isNull()){
       fi.close();
       throw "JSON Doc parsing error!";
   }

    fi.close();
    return NotesBook::fromJsonDoc(jdoc);
}



const QString title_str("title");
const QString note_str("note");
const QString modTime_str("modTime");

QJsonDocument ImpoExpoJson::toJsonArrayDoc(const QList<Note> notes)
{
    QJsonArray notes_array;

    foreach (Note note, notes) {
        QJsonObject itemData;
        itemData.insert(title_str,note.getTitle());
        itemData.insert(modTime_str,ImpoExpoJson::makeMSecSinceEpoch(note.getModTime()));
        itemData.insert(note_str,note.getNote());
        notes_array.append(QJsonValue(itemData));
    }
    QJsonObject finalObj;
    finalObj.insert("notes",QJsonValue(notes_array));
    QJsonDocument jdoc;
    jdoc.setObject(finalObj);
    return jdoc;
}

QList<Note> ImpoExpoJson::fromJsonArrayDoc(const QJsonDocument doc)
{
    QList<Note> notes;
    QJsonObject rootObj = doc.object();
    QJsonValue av = rootObj.value("notes");
    QJsonArray array = av.toArray();
    foreach (const QJsonValue &val, array) {
        Note note;
        note.setTitle(val.toObject().value(title_str).toString());
        double num = val.toObject().value(modTime_str).toDouble();
        QDate dd = ImpoExpoJson::makeQDateFromEpoch(num);
        note.setModTime(dd);
        //note.setModTime(QDate().currentDate());
        note.setNote(val.toObject().value(note_str).toString());
        notes.append(note);
    }
    return notes;
}

/**
 * @brief makeQDateFromEpoch - Get QDate from Java Date
 * @param msec Java Date timestamp
 * @return QDate
 */
QDate ImpoExpoJson::makeQDateFromEpoch(qint64 msec){
     QDateTime dt;
     dt.setMSecsSinceEpoch(msec);
     return dt.date();
}
/**
 * @brief makeMSecSinceEpoch Get java Date from QDate
 * @param date QDate value
 * @return Java Date timestamp (Time part is 0)
 */
qint64 ImpoExpoJson::makeMSecSinceEpoch(QDate date){
    QDateTime dt;
    dt.setDate(date);
    dt.setTime(QTime(0,0)); //Time part is 0
    return dt.toMSecsSinceEpoch(); //Java Date
}
/**
 * @brief makeQDateFromEpoch - Get QDateTime from Java Date
 * @param msec Java Date timestamp
 * @return QDateTime
 */
QDateTime ImpoExpoJson::makeQDateTimeFromEpoch(qint64 msec){
     QDateTime dt;
     dt.setMSecsSinceEpoch(msec);
     return dt;
}
/**
 * @brief makeMSecSinceEpoch Get java Date from QDateTime
 * @param date QDateTime value
 * @return Java Date timestamp
 */
qint64 ImpoExpoJson::makeMSecSinceEpochDT(QDateTime date){
    QDateTime dt;
    dt= date;
    return dt.toMSecsSinceEpoch(); //Java Date
}

