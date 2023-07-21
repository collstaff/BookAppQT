#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Preferences;
}

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences(MainWindow *mainWindow, QWidget *parent = nullptr);
    ~Preferences();

private:
    Ui::Preferences *ui;
    MainWindow* m_mainWindow;
private slots:
    void updateSettings();
    void updateFontWeight(bool isChecked);
};

#endif // PREFERENCES_H
