#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "note.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /**
    QDate date = QDate().currentDate();
    Note note("Note_1","Content_1");

    qDebug()<<note.toString();
    **/
    return a.exec();
}
