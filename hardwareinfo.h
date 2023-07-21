#ifndef HARDWAREINFO_H
#define HARDWAREINFO_H

#include <QDialog>

namespace Ui {
class HardwareInfo;
}

class HardwareInfo : public QDialog
{
    Q_OBJECT

public:
    explicit HardwareInfo(QWidget *parent = nullptr);
    ~HardwareInfo();

private:
    Ui::HardwareInfo *ui;
};

#endif // HARDWAREINFO_H
