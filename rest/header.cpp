#include "rest/header.h"



QString Header::toString(){
    return QString("Header: id=%0, Title= %1, modTime=%2")
            .arg(id).arg(title).arg(modTime.toString("dd/MM/yyyy HH:mm:ss"));
}

const QString id_str="id";
const QString title_str="title";
const QString modTime_str="modTime";
const QString note_str="note";

QJsonDocument Header::toJsonArrayDoc(const QList<Header> headers)
{
    QJsonArray headers_array;

    foreach (Header header, headers) {
        QJsonObject itemData;
        itemData.insert(id_str,double(header.getId()));
        itemData.insert(title_str,header.getTitle());
        itemData.insert(modTime_str,Header::makeMSecSinceEpochDT(header.getModTime()));

        headers_array.append(QJsonValue(itemData));
    }
    //QJsonObject finalObj;
    //finalObj.insert("notes",QJsonValue(headers_array));
    QJsonDocument jdoc;
    jdoc.setArray(headers_array);
    return jdoc;
}

QList<Header> Header::fromJsonArrayDoc(const QJsonDocument doc)
{
    QList<Header> headers;
    //QJsonObject rootObj = doc.object();
    //QJsonValue av = rootObj.value("notes");
    QJsonArray array = doc.array();
    foreach (const QJsonValue &val, array) {
        Header header;
        header.setId(val.toObject().value(id_str).toDouble());
        header.setTitle(val.toObject().value(title_str).toString());
        double num = val.toObject().value(modTime_str).toDouble();
        QDateTime dd = Header::makeQDateTimeFromEpoch(num);
        header.setModTime(dd);

        headers.append(header);
    }
    return headers;
}

/**
QJsonDocument Header::toJsonArrayDoc(const QList<Header> headers)
{
    QJsonArray headers_array;

    foreach (Header header, headers) {
        QJsonObject itemData;
        itemData.insert(id_str,double(header.getId()));
        itemData.insert(title_str,header.getTitle());
        itemData.insert(modTime_str,Header::makeMSecSinceEpochDT(header.getModTime()));

        headers_array.append(QJsonValue(itemData));
    }
    //QJsonObject finalObj;
    //finalObj.insert("notes",QJsonValue(headers_array));
    QJsonDocument jdoc;
    jdoc.setArray(headers_array);
    return jdoc;
}

QList<Header> Header::fromJsonArrayDoc(const QJsonDocument doc)
{
    QList<Header> headers;
    //QJsonObject rootObj = doc.object();
    //QJsonValue av = rootObj.value("notes");
    QJsonArray array = doc.array();
    foreach (const QJsonValue &val, array) {
        Header header;
        header.setId(val.toObject().value(id_str).toDouble());
        header.setTitle(val.toObject().value(title_str).toString());
        double num = val.toObject().value(modTime_str).toDouble();
        QDateTime dd = Header::makeQDateTimeFromEpoch(num);
        header.setModTime(dd);

        headers.append(header);
    }
    return headers;
}
**/

QJsonDocument Header::toJsonArrayNotesDoc(const QList<Note> notes)
{
    QJsonArray note_array;

    foreach (Note note, notes) {
        QJsonObject itemData;
        //itemData.insert(id_str,double(note.getId()));
        itemData.insert(title_str,note.getTitle());
        itemData.insert(note_str,note.getNote());
        //itemData.insert(modTime_str,Header::makeMSecSinceEpoch(note.getModTime()));
        itemData.insert(modTime_str,note.getModTime().toString("yyyy-MM-dd"));


        note_array.append(QJsonValue(itemData));
    }
    //QJsonObject finalObj;
    //finalObj.insert("notes",QJsonValue(headers_array));
    QJsonDocument jdoc;
   // QTextCodec
    jdoc.setArray(note_array);

    return jdoc;
}

