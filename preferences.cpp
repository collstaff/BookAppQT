#include "preferences.h"
#include "ui_preferences.h"
#include <QSettings>
#include <QColorDialog>
#include <QFile>
#include <QXmlStreamReader>
#include <QPalette>
#include <QFont>
#include "Logging.h"

Preferences::Preferences(MainWindow* mainWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences),
    m_mainWindow(mainWindow)
{
    Log log;

    log.OpenLogFile();

    log.LogItem("Displaying preferences page.");

    QSettings settings("BookStoreApp", "MyOrganization");
    //260b05
    // Get font
    QFont currentFont = qApp->font();
    QString currentFontFamily = currentFont.family();
    QFont::Weight currentFontWeight = currentFont.weight();

    ui->setupUi(this);

    if (currentFontFamily == "Times New Roman")
    {
        ui->changeFontChk->setChecked(true);
    }
    else
    {
        ui->changeFontChk->setChecked(false);
    }

    if (currentFontWeight == QFont::ExtraBold)
    {
        ui->fontWeightChk->setChecked(true);
    }
    else
    {
        ui->fontWeightChk->setChecked(false);
    }
}

Preferences::~Preferences()
{
    delete ui;
}

void Preferences::updateSettings()
{
    if (ui->changeFontChk->isChecked())
    {
        QFont font = qApp->font();
        font.setFamily("Times New Roman");
        qApp->setFont(font);
    }
    else
    {
        QFont font = qApp->font();
        font.setFamily("Segoe UI");
        qApp->setFont(font);
    }

    if (ui->fontWeightChk->isChecked())
    {
        updateFontWeight(true);
    }
    else
    {
        updateFontWeight(false);
    }


    close();
}

void Preferences::updateFontWeight(bool isChecked)
{
    if (isChecked)
    {
        QFont font = qApp->font();
        font.setWeight(QFont::ExtraBold);
        qApp->setFont(font);
    }
    else
    {
        QFont font = qApp->font();
        font.setWeight(QFont::Normal);
        qApp->setFont(font);
    }
}

