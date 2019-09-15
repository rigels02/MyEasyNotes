#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

AppSettings appSettings("myeasynotes.ini");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    repo = NotesRepo();
    filterStatus=false;
    dataServerWin=nullptr;

    updateView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
   noteform* noteDlg = new noteform(this);
   noteDlg->setWindowTitle("Add Note");
   ui->menuBar->setEnabled(false);
   noteDlg->setWindowModality(Qt::WindowModal);
#ifndef Q_OS_WIN

    noteDlg->showMaximized();
#endif
   //noteDlg->setMaximumSize(this->size());
   bool acc= noteDlg->exec();
   if(acc){

       Note rnote= noteDlg->getData();
       //rnote.setModTime(QDate().currentDate());
       if(!isValid(rnote)) goto Exi;
       repo.add(rnote);
       updateView();
   }
   Exi:
   delete noteDlg;
   ui->menuBar->setEnabled(true);
}

void MainWindow::on_btnUpdate_clicked()
{
    //int idx = getCurrentItemIdx();
    int idx = getCurrentDataItemIdx();
    if(idx< 0) return;

    //QString title= repo.findById(idx).getTitle();
    int num= repo.count();
    updateStatusInfo(QString("%0 items, selected idx=%1").arg(num).arg(idx));
    //qDebug()<<QString("selected %0: %1").arg(idx).arg(title);
    Note note= repo.findById(idx);
    noteform* noteDlg = new noteform(this);
    noteDlg->setWindowTitle("Update Note");
    ui->menuBar->setEnabled(false);
    noteDlg->setWindowModality(Qt::WindowModal);
#ifndef Q_OS_WIN
    noteDlg->showMaximized();
#endif

    int pos=-1;
    if(filterStatus){
        pos= WordFilter::wordPos(note.getNote(),ui->edSearch->text());
    }
    noteDlg->setData(note,pos);
    bool acc= noteDlg->exec();
    if(acc){
        Note rnote= noteDlg->getData();
        if(!isValid(rnote)) goto Exi;
        repo.edit(idx,rnote);
        updateView();
    }
   Exi:
    delete noteDlg;
    ui->menuBar->setEnabled(true);
}

int MainWindow::getCurrentItemIdx(){
    return ui->listWidget->currentIndex().row();
}

int MainWindow::getCurrentDataItemIdx()
{
    QListWidgetItem* item = ui->listWidget->currentItem();
    if(item==nullptr) return -1;
    int idx= getCurrentItemIdx();
    if(idx == -1) return -1;
    return item->data(Qt::UserRole).toInt(); //get keeped Note's Id
}

void MainWindow::on_btnDelete_clicked()
{
    //int idx = getCurrentItemIdx();
    int idx = getCurrentDataItemIdx();
    if(idx< 0) return;
    int ok= QMessageBox::question(this,"Delete?",
                          "Are you sure to delete selected note?",
                          QMessageBox::Ok,QMessageBox::Cancel);
    if(ok == QMessageBox::Ok){
    repo.remove(idx);
    updateView();
    }
}

void MainWindow::addSimpleItems(const QList<INote> &list){
    QStringList slst= QStringList();
    foreach (Note note, list) {
        slst<< getItem(note);
    }
    ui->listWidget->addItems(slst);

}

void MainWindow::addDataItems(const QList<INote> &list)
{
    int idx=0;
    foreach (INote note, list) {
       QString stitle= getItem(note);
       QListWidgetItem* wi1 = new QListWidgetItem(stitle);
       wi1->setData(Qt::UserRole,note.getId());
       ui->listWidget->insertItem(idx,wi1);
       idx++;
    }


}

bool MainWindow::isValid(const Note note)
{
 if(!note.getTitle().isEmpty()) return true;
 QMessageBox::information(this,"Error","Note must have a title!");
 return false;
}
void MainWindow::updateViewWithList(const QList<INote> list)
{
    ui->listWidget->clear();

   // addSimpleItems(list);
    addDataItems(list);

    updateStatusInfo(QString("%0 items").arg(list.size()));

}

void MainWindow::updateView()
{

    updateViewWithList(repo.finaAll());

}



QString MainWindow::getItem(Note note)
{
   float sz = note.getNote().size()/1024.0;
   return QString("%0    %1/%2/%3  %4 K")
            .arg(note.getTitle())
            .arg(note.getModTime().day(),2,10)
            .arg(note.getModTime().month(),2,10)
           .arg((note.getModTime().year()))
           .arg(sz,0,'f',2);
}

void MainWindow::updateStatusInfo(QString txt)
{

    ui->Lstatus->setText(QString("%0, last modify: %1")
         .arg(txt)
         .arg(repo.getLastModifyTime().toString("dd/MM/yyyy HH:mm:ss")));
}

void MainWindow::sortByTitle()
{
    QList<INote> list= repo.finaAll();
    Helper::sortByTitle(list);
    repo.importData(list);
    updateViewWithList(repo.finaAll());
}

void MainWindow::sortByDate()
{
    QList<INote> list= repo.finaAll();
    Helper::sortByDate(list);
     repo.importData(list);
     updateViewWithList(repo.finaAll());
}

void MainWindow::sortByDateLastFirst()
{
    QList<INote> list= repo.finaAll();
    Helper::sortByDateReverse(list);
     repo.importData(list);
     updateViewWithList(repo.finaAll());
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
   on_btnUpdate_clicked();
}