QJsonArray Header::toJsonArray(const QList<Note> notes)
{
    QJsonArray note_array;

    foreach (Note note, notes) {
        QJsonObject itemData;
        //itemData.insert(id_str,double(note.getId()));
        itemData.insert(title_str,note.getTitle());
        itemData.insert(note_str,note.getNote());
        //itemData.insert(modTime_str,Header::makeMSecSinceEpoch(note.getModTime()));
        itemData.insert(modTime_str,note.getModTime().toString("yyyy-MM-dd"));


        note_array.append(QJsonValue(itemData));
    }


    return note_array;
}

QList<Note> Header::fromJsonArray(const QJsonArray jnotes)
{
    QList<Note> notes;
    //QJsonObject rootObj = doc.object();
    //QJsonValue av = rootObj.value("notes");

    foreach (const QJsonValue &val, jnotes) {
        Note note;
        //note.setId(val.toObject().value(id_str).toDouble());
        note.setTitle(val.toObject().value(title_str).toString());
        note.setNote(val.toObject().value(note_str).toString());

        QString num = val.toObject().value(modTime_str).toString();
        //QDate dd = Header::makeQDateFromEpoch(num);
        note.setModTime(QDate::fromString(num,"yyyy-MM-dd"));

        notes.append(note);
    }
    return notes;
}

QList<INote> Header::fromJsonArrayNotesDoc(const QJsonDocument doc)
{
    QList<INote> notes;
    //QJsonObject rootObj = doc.object();
    //QJsonValue av = rootObj.value("notes");
    QJsonArray array = doc.array();
    foreach (const QJsonValue &val, array) {
        INote note;
        note.setId(val.toObject().value(id_str).toDouble());
        note.setTitle(val.toObject().value(title_str).toString());
        note.setNote(val.toObject().value(note_str).toString());

        QString num = val.toObject().value(modTime_str).toString();
        //QDate dd = Header::makeQDateFromEpoch(num);
        note.setModTime(QDate::fromString(num,"yyyy-MM-dd"));

        notes.append(note);
    }
    return notes;
}


/**
 * @brief makeQDateFromEpoch - Get QDateTime from Java Date
 * @param msec Java Date timestamp
 * @return QDateTime
 */
QDateTime Header::makeQDateTimeFromEpoch(qint64 msec){
     QDateTime dt;
     dt.setMSecsSinceEpoch(msec);
     return dt;
}
/**
 * @brief makeMSecSinceEpoch Get java Date from QDateTime
 * @param date QDateTime value
 * @return Java Date timestamp
 */
qint64 Header::makeMSecSinceEpochDT(QDateTime date){
    QDateTime dt;
    dt= date;
    return dt.toMSecsSinceEpoch();  //Java Date

}

/**
 * @brief makeQDateFromEpoch - Get QDate from Java Date
 * @param msec Java Date timestamp
 * @return QDate
 */
QDate Header::makeQDateFromEpoch(qint64 msec){
     QDateTime dt;
     dt.setMSecsSinceEpoch(msec);
     return dt.date();
}
/**
 * @brief makeMSecSinceEpoch Get java Date from QDate
 * @param date QDate value
 * @return Java Date timestamp (Time part is 0)
 */
qint64 Header::makeMSecSinceEpoch(QDate date){
    QDateTime dt;
    dt.setDate(date);
    dt.setTime(QTime(0,0)); //Time part is 0
    return dt.toMSecsSinceEpoch(); //Java Date
}
QList<Note> Header::convertINotesList(QList<INote> inotes){
    QList<Note> notes;
    foreach (INote inote, inotes) {
       Note note(inote.getTitle(), inote.getModTime(),inote.getNote());
       notes.append(note);
    }
    return notes;
}

QList<INote> Header::convertNotesList(QList<Note> notes)
{
    QList<INote> inotes;
    foreach (Note note, notes) {
       INote inote(0,note.getTitle(), note.getModTime(),note.getNote());
       inotes.append(inote);
    }
    return inotes;
}
