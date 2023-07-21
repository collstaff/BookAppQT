#include "hardwareinfo.h"
#include "ui_hardwareinfo.h"
#include <QSysInfo>
#include <QRegularExpression>
#include <QStringList>
#include "Logging.h"

HardwareInfo::HardwareInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HardwareInfo)
{
    Log log;
    log.OpenLogFile();

    log.LogItem("Displaying hardware info");

     QSysInfo *systemInfo = new QSysInfo();
    ui->setupUi(this);

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setItem(0,0, new QTableWidgetItem("Property"));
    ui->tableWidget->setItem(0,1, new QTableWidgetItem("Value"));

    QString buildApi = systemInfo->buildAbi();
    QRegularExpression rx("[-]");// match a comma or a space
    QStringList list = buildApi.split(rx);

    //ui->tableWidget->setColumnWidth(1, 250);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setItem(1,0, new QTableWidgetItem("Architecture"));
    ui->tableWidget->setItem(1,1, new QTableWidgetItem(list[0]));

    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setItem(2,0, new QTableWidgetItem("Endianness"));
    ui->tableWidget->setItem(2,1, new QTableWidgetItem(list[1]));

    ui->tableWidget->setRowCount(4);
    ui->tableWidget->setItem(3,0, new QTableWidgetItem("Product Version"));
    ui->tableWidget->setItem(3,1, new QTableWidgetItem(systemInfo->productVersion()));

    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setItem(4,0, new QTableWidgetItem("Product Type"));
    ui->tableWidget->setItem(4,1, new QTableWidgetItem(systemInfo->QSysInfo::productType()));

    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setItem(5,0, new QTableWidgetItem("Kernel Version"));
    ui->tableWidget->setItem(5,1, new QTableWidgetItem(systemInfo->QSysInfo::kernelVersion()));

    ui->tableWidget->setRowCount(7);
    ui->tableWidget->setItem(6,0, new QTableWidgetItem("Kernel Type"));
    ui->tableWidget->setItem(6,1, new QTableWidgetItem(systemInfo->QSysInfo::kernelType()));

    log.LogItem("Hardware info displayed");
    log.CloseLogFile();
}


HardwareInfo::~HardwareInfo()
{
    delete ui;
}
