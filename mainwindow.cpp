#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "BookClass.h"
#include "Logging.h"
#include "dbmanager.h"
#include "hardwareinfo.h"
#include <QSplashScreen>
#include <QTimer>
#include <QApplication>
#include <iostream>
#include <QMessageBox>
#include <QRegularExpression>
#include "notes.h"
#include "adduser.h"
#include "deleteuser.h"
#include "changeuserpass.h"
#include "preferences.h"

QVector<Book> SearchInventory(QVector<Book> bookVector, QString searchTerm);
QVector<Book> readInventory();
dbmanager db("BookStore.db");

//Create a global book list and shopping cart variable that will persist through tab switches
QVector<QString> currentBookListVector;
QVector<QString> currentShoppingListVector;

const QString dbName = "BookStore.db";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Connect to the database
    db.ConnectToDatabase(dbName);

    //Create the book table
    db.CreateInventoryTable(dbName);

    //Create User Table
    db.CreateUserTable(dbName);

    //Create Shoppers Table
    db.CreateShopperTable(dbName);

    //Create Lists Table
    db.CreateListTable(dbName);

    //Retrieves the number of books in the database
    int numBooks = db.PullNumberOfBooks(dbName);

    ui->setupUi(this);
    ui->statusbar->showMessage("Number of books in inventory: " + QString::number(numBooks));
}

MainWindow::~MainWindow()
{
    Log log;

    log.OpenLogFile();

    log.LogItem("Exiting Application\n");

    log.CloseLogFile();

    db.DisconnectFromDatabase("BookStore.db");

    delete ui;
}

void MainWindow::search_inventory()
{
    Log log;

    log.OpenLogFile();
    ui->statusbar->currentMessage();


    //Clear values every time the search button is clicked to provide cleaner searching
    ui->bookList->clear();
    ui->searchOutputTxt_3->clear();

    QString searchTerm;

    //Determine who sent the command
    if (QObject::sender()->objectName() == "searchBtn")
    {
        searchTerm = ui->searchLineEdt->displayText();
    }
    else if (QObject::sender()->objectName() == "titleSearchBtn")
    {
        searchTerm = ui->titleTxt->displayText();
    }

    //Values are already used and no longer needed
    ui->searchLineEdt->clear();
    ui->titleTxt->clear();

    log.LogItem("Search button clicked. Search term: " + searchTerm);

    QVector<Book> booksToOutput = db.SearchInventoryTable(dbName, searchTerm);

    ui->statusbar->showMessage("Searching Inventory");


    if (booksToOutput.count() <= 0) {
        QMessageBox::information(this,"No Results Returned", "The provided search term did not return any books!", QMessageBox::Ok);
        ui->statusbar->showMessage("Search Returned No Books!");
    }
    else {

        //Determine who sent the command
        if (QObject::sender()->objectName() == "searchBtn")
        {
            for(Book book : booksToOutput) {
                //This displays search results for the search page text box
                QString stringToOutput = "---------------------\nISBN: " + book.isbn + "\n" + "Title: " + book.title + "\n" + "Author: " + book.author + "\n" +
                                        "Publication Year: " + book.publicationYear + "\n" + "Publisher: " + book.publisher + "\nGenre: " + book.genre + "\n" +
                                        "Description: " + book.desc + "\n" + "MSRP: $" + QString::number(book.msrp) + "\n" + "Quantity: " + QString::number(book.quantity) + "\n";
                ui->searchOutputTxt_3->appendPlainText(stringToOutput);
            }
        }
        else if (QObject::sender()->objectName() == "titleSearchBtn")
        {
            for(Book book : booksToOutput)
            {
                //This displays search results for the add book page list box
                if (book.quantity > 0)
                {
                    ui->bookList->addItem("Title: " + book.title + "\nAuthor: " + book.author + "\nMSRP: $" + QString::number(book.msrp) + "\nInventory Quantity: " + QString::number(book.quantity) + "\n");
                }
            }
        }

        ui->statusbar->showMessage("Number of books returned from search: " + QString::number(booksToOutput.count()));
    }

    log.CloseLogFile();
}

void MainWindow::on_actionHardware_Info_triggered()
{
    HardwareInfo hardwareInfo;
    hardwareInfo.setModal(true);
    hardwareInfo.exec();
}

void MainWindow::on_actionPreferences_triggered()
{

    Preferences prefScreen(this);
    prefScreen.exec();
}

void MainWindow::on_actionNotes_triggered()
{
    Notes notes;
    notes.setModal(true);
    notes.exec();
}

