#include "changeuserpass.h"
#include "ui_changeuserpass.h"
#include <QDialog>
#include <QMessageBox>
#include "dbmanager.h"
#include "Logging.h"

ChangeUserPass::ChangeUserPass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeUserPass)
{
    ui->setupUi(this);
}

ChangeUserPass::~ChangeUserPass()
{
    delete ui;
}

void ChangeUserPass::changeUserPassword()
{
    Log log;

    log.OpenLogFile();

    dbmanager db("BookStore.db");

    //Grab the user credentials from the text boxes
    QString username = ui->changeUserTxt->toPlainText();
    QString password = ui->newPassTxt->toPlainText();

    log.LogItem("Beginning password update. User: " + username);

    User userToUpdate(username, password);

    auto isSuccessful = db.UpdateUserTable("BookStore.db", userToUpdate);

    if (isSuccessful)
    {
        QMessageBox::information(this,"Password changed", "Password change for " + username + " succeeded.", QMessageBox::Ok);
        log.LogItem("Password update Succeeded. User: " + username);
    }
    else
    {
        QMessageBox::information(this,"Error Changing Password", "Password changed failed.", QMessageBox::Ok);
        log.LogItem("Password update failed. User: " + username);
    }

    log.CloseLogFile();
}
