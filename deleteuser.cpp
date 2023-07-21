#include "deleteuser.h"
#include "ui_deleteuser.h"
#include "dbmanager.h"
#include <QMessageBox>
#include <QDialog>
#include "Logging.h"

deleteuser::deleteuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteuser)
{
    ui->setupUi(this);
}

deleteuser::~deleteuser()
{
    delete ui;
}

void deleteuser::deleteUserFromDb()
{
    bool isSuccessful;

    Log log;
    log.OpenLogFile();

    dbmanager db("BookStore.db");

    //Grab the user credentials from the text boxes
    QString username = ui->deleteUserTxt->toPlainText();
    QString password = "";

    log.LogItem("Beginning deletion of user. Username: " + username);

    User userToAdd(username, password);

    isSuccessful = db.DeleteFromUserTable("BookStore.db", userToAdd);

    if (isSuccessful)
    {
        QMessageBox::information(this,"User Removed", "User has been successfully removed", QMessageBox::Ok);
        log.LogItem("User deletion succeeded. Username: " + username);
    }
    else
    {
        QMessageBox::information(this,"Error Removing User", "An error has occurred during user removal", QMessageBox::Ok);
        log.LogItem("User deletion failed. Username: " + username);
    }

    log.CloseLogFile();
}
