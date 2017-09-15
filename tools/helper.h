#ifndef HELPER_H
#define HELPER_H

#include <QList>
#include "inote.h"

class Helper
{
public:
    Helper();
    static void sortByTitle(QList<INote> &slist);
    static void sortByDate(QList<INote> &slist);
    static void sortByDateReverse(QList<INote> &slist);
};

#endif // HELPER_H
