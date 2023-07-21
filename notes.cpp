#include "notes.h"
#include "ui_notes.h"
#include <QFile>

Notes::Notes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Notes)
{
    ui->setupUi(this);
}

Notes::~Notes()
{
    delete ui;
}

void Notes::exportNotes() {
    QFile file;

    file.setFileName("BookStoreNotes.txt");

    QString stringToExport = ui->notesTxt->toPlainText();

    file.open(QIODevice::WriteOnly);

    QTextStream out(&file);
    out << stringToExport;

    ui->notesLbl->setText("Notes Exported!");
    ui->notesTxt->setText("");
}
