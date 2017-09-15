#include "helper.h"

Helper::Helper()
{

}

void Helper::sortByTitle(QList<INote> &slist)
{
   std::sort(slist.begin(),slist.end(),
              [](const Note a, const Note b)-> bool {return a.getTitle()<b.getTitle();});
}

void Helper::sortByDate( QList<INote> &slist)
{
    std::sort(slist.begin(),slist.end(),
               [](const Note a, const Note b)-> bool {return a.getModTime()<b.getModTime();});

}

void Helper::sortByDateReverse(QList<INote> &slist)
{
    std::sort(slist.begin(),slist.end(),
               [](const Note a, const Note b)-> bool {return a.getModTime()>b.getModTime();});

}
