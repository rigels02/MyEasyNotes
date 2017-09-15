#ifndef NOTEFORM_H
#define NOTEFORM_H

#include <QDialog>
#include "note.h"

namespace Ui {
class noteform;
}

class noteform : public QDialog
{
    Q_OBJECT

public:
    explicit noteform(QWidget *parent = 0);
    ~noteform();
    Note getData();
    void setData(Note note, int selectedPos= -1);
    //void setTitle(QString title);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::noteform *ui;
};

#endif // NOTEFORM_H
