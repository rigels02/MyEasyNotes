#include "myeasynotestest.h"



void MyEasyNotesTest::initTestCase()
{

}

void MyEasyNotesTest::cleanupTestCase()
{

}

void MyEasyNotesTest::init()
{

}

void MyEasyNotesTest::cleanup()
{

}

void MyEasyNotesTest::testHi()
{
    qDebug()<<"Test try..";
}

static bool cmp(const Note &a, const Note &b){

    return a.getTitle()<b.getTitle();
}
void MyEasyNotesTest::testSortByTitle()
{

  QList<INote> notes;
  notes<<INote(1,"Note_4",QDate().currentDate(),"Content_4")
         <<INote(2,"Note_3",QDate().currentDate(),"Content_3")
         <<INote(3,"Note_2",QDate().currentDate(),"Content_2")
         <<INote(4,"Note_1",QDate().currentDate(),"Content_1");
  foreach (INote inote, notes) {
      qDebug()<<"Note:"<<inote.toString();
  }
 Helper::sortByTitle(notes);
 // std::sort(notes.begin(),notes.end(),cmp);
 foreach (INote inote, notes) {
     qDebug()<<"Note1:"<<inote.toString();
 }

}

void MyEasyNotesTest::testSortByDate()
{
    QList<INote> notes;
    INote note4(0,"Note_4",QDate().currentDate(),"Content_4");
    note4.setModTime(QDate(2017,1,2));
    INote note3(1,"Note_3",QDate().currentDate(),"Content_3");
    note3.setModTime(QDate(2016,1,2));
    INote note2(2,"Note_2",QDate().currentDate(),"Content_2");
    note2.setModTime(QDate(2015,1,3));
    INote note1(3,"Note_1",QDate().currentDate(),"Content_1");
    note1.setModTime(QDate(2015,1,2));

    notes<<note4<<note3<<note2<<note1;

    foreach (INote note, notes) {
        qDebug()<<"Note:"<<note.toString();
    }
   Helper::sortByDate(notes);
   // std::sort(notes.begin(),notes.end(),cmp);
   foreach (Note note, notes) {
       qDebug()<<"Note1:"<<note.toString();
   }
}


void MyEasyNotesTest::testStaticSetFilterResetFilter()
{
    QList<INote> notes;
    INote note4(0,"Note_4",QDate().currentDate(),"Content_4");
    note4.setModTime(QDate(2017,1,2));
    INote note3(1,"Note_3",QDate().currentDate(),"Content_3");
    note3.setModTime(QDate(2016,1,2));
    INote note2(2,"Note_2",QDate().currentDate(),"Content_2");
    note2.setModTime(QDate(2015,1,3));
    INote note1(3,"Note_1",QDate().currentDate(),"Content_1");
    note1.setModTime(QDate(2015,1,2));

    notes<<note4<<note3<<note2<<note1;

    QList<INote>result= WordFilter::doFilter(notes,"_2 _3");
    foreach (INote note, result) {
        QVERIFY(note.getTitle().contains("_2")
                || note.getTitle().contains("_3"));
        qDebug()<<note.toString();
    }
    QVERIFY(result.size()==2);

    result= WordFilter::doFilter(notes,"");
    QVERIFY(result.size()==4);
}

void MyEasyNotesTest::testFilterGetWordPos()
{
    QString text = "This is my test text sample";
    int pos= WordFilter::wordPos(text,"test sample");
    QVERIFY(pos==11);
}
