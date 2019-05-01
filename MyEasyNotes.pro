#-------------------------------------------------
#
# Project created by QtCreator 2017-08-01T12:39:10
#
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyEasyNotes
TEMPLATE = app


//CONFIG+= Test

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
            APP_VERSION='\\"1.00\\"'

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    note.cpp \
    notesrepo.cpp \
    noteform.cpp \
    io/iofileimpl.cpp \
    ie/impoexpotxtfiles.cpp \
    ie/impoexpojson.cpp \
    tools/helper.cpp \
    inote.cpp \
    filter/wordfilter.cpp \
    rest/restclient.cpp \
    rest/header.cpp \
    io/appsettings.cpp \
    rest/notesbook.cpp \
    dataserverwin.cpp


HEADERS += \
        mainwindow.h \
    note.h \
    notesrepo.h \
    noteform.h \
    io/iofileimpl.h \
    ie/impoexpotxtfiles.h \
    ie/impoexpojson.h \
    tools/helper.h \
    inote.h \
    filter/wordfilter.h \
    rest/header.h \
    rest/restclient.h \
    io/appsettings.h \
    rest/notesbook.h \
    dataserverwin.h


FORMS += \
    noteform.ui \
    mainwindow.ui \
    dataserverwin.ui

CONFIG += mobility
MOBILITY = 

Test{
  message(Test build)
QT += testlib
TARGET = MyEasyNotesTest
SOURCES -= main.cpp

HEADERS += test/myeasynotestest.h

SOURCES += test/main.cpp \
            test/myeasynotestest.cpp
#
#RESOURCES += \
#    test/testfiles.qrc
#

} else {
 message(Normal build)
}

