#include "wordfilter.h"



QList<INote> WordFilter::doFilter(const QList<INote> &list, const QString words)
{
    if(list.isEmpty() || words.isEmpty()) return list;
    QStringList sw = prepareWords(words);
     return WordFilter::doFilter(list,sw);
}

QList<INote> WordFilter::doFilter(const QList<INote> &list, const QStringList words)
{
    if(list.isEmpty() || words.isEmpty()) return list;
    QList<INote> filtered;
    foreach (INote note, list) {
        foreach (QString w, words) {
            if(note.getTitle().contains(w,Qt::CaseInsensitive)
                    || note.getNote().contains(w,Qt::CaseInsensitive)){
                filtered<<note;
            }
        }
    }
    return filtered;
}

QStringList WordFilter::prepareWords(QString words)
{
    QString words1= words.replace(QRegExp("[.,?]")," ");
   QStringList sw= words1.split(" ");
   QStringList sw1;
   foreach (QString w, sw) {
       if(!w.isEmpty()){
           sw1<<w;
       }
   }
   return sw1;
}

int WordFilter::wordPos(const QString inputString,QString words){

    int pos= -1;
    if(inputString.isEmpty() || words.isEmpty()) return -1;
    QStringList sl= WordFilter::prepareWords(words);
    //select pos for first word

    foreach (QString w, sl) {
        if(inputString.contains(w,Qt::CaseInsensitive)){
           pos= inputString.indexOf(w,0,Qt::CaseInsensitive);

           return pos;
        }
    }
    return pos;
}
