#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class logindialog;
}

class logindialog : public QDialog
{
    Q_OBJECT

public:
    explicit logindialog(QWidget *parent = nullptr);
    ~logindialog();

private:
    Ui::logindialog *ui;

private slots:
    void logUserIn();
};

#endif // LOGINDIALOG_H
