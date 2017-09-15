#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QFile>
#include <QTextStream>

class AppSettings
{
public:
    AppSettings(QString fileName);


    void appendRec(QString key, QString value);
    QMap<QString,QString> readAllKeys();

    QString getProperty(QString key);
    void reset();
    void putProperty(QString key, QString val);
private:
    QFile *openFileToWrite();
    QFile *openFileToRead();
private:
    QString fileName;

};

#endif // APPSETTINGS_H
