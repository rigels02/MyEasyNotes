#ifndef DATASERVERWIN_H
#define DATASERVERWIN_H

#include <QMainWindow>

#include "io/appsettings.h"
#include "rest/restclient.h"
#include "notesrepo.h"

#define HOST "localhost"
#define PORT 8080
#define BASEURL "/notesbook"
#define key_Host "host"
#define key_Port "port"
#define key_baseUrl "url"
#define HIWORD "NotesBookController31082017"

namespace Ui {
class DataServerWin;
}

class DataServerWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataServerWin(QWidget *parent = 0, NotesRepo *repo=0);
    ~DataServerWin();
    void requestAndCompareDataWithRemote();
    bool isBusyOnRequest();

signals:
    void DataServerWinCloseAndReturn();

private slots:
    void on_btnSendToServer_clicked();

    void on_btnReceiveFromServer_clicked();

    void on_btnAcceptHostData_clicked();

    void on_btnAbort_clicked();

private:
    Ui::DataServerWin *ui;
    NotesRepo *repo;
    QString schema;
    QString host;
    int port;
    QString baseUrl;
    RestClient *m_client;
private:
    void closeEvent(QCloseEvent *event) override;
    void updateButtonsStatus();
    void getProperties();
    void putProperties();
    void appendReportTxt(QString txt);
    int compareDateTimes(QDateTime t1, QDateTime t2);
    void showBusyUpdateButtonsStatus(QString msg);
    void hideBusyUpdateButtonsStatus(QString msg);
};

#endif // DATASERVERWIN_H
