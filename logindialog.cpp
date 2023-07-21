#include "logindialog.h"
#include "ui_logindialog.h"
#include "dbmanager.h"
#include <QMessageBox>
#include "Logging.h"

logindialog::logindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindialog)
{
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui->setupUi(this);
}

logindialog::~logindialog()
{
    delete ui;
}

void logindialog::logUserIn()
{
    Log log;

    log.OpenLogFile();

    log.LogItem("Displaying login screen");

    QString username = ui ->usernameTxt->toPlainText();
    QString password = ui ->passwordTxt->toPlainText();

    dbmanager db("BookStore.db");

    if (db.VerifyLogin("BookStore.db", username, password))
    {

        QMessageBox::information(this, "LoginBox", "Succesfully logged in");
        log.LogItem("Login successful");
        accept();

    }
    else {

        QMessageBox::warning(this, "LoginBox", "username and password do not match");
        log.LogItem("Login failed");

        log.CloseLogFile();
    }
}
