#include "noteform.h"
#include "ui_noteform.h"

#include <QDebug>

noteform::noteform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::noteform)
{
    ui->setupUi(this);
}

noteform::~noteform()
{
    delete ui;
}

Note noteform::getData()
{
    Note note;
    note.setTitle(ui->title->text());
    note.setNote(ui->note->toPlainText());
    return note;
}

void noteform::setData(Note note, int selectedPos)
{
    ui->title->setText(note.getTitle());
    ui->note->setPlainText(note.getNote());
    if(selectedPos > -1){
        ui->note->setFocus();
        QTextCursor cursor = ui->note->textCursor();
        cursor.setPosition(selectedPos,QTextCursor::MoveAnchor);
        cursor.movePosition(QTextCursor::EndOfWord,QTextCursor::KeepAnchor);
        ui->note->setTextCursor(cursor);
    }
}



void noteform::on_buttonBox_accepted()
{
 qDebug()<<"accepeted...";
 qDebug()<<ui->title<<":"<<ui->note;
}
