#include "appsettings.h"

AppSettings::AppSettings(QString fileName)
{
  this->fileName = fileName;

}
QFile* AppSettings::openFileToWrite(){
    QFile* fi  = new QFile(this->fileName);
    if(!fi->exists()){
        fi->open(QFile::WriteOnly);
    }else{
        fi->open(QFile::WriteOnly|QFile::Append);
    }
     return fi;

}

void AppSettings::reset(){
    QFile* fi  = new QFile(this->fileName);
    if(fi->exists()){
        fi->remove();
    }
    fi->close();
}
QFile* AppSettings::openFileToRead(){
    QFile *fi =  new QFile(this->fileName);
    if(!fi->exists()) return 0;
    fi->open(QFile::ReadOnly);

    return fi;
}
void AppSettings::appendRec(QString key, QString value){
 QFile *fi = openFileToWrite();
 QTextStream ds(fi);

 ds<<QString("%0=%1\n").arg(key).arg(value);
 fi->close();
}
QMap<QString, QString> AppSettings::readAllKeys(){
    QFile *fi=openFileToRead();
    if(fi != 0 ){
     QTextStream ds(fi);
     QString all= ds.readAll();
      QStringList lines= all.split("\n");
      QMap<QString,QString> map;
      foreach (QString line, lines) {
          if(line.isEmpty()) continue;
          QStringList kv= line.split("=");
          map.insert(kv[0],kv[1]);
      }
      fi->close();
      return map;
    }else {
        return QMap<QString,QString>();
    }

}
QString AppSettings::getProperty(QString key){

    QMap<QString,QString> map= readAllKeys();

        QMapIterator<QString, QString> i(map);
          while (i.hasNext()) {
              i.next();
              if(i.key().compare(key)==0){
                  return i.value();
              }
          }
        return "";
}
void AppSettings::putProperty(QString key,QString val){

    QMap<QString,QString> map= readAllKeys();

    QMapIterator<QString, QString> i(map);
      while (i.hasNext()) {
          i.next();
          if(i.key().compare(key)==0){
              map.remove(key);
              break;

          }
      }
      map.insert(key,val);
      reset();
    QFile* fi= openFileToWrite();
    QTextStream ds(fi);
    QMapIterator<QString, QString> ii(map);
      while (ii.hasNext()) {
          ii.next();
          ds<< QString("%0=%1\n").arg(ii.key()).arg(ii.value());
      }
    fi->close();
}