void MainWindow::showHelpWindow() {
    if (QObject::sender()->objectName() == "searchHelp") {
        QMessageBox::information(this,"Search Menu", "In order to perform a search, simply type in the title you would like to search for. You are also able to enter simple search terms to return multiple book entries", QMessageBox::Ok);
    }
    else if (QObject::sender()->objectName() == "addBookHelp") {
        QMessageBox::information(this,"Add Book Menu", "In order to add a book, simply enter the appropriate information in the text boxes below, then hit 'Add To Inventory'", QMessageBox::Ok);
    }
    else if (QObject::sender()->objectName() == "cartHelp") {
        QMessageBox::information(this,"Shopping Cart Menu", "This page displays the current books in your shopping cart. In order to purchase, all you need to do is enter your information in the given boxes and press the purchase button", QMessageBox::Ok);
    }
    else if (QObject::sender()->objectName() == "adminHelp") {
        QMessageBox::information(this,"Admin Help Menu", "This menu provides administrators functionality to the user's of the application and their accounts. This functionality includes adding and removing users, and changing user passwords", QMessageBox::Ok);
    }
    else if (QObject::sender()->objectName() == "bookListHelp") {
        QMessageBox::information(this,"Book List Help Menu", "This menu allows users to add books they want to a list that can be saved and exported to a text file. Simply enter the desired title into the search box, click one of the selections, then click either 'Add Book To List' or"
                                                             " 'Add Book To Shopping Cart'. To save or export your list to a text file, simply click the corresponding button.", QMessageBox::Ok);
    }

}


void MainWindow::on_addUserBtn_clicked()
{
    AddUser addUserScreen;
    addUserScreen.exec();
}

void MainWindow::on_deleteUserBtn_clicked()
{
    deleteuser deleteUserScreen;
    deleteUserScreen.exec();
}

void MainWindow::on_changePassBtn_clicked()
{
    ChangeUserPass changePassScreen;
    changePassScreen.exec();
}

void MainWindow::addBookToInventory()
{
    Log log;
    log.OpenLogFile();

    log.LogItem("Inserting new book into Inventory table");

    //Build an error message if there are elements that do not match the correct format
    QString errorMessage = "";

    //REQUIRED VALUES
    //----------------------------------------------
    QString isbn = ui->isbnTxt->toPlainText();
    QString title = ui->bookTitleTxt->toPlainText();
    QString author = ui->authorTxt->toPlainText();
    QString pubYear = ui->pubYearTxt->toPlainText();
    QString pub = ui->pubTxt->toPlainText();
    QString msrp = ui->msrpTxt->toPlainText();
    QString quant = ui->quantTxt->toPlainText();
    //----------------------------------------------

    //NOT REQUIRED VALUES
    //----------------------------------------------
    QString genre = ui->genreTxt->toPlainText();
    QString desc = ui->descTxt->toPlainText();
    //----------------------------------------------

    if((isbn.length() != 13 && isbn.length() != 10))
    {
        errorMessage.append("ISBN must be either 10 or 13 numbers\n");
    }

    if(title.length() == 0)
    {
        errorMessage.append("You must enter a title\n");
    }

    if(author.length() == 0)
    {
        errorMessage.append("You must enter an author\n");
    }

    if(pubYear.length() == 0)
    {
        errorMessage.append("You must enter a publish year\n");
    }

    if(pub.length() == 0)
    {
        errorMessage.append("You must enter a publisher\n");
    }

    if(msrp.length() == 0)
    {
        errorMessage.append("You must enter an MSRP\n");
    }

    if(quant.length() == 0)
    {
        errorMessage.append("You must enter a quantity\n");
    }


    //If the error message is NOT an empty string, display it and prevent insertion into the DB
    if (errorMessage != "")
    {
        log.LogItem("Book add entries invalid. Halting book insertion");

        QMessageBox invalidEntriesMsg;
        invalidEntriesMsg.setText(errorMessage);
        invalidEntriesMsg.exec();
    }
    else
    {
        //Entries are valid. Create book object and insert into DB
        log.LogItem("Book add entries valid. Continuing book insertion");

        Book bookToInsert;

        bookToInsert.isbn = isbn;
        bookToInsert.title = title;
        bookToInsert.author = author;
        bookToInsert.publisher = pub;
        bookToInsert.publicationYear = pubYear;
        bookToInsert.msrp = msrp.toDouble();
        bookToInsert.quantity = quant.toInt();

        if (genre == "")
        {
            bookToInsert.genre = "NONE";
        }
        else
        {
           bookToInsert.genre = genre;
        }

        if (desc == "")
        {
            bookToInsert.desc = "NONE";
        }
        else
        {
           bookToInsert.desc = desc;
        }

        //Insert into inventory table
        auto didSucceed = db.InsertIntoInventoryTable(dbName, bookToInsert);

        if (didSucceed)
        {
            log.LogItem("Insert succeeded");
            ui->statusbar->showMessage("Book Successfully Added!");
            QMessageBox::information(this, "Book Insert", "Book Successfully Added!");

            ui->isbnTxt->clear();
            ui->bookTitleTxt->clear();
            ui->authorTxt->clear();
            ui->pubYearTxt->clear();
            ui->pubTxt->clear();
            ui->msrpTxt->clear();
            ui->quantTxt->clear();
            ui->genreTxt->clear();
            ui->descTxt->clear();
        }
        else
        {
            log.LogItem("Insertion failed");
            ui->statusbar->showMessage("Book Not Added Due To Error.");
            QMessageBox::information(this, "Book Insert", "Book Insertion Failed.");
        }

        //Refresh the status bar to reflect the number of books in inventory
        log.LogItem("Refreshing status bar for new book count");

        int numBooks = db.PullNumberOfBooks(dbName);
        ui->statusbar->showMessage("Number of books in inventory: " + QString::number(numBooks));

        log.LogItem("Status bar refreshed with new book count");

        log.CloseLogFile();
    }
}

