#ifndef DELETEUSER_H
#define DELETEUSER_H

#include <QDialog>

namespace Ui {
class deleteuser;
}

class deleteuser : public QDialog
{
    Q_OBJECT

public:
    explicit deleteuser(QWidget *parent = nullptr);
    ~deleteuser();

private:
    Ui::deleteuser *ui;
private slots:
    void deleteUserFromDb();
};

#endif // DELETEUSER_H
