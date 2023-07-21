#include "adduser.h"
#include "ui_adduser.h"
#include "dbmanager.h"
#include <QMessageBox>
#include <QDialog>
#include "Logging.h"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::addUserToDb()
{
    Log log;

    log.OpenLogFile();

    dbmanager db("BookStore.db");

    //Grab the user credentials from the text boxes
    QString username = ui->addUsernameTxt->toPlainText();
    QString password = ui->addPassTxt->toPlainText();

    log.LogItem("Beginning User DB insertion. Username: " + username);

    User userToAdd(username, password);

    auto isSuccessful = db.InsertIntoUserTable("BookStore.db", userToAdd);

    if (isSuccessful)
    {
        QMessageBox::information(this,"User Added", "User " + username + " successfully added.", QMessageBox::Ok);

        log.LogItem("User Insertion Succeeded. Username: " + username);
    }
    else
    {
        QMessageBox::information(this,"Error Adding User", "Error while adding user " + username+ ".", QMessageBox::Ok);

        log.LogItem("User Insertion Failed. Username: " + username);
    }

    log.CloseLogFile();
}

