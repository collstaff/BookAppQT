#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void search_inventory();
    void on_actionHardware_Info_triggered();
    void showHelpWindow();
    void on_actionNotes_triggered();
    void on_actionPreferences_triggered();
    void on_addUserBtn_clicked();
    void on_deleteUserBtn_clicked();
    void on_changePassBtn_clicked();
    void addBookToInventory();
    void addBookToListTextBox();
    void saveListToDb();
    void exportListToTxt();
    void removeBookFromList();
    void addBookToShoppingList();
    void purchaseBooks();
};
#endif // MAINWINDOW_H
