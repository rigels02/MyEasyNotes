#ifndef WORDFILTER_H
#define WORDFILTER_H

#include <QString>
#include <QStringList>

#include <QDebug>

#include "inote.h"


class WordFilter
{
public:
    static QList<INote> doFilter(const QList<INote> &list, const QString words);
     static QList<INote> doFilter(const QList<INote> &list, const QStringList words);
     static QStringList prepareWords(QString words);

     static int wordPos(const QString inputString, QString words);
};

#endif // WORDFILTER_H
