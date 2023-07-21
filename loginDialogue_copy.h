#ifndef LOGINDIALOGUE_COPY_H
#define LOGINDIALOGUE_COPY_H


include <QDialog>
include <QLabel>
include <QPushButton>
include <QDialogButtonBox>
include <QLineEdit>
include <QComboBox>
include <QGridLayout>
include <QStringList>
include <QDebug>






class LoginDialog : public QDialog {


Q_OBJECT

private:

QLabel labelUsername;


QLabel labelPassword;


QComboBox comboUsername;




QLineEdit editPassword;





QDialogButtonBox buttons;


void setUpGUI();

public:

explicit LoginDialog(QWidget parent = 0);

/*!
* Sets the proposed username, that can come for instance
* from a shared setting.
username the string that represents the current username

to display

*/
void setUsername( QString& username );

/*!
* Sets the current password to propose to the user for the login.
* password the password to fill into the dialog form
*/
void setPassword( QString& password );

/*!
* Sets a list of allowed usernames from which the user
* can pick one if he does not want to directly edit it.
usernames a list of usernames

    /

void setUsernamesList( const QStringList& usernames );

signals:

/*!

* A signal emitted when the login is performed.
* username the username entered in the dialog
* password the password entered in the dialog
* index the number of the username selected in the combobox
*/
void acceptLogin( QString& username, QString& password, int& indexNumber );

public slots:

/*!
* A lot to adjust the emitting of the signal.
*/
void slotAcceptLogin();

};

    #endif // LOGINDIALOG_H
