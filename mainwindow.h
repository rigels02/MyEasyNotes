#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QFileDialog>
#include "io/appsettings.h"
#include "noteform.h"
#include "notesrepo.h"
#include "ie/impoexpotxtfiles.h"
#include "ie/impoexpojson.h"
#include "tools/helper.h"
#include "rest/restclient.h"
#include "dataserverwin.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void addSimpleItems(const QList<INote> &list);
    void addDataItems(const QList<INote> &list);
    bool isValid(const Note note);

    bool isValidSearchString();
private slots:
    void on_btnAdd_clicked();

    void on_btnUpdate_clicked();

    void on_btnDelete_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_actionImport_text_files_triggered();

    void on_actionExport_Json_file_triggered();

    void on_actionImport_Json_file_triggered();

    void on_actionSort_by_Title_triggered();

    void on_actionSort_by_Date_triggered();

    void on_actionDelete_ALL_triggered();

    void on_actionSort_by_Date_Last_first_triggered();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_btnSearch_clicked();

    void on_actionRest_Server_triggered();
    void on_dataServerReturn();


    void on_actionApp_Version_triggered();

private:
    Ui::MainWindow *ui;
    DataServerWin *dataServerWin;
    NotesRepo repo;
    bool filterStatus;

    void updateView();
    void updateViewWithList(const QList<INote> list);
    QString getItem(Note note);
    void updateStatusInfo(QString txt);
    void sortByTitle();
    void sortByDate();
    void sortByDateLastFirst();
    int getCurrentItemIdx();
    int getCurrentDataItemIdx();
};

#endif // MAINWINDOW_H