void MainWindow::addBookToListTextBox()
{
    QString bookToMove = ui->bookList->currentItem()->text();

    currentBookListVector.push_back(bookToMove);

    ui->finalBookList->addItem(bookToMove);

}

void MainWindow::saveListToDb()
{
    QVector<List> bookVector;
    QString title;
    QString author;

    for(int i = 0; i < ui->finalBookList->count(); ++i)
    {
        QString item = ui->finalBookList->item(i)->text();

        QRegularExpression re("Title: (.+)\n");

        QRegularExpressionMatch match = re.match(item);

        if (match.hasMatch())
        {
            title = match.captured(1);
        }

        QRegularExpression reg("Author: (.*)\n");

        QRegularExpressionMatch regMatch = reg.match(item);

        if (regMatch.hasMatch())
        {
            author = regMatch.captured(1);
        }

        List bookForList(title, author);

        bookVector.push_back(bookForList);

        ui->statusbar->showMessage("List Saved");
    }

    db.InsertIntoListTable(dbName, bookVector);
}



void MainWindow::addBookToShoppingList()
{
    double subtotal;
    double tax;
    double grandTotal;
    QString bookToMove = ui->bookList->currentItem()->text();

    currentShoppingListVector.push_back(bookToMove);

    ui->shoppingList->addItem(bookToMove);

    for(int i = 0; i < ui->shoppingList->count(); ++i)
    {
        QString item = ui->shoppingList->item(i)->text();

        //Probably the hardest thing to figure out
        QRegularExpression re("MSRP:\\s*\\$(?<price>[-+]?\\d*\\.?\\d+)");

        QRegularExpressionMatch match = re.match(item);

        if (match.hasMatch())
        {
            QString doubleAsString = match.captured("price");
            double convertedToDouble = doubleAsString.toDouble();

            subtotal += convertedToDouble;
        }
    }

    tax = (subtotal * 0.06);
    grandTotal = tax + subtotal;

    ui->grandTotalTxt->setText("$" + QString::number(grandTotal, 'f', 2));
    ui->taxTxt->setText("$" + QString::number(tax, 'f', 2));
    ui->subTotalTxt->setText("$" + QString::number(subtotal, 'f', 2));
}

void MainWindow::exportListToTxt()
{
    QFile file;

    file.setFileName("BookList.txt");

    QString stringToExport;


    for(int i = 0; i < ui->finalBookList->count(); ++i)
    {
        QString item = ui->finalBookList->item(i)->text();
        stringToExport.append(item + "\n");
    }


    file.open(QIODevice::WriteOnly);

    QTextStream out(&file);
    out << "Book List\n------------------------\n" << stringToExport;

    ui->statusbar->showMessage("List exported to text file");

}

void MainWindow::removeBookFromList()
{
    delete ui->finalBookList->currentItem();
}

void MainWindow::purchaseBooks()
{
    QString name;
    QString email;
    QString totalAmount;

    QString subtotal = ui->subTotalTxt->displayText();
    QString tax = ui->taxTxt->displayText();
    QString grandtotal = ui->grandTotalTxt->displayText();

    name = ui->nameTxt->toPlainText();
    email = ui->emailTxt->toPlainText();
    totalAmount = ui->grandTotalTxt->text();

    if (name == "" || email == "" || totalAmount == "")
    {
        QMessageBox::information(this,"Invalid input", "You must enter a name and email address and have books in your shopping cart", QMessageBox::Ok);
    }
    else
    {
        //Loop through each item and get the book title
        for(int i = 0; i < ui->shoppingList->count(); ++i)
        {
            QString item = ui->shoppingList->item(i)->text();


            QRegularExpression re("Title: (.+)\n");

            QRegularExpressionMatch match = re.match(item);

            if (match.hasMatch())
            {
                //Reduce the quantity count by 1 through the update quantity method
                QString bookTitle = match.captured(1);
                db.UpdateQuantityInInventory(dbName, bookTitle);
            }
        }

        Shopper shopper(name, email, totalAmount);

        db.InsertIntoShopperTable(dbName, shopper);

        QMessageBox::information(this,"Purchase Receipt", "RECEIPT\n-------------------\nShopper name: " + name + "\nShopper email: " + email + "\nSubtotal: " + subtotal + "\nTax: " + tax + "\nGrand Total: " + grandtotal + "\n-------------------", QMessageBox::Ok);

        ui->nameTxt->clear();
        ui->emailTxt->clear();
        ui->taxTxt->clear();
        ui->subTotalTxt->clear();
        ui->grandTotalTxt->clear();
        ui->shoppingList->clear();
        ui->statusbar->showMessage("Books purchased! Thank you " + name + "!");
    }
}







