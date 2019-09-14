#include "dataserverwin.h"
#include "ui_dataserverwin.h"

extern AppSettings appSettings;


DataServerWin::DataServerWin(QWidget *parent, NotesRepo *repo) :
    QMainWindow(parent),
    ui(new Ui::DataServerWin)
{
    ui->setupUi(this);
    ui->txtReport->setReadOnly(true);
    ui->progressBar->setVisible(false);
    this->repo = repo;
    this->schema="http";
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    m_client =nullptr;
    getProperties();

}

DataServerWin::~DataServerWin()
{
    delete ui;
    if(m_client!=nullptr)
        delete m_client;
}

void DataServerWin::closeEvent(QCloseEvent *event){

    /**
    While m_client is busy with request ignore close event!
    It is done to prevent application to allow possibility to do other data modification in the same time,
     and cause unpredicted result,
     during proceding of rest_client request which also do data modification.
    m_client will be busy with request until it is completed, timed out or aborted.

Alternatively,You can use the following piece of code in your Qt Window to
disable Close (“X”) button in the title bar.

    setWindowFlags(Qt::Window
    | Qt::WindowMinimizeButtonHint
    | Qt::WindowMaximizeButtonHint);
to enable it again:

    setWindowFlags(Qt::Window
    | Qt::WindowMinimizeButtonHint
    | Qt::WindowMaximizeButtonHint
    | Qt::WindowCloseButtonHint);

    **/
    if(isBusyOnRequest()){
        event->ignore();
        return;
    }
    event->accept();
    emit DataServerWinCloseAndReturn();

}

void DataServerWin::updateButtonsStatus()
{
    if(m_client!=nullptr){
        if(m_client->busyOnRequest()){
            ui->btnAcceptHostData->setEnabled(false);
            ui->btnReceiveFromServer->setEnabled(false);
            ui->btnSendToServer->setEnabled(false);
            ui->btnAbort->setEnabled(true);
        }else{
            ui->btnAcceptHostData->setEnabled(true);
            ui->btnReceiveFromServer->setEnabled(true);
            ui->btnSendToServer->setEnabled(true);
            ui->btnAbort->setEnabled(false);
        }
    }
}

void DataServerWin::getProperties(){
    this->host = appSettings.getProperty(key_Host);
    this->port = appSettings.getProperty(key_Port).toInt();
    this->baseUrl = appSettings.getProperty(key_baseUrl);
    this->host= (this->host.isEmpty())? HOST: this->host;
    this->port= (this->port==0)? PORT: this->port;
    this->baseUrl= (this->baseUrl.isEmpty())? BASEURL: this->baseUrl;
    ui->txtHost->setText(this->host);
    ui->txtPort->setText(QString("%0").arg(this->port));
    ui->txtBaseUrl->setText(this->baseUrl);
}

void DataServerWin::putProperties()
{
    appSettings.putProperty(key_Host,ui->txtHost->text());
    appSettings.putProperty(key_Port,ui->txtPort->text());
    appSettings.putProperty(key_baseUrl,ui->txtBaseUrl->text());
}

