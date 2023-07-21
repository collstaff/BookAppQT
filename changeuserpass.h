#ifndef CHANGEUSERPASS_H
#define CHANGEUSERPASS_H

#include <QDialog>

namespace Ui {
class ChangeUserPass;
}

class ChangeUserPass : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeUserPass(QWidget *parent = nullptr);
    ~ChangeUserPass();

private:
    Ui::ChangeUserPass *ui;
private slots:
    void changeUserPassword();
};

#endif // CHANGEUSERPASS_H
