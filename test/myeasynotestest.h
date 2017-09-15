#ifndef MYEASYNOTESTEST_H
#define MYEASYNOTESTEST_H

#include <QObject>
#include <QtTest>
#include <QDebug>
#include "note.h"
#include "inote.h"
#include "tools/helper.h"
#include <filter/wordfilter.h>

class MyEasyNotesTest : public QObject
{
    Q_OBJECT
private slots:
    // functions executed by QtTest before and after test suite
    void initTestCase();
    void cleanupTestCase();

    // functions executed by QtTest before and after each test
    void init();
    void cleanup();

    // test functions - all functions prefixed with "test" will be ran as tests
    void testHi();
    void testSortByTitle();
     void testSortByDate();

     void testStaticSetFilterResetFilter();
     void testFilterGetWordPos();
};

#endif // MYEASYNOTESTEST_H
