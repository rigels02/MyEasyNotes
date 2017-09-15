#include <QtTest>
#include "test/myeasynotestest.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

   MyEasyNotesTest myTest;
   // Test1 myTest;
    //TestSuite2 testSuite2;
    // multiple test suites can be ran like this
    return QTest::qExec(&myTest, argc, argv);
    /**
    |
            QTest::qExec(&testSuite2, argc, argv);
            **/
}
