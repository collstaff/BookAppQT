#include "mainwindow.h"
#include "Logging.h"
#include "logindialog.h"
#include "qscreen.h"
#include <QSplashScreen>
#include <QTimer>
#include <QApplication>
#include <iostream>
#include <fstream>
#include <QPixmap>
#include <list>
#include <QMessageBox>

#include <QPainter>
using namespace std;

int main(int argc, char *argv[])
{
    Log log;

    log.OpenLogFile();

    QApplication a(argc, argv);

    log.LogItem("Application Started");

    /* This code was originally used to populate the Inventory table. This code will be kept just in case, but isn't really needed anymore

    log.LogItem("Retrieving Inventory");

    // Reads the inventory data from the CSV file to be added to the database
    QVector<Book> bookList = readInventory();

    dbmanager db("BookStore.db");
    db.PopulateInventoryTable("BookStore.db", bookList);

    log.LogItem("Inventory retrieved");
    */

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    MainWindow w;
    QPixmap pixmap(":/splash.png");


    QScreen *screen;
    if (QGuiApplication::screens().count() >= 2) {
        screen = QGuiApplication::screens().at(1);
    }
    else {
        screen = QGuiApplication::screens().at(0);
    }

    QSize screenGeometry = screen->size();
    int height = screenGeometry.height() * .15;
    int width = screenGeometry.width() * .15;

    QSplashScreen *splash = new QSplashScreen(screen, pixmap);
    splash->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SplashScreen);

    a.processEvents();

    //a.processEvents();


    w.show();

    QPixmap SplashImage(width,height);

    SplashImage.fill(Qt::white);




    QSplashScreen SplashScreen(screen, SplashImage, Qt::WindowStaysOnTopHint);


    SplashScreen.show();

    SplashScreen.showMessage("Loading Book Store App");



    a.processEvents();

    QTimer::singleShot(5000, &SplashScreen, SLOT(close()));
    //QTimer::singleShot(5000, &w, SLOT(show()));
    w.show();

    logindialog loginDialog;
    loginDialog.exec();

    return a.exec();
}