void DataServerWin::appendReportTxt(QString txt){

      ui->txtReport->setPlainText(
                  ui->txtReport->toPlainText()+"\n"+ txt
                  );

}
void DataServerWin::showBusyUpdateButtonsStatus(QString msg){
 ui->progressBar->setVisible(true);
 ui->lblStatus->setText(msg);
 updateButtonsStatus();
}
void DataServerWin::hideBusyUpdateButtonsStatus(QString msg){
     ui->progressBar->setVisible(false);
      ui->lblStatus->setText(msg);
      updateButtonsStatus();
}
void DataServerWin::requestAndCompareDataWithRemote(){
    if(repo==nullptr) return;

    ui->lblStatus->setText("");
    QDateTime localModTime = repo->getLastModifyTime();
    if(localModTime.isNull()){
        appendReportTxt("No local data ");

    }


    m_client= new  RestClient(schema,host,port,baseUrl);
    bool ok=false;
     showBusyUpdateButtonsStatus("Connecting...");
    QString hiResult = m_client->hi("/hi", ok);
    if(!ok){
        appendReportTxt(hiResult);
        hideBusyUpdateButtonsStatus(hiResult);
        return;
    }
    if(hiResult.compare(HIWORD)!=0){
        appendReportTxt("WRONG Hi Word!");
        hideBusyUpdateButtonsStatus("");
        return;

    }
    QList<Header> hdrs= m_client->getHeaders("/headers",ok);
    if(!ok){
        appendReportTxt(m_client->getLastError());
        hideBusyUpdateButtonsStatus(m_client->getLastError());
        return;
    }
    if(hdrs.isEmpty()){
        appendReportTxt("No data on DB server ");
        hideBusyUpdateButtonsStatus("No data");
     return;
    }
    QString smsg;
    foreach (Header header, hdrs) {
        if(header.getTitle().compare("root")==0){
            if(compareDateTimes(header.getModTime(), localModTime)==0 ){
                smsg = "Modify TimeStamp local == DB server ";
                appendReportTxt(smsg);
                hideBusyUpdateButtonsStatus(smsg);
                return;
            }
            if(compareDateTimes(header.getModTime(),localModTime)<0 ){
                smsg= "Modify TimeStamp local is newer then on DB server ";
                appendReportTxt(smsg);
                hideBusyUpdateButtonsStatus(smsg);
                return;
            }
            if(compareDateTimes(header.getModTime(), localModTime)>0 ){
                smsg = "Modify TimeStamp local is older then on DB server ";
                appendReportTxt(smsg);
                hideBusyUpdateButtonsStatus(smsg);
                return;
            }
        }
    }
}

bool DataServerWin::isBusyOnRequest()
{
    if(m_client!= nullptr){
        bool busy = m_client->busyOnRequest();
       return  busy;
    }
    return false;
}
int DataServerWin::compareDateTimes(QDateTime t1, QDateTime t2){

    uint mt1 = t1.toTime_t();
    uint mt2 = t2.toTime_t();
    //There might be one second difference with MySql Server
    if(qAbs(mt1-mt2)<= 1) return 0;
    if(mt1<mt2) return -1;
    if(mt1>mt2) return 1;
    return 0;
}
void DataServerWin::on_btnSendToServer_clicked()
{
   if(repo == nullptr) return;
   QList<Note> notes= Header::convertINotesList(repo->finaAll());
   NotesBook book;
   book.setId(0);
   book.setModTime(repo->getLastModifyTime());
   book.setNotes(notes);
   //if(notes.isEmpty()) return;

   m_client = new RestClient(schema,host,port,baseUrl);
   showBusyUpdateButtonsStatus("Sending...");
   bool ok = m_client->postBook("",book);
   if(!ok){
       hideBusyUpdateButtonsStatus(m_client->getLastError());
        appendReportTxt(m_client->getLastError());
       QMessageBox::critical(this,"Error",QString("Can not send!\n%0").arg(m_client->getLastError()));
   return;
   }
   hideBusyUpdateButtonsStatus("Data sent");
   QString smsg = QString("%0 notes have been sent to DB Server!").arg(book.getNotes().size());
   appendReportTxt(smsg);
   QMessageBox::information(this,"Send To Server",smsg);

}

void DataServerWin::on_btnReceiveFromServer_clicked()
{
    if(repo == nullptr) return;

    m_client = new RestClient(schema,host,port,baseUrl);
    bool ok;
     showBusyUpdateButtonsStatus("Receiving...");
   NotesBook book = m_client->getBook("",ok);
   if(!ok){
    hideBusyUpdateButtonsStatus(m_client->getLastError());
    appendReportTxt(m_client->getLastError());
    QMessageBox::critical(this,"Receive Error",QString("Error: %0").arg(m_client->getLastError()));
    return;
    }
    repo->removeAll();
    repo->saveAll(book.getModTime(),book.getNotes());
    QString smsg= QString("%0 notes have been received from DB Server!").arg(book.getNotes().size());
    hideBusyUpdateButtonsStatus("Data received");
    appendReportTxt(smsg);
    QMessageBox::information(this,"Receive From Server",smsg);

}



void DataServerWin::on_btnAcceptHostData_clicked()
{
    putProperties();
    getProperties();
    requestAndCompareDataWithRemote();
}

void DataServerWin::on_btnAbort_clicked()
{
    if(m_client!=nullptr){

        m_client->abort();
    }
}
