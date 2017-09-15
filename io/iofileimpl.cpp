#include "iofileimpl.h"

const QString idxFile= "qindex.idx";
const QString dataFile="data_1";
const QString dataExt=".dat";
const QString magicSign="01Aug2017@#$%";

IOFileImpl::IOFileImpl()
{

 QString fn= "data_1.dat";
 QFile fi(composeFileName());
 if(!fi.exists()){

     createDataFile(fi);
     fi.close();
     return;
 }

 fi.close();
}


void IOFileImpl::saveAll(QList<Note> data)
{
    QFile fi(composeFileName());
  //openDataFile(fi);
   createDataFile(fi);
  QDataStream ds(&fi);
  ds<<data.size();
  foreach (Note note, data) {
      note.writeData(ds);
  }
  fi.close();
}

void IOFileImpl::saveAllWithTime(QDateTime time,QList<Note> data)
{
    QFile fi(composeFileName());
    if(!fi.open(QIODevice::ReadWrite)){
        //QMessageBox::critical(0,"Error","Can not create Index file",QMessageBox::Abort);
        throw "Can not create Data file!";
    }
    QDataStream ds(&fi);
    ds<<magicSign;
    ds<<time;
    modTime= time;

  ds<<data.size();
  foreach (Note note, data) {
      note.writeData(ds);
  }
  fi.close();
}


QList<Note> IOFileImpl::loadAll()
{
    QFile fi(composeFileName());
  openDataFile(fi);
  QDataStream ds(&fi);
  QList<Note> data;
  int sz;
  ds>>sz;
  for(int i=0; i< sz;i++){
      Note note;
      note.readData(ds);
      data.append(note);
  }
  return data;
}


void IOFileImpl::createDataFile(QFile &fi)
{

 if(!fi.open(QIODevice::ReadWrite)){
     //QMessageBox::critical(0,"Error","Can not create Index file",QMessageBox::Abort);
     throw "Can not create Data file!";
 }
 QDataStream ds(&fi);
 writeHeader(ds);

}

void IOFileImpl::openDataFile(QFile &fi)
{
    if(!fi.open(QIODevice::ReadWrite)){
        //QMessageBox::critical(0,"Error","Can not create Index file",QMessageBox::Abort);
        throw "Can not open Data file!";
    }
  QDataStream ds(&fi);
  readHeader(ds);

}

void IOFileImpl::writeHeader(QDataStream &ds)
{
    ds<<magicSign;
    ds<<QDateTime::currentDateTime();
    modTime= QDateTime::currentDateTime();
}

void IOFileImpl::readHeader(QDataStream &ds)
{
    QString head;
    ds>>head;
    if(head.compare(magicSign)!=0)
        throw "Bad data file header";
    QDateTime mdate;
    ds>> mdate;
    this->modTime= mdate;
}

QString IOFileImpl::composeFileName()
{
 QString filename = QString(dataFile).append(dataExt);
 return    filename;
}

QDateTime IOFileImpl::getModTime() const
{
    return modTime;
}