void MainWindow::on_actionImport_text_files_triggered()
{
  QFileDialog fd;
  fd.setFileMode(QFileDialog::ExistingFiles);
  fd.setWindowTitle("Select file(s) to import");
#ifndef Q_OS_WIN
    fd.showMaximized();
#endif

  int result = fd.exec();
  if(result==1){
      QStringList lst= fd.selectedFiles();
      qDebug()<<QString("selected: ")<<lst;
      ImpoExpoTxtFiles impo(lst);
      QList<Note> anotes= impo.getNotes();
      repo.append(anotes);
      updateView();
      QMessageBox::information(
                  this,"Import",
                  QString("Import of %0 items completed!").arg(anotes.size())
                  );
  }
  qDebug()<<QString("result: %0").arg(result);
}

void MainWindow::on_actionExport_Json_file_triggered()
{
    QFileDialog fd;
    fd.setFileMode(QFileDialog::AnyFile);
    fd.setWindowTitle("Select/type file to export");
  #ifndef Q_OS_WIN
      fd.showMaximized();
  #endif

   int result = fd.exec();
   if(result == 1){
    QStringList filename = fd.selectedFiles();

    ImpoExpoJson expo;
    QList<INote> inotes;
    QList<Note> notes;

    inotes= repo.finaAll();
    foreach (INote inote, inotes) {
        Note note= inote.getNoteObj();
        notes.append(note);
    }

    NotesBook book("root",repo.getLastModifyTime());
    book.setNotes(notes);
    expo.expoNotesBookJson(filename.at(0),book);
    //expo.expoJson(filename.at(0),notes);
    QMessageBox::information(this,"Export",QString("Export completed to file: %0 !").arg(filename.at(0)));
}
}

void MainWindow::on_actionImport_Json_file_triggered()
{
    QFileDialog fd;
    fd.setFileMode(QFileDialog::ExistingFile);
    fd.setWindowTitle("Select file to import from");
#ifndef Q_OS_WIN
    fd.showMaximized();
#endif

    int result = fd.exec();
    if(result == 1){
        QStringList filename = fd.selectedFiles();
        /**
    QString filename = fd.getOpenFileName(nullptr,"Json file");
    if(filename.isNull())
          return;
    **/
        ImpoExpoJson impo;

        NotesBook book = impo.impoNotesBookJson(filename.at(0));
        //QList<Note> notes = impo.impoJson(filename.at(0));
        int ok =QMessageBox::question(this,"Import?",
                                      "The existing data will be overwritten!\nContinue?",
                                      QMessageBox::Ok,QMessageBox::Cancel
                                      );
        if(ok==QMessageBox::Ok){
            repo.removeAll();
            repo.saveAll(book.getModTime(),book.getNotes());
            //repo.importData(notes);
            updateView();
            QMessageBox::information(
                        this,"Import",
                        QString("Import of %0 items completed from file %1!").arg(book.getNotes().size()).arg(filename.at(0))
                        );
        }
    }
}




void MainWindow::on_actionSort_by_Title_triggered()
{
    sortByTitle();

}

void MainWindow::on_actionSort_by_Date_triggered()
{
    sortByDate();
}

void MainWindow::on_actionDelete_ALL_triggered()
{
    int ok =QMessageBox::question(this,"Delete ALL!?",
                                  "ALL existing data will be deleted!\nContinue?",
                                  QMessageBox::Ok,QMessageBox::Cancel
                                  );
    if(ok==QMessageBox::Ok){
        repo.removeAll();
        updateView();
    }
}

void MainWindow::on_actionSort_by_Date_Last_first_triggered()
{
    sortByDateLastFirst();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int num= repo.count();
    //int idx = ui->listWidget->currentIndex().row();
    //int idx = getCurrentDataItemIdx();
    int idx = getCurrentItemIdx();
    updateStatusInfo(QString("%0 items, selected idx=%1").arg(num).arg(idx));
}

void MainWindow::on_btnSearch_clicked()
{
    if(filterStatus){
     //reset search filter

      repo.setFilter("");
      ui->edSearch->setText("");
      ui->btnSearch->setText("Search");
      filterStatus=false;
      updateView();
    }else{
     //set filter for search
        if(!isValidSearchString()) return;
        repo.setFilter(ui->edSearch->text());
        ui->btnSearch->setText("Cancel");
        filterStatus=true;
        updateView();
    }
}
bool MainWindow::isValidSearchString(){
    if(ui->edSearch->text().isEmpty()) return false;
    QString words= ui->edSearch->text();
    QString words1= words.replace(QRegExp("[.,?]"),"");
    if(words1.isEmpty()){
        QMessageBox::information(this,"Error","Did you typed only delimiters: ,.??");
        return false;
    }
    return true;
}




void MainWindow::on_actionRest_Server_triggered()
{

    if(dataServerWin==nullptr){
   dataServerWin = new DataServerWin(nullptr,&repo);
   connect(dataServerWin,SIGNAL(DataServerWinCloseAndReturn()),this,SLOT(on_dataServerReturn()));
     dataServerWin->setWindowModality(Qt::ApplicationModal);
     dataServerWin->show();
     dataServerWin->requestAndCompareDataWithRemote();
    }else{

         dataServerWin->show();
    }

}

void MainWindow::on_dataServerReturn()
{
  if( !dataServerWin->isBusyOnRequest() ){
  //disconnect(dataServerWin,SIGNAL(DataServerWinReturn()),this,SLOT(on_dataServerReturn()));

  //delete dataServerWin; //Deleted after dataServerWin.CloseEvent processed.
    dataServerWin=nullptr;
  }else{
    dataServerWin->hide();
  }
    updateView();
}



void MainWindow::on_actionApp_Version_triggered()
{
    QMessageBox::information(this,"Info",QString("Ver. ")+APP_VERSION,QMessageBox::Ok);
}
