#include "dbmanager.h"
#include <QString>

using namespace std;


dbmanager::dbmanager(const QString& path)
{
    ConnectToDatabase(path);
}

std::string dbmanager::ConnectToDatabase(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: Connection Failed";
        return "Database Connection Failed";
    }
    else
    {
        qDebug() << "Database Connected";
        return "Database Connection Succeeded";
    }
}

std::string dbmanager::DisconnectFromDatabase(const QString& path)
{
    m_db.setDatabaseName(path);

    m_db.close();

    qDebug() << "Database Disconnected";
    return "Database Disconnected";
}

std::string dbmanager::CreateInventoryTable(const QString& path)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("CREATE TABLE IF NOT EXISTS INVENTORY("  \
                        "isbn TEXT PRIMARY KEY  NOT NULL," \
                        "title           TEXT    ,"\
                        "author           TEXT    ,"\
                        "publicationYear           TEXT,"\
                        "publisher           TEXT    ,"\
                        "genre           TEXT    ,"\
                        "desc           TEXT    ,"\
                        "msrp           REAL    ,"\
                        "quantity           INT    );");

    if(createQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Create Book Table Error" << createQuery.lastError();
    }

    return "";
}

QVector<Book> dbmanager::SearchInventoryTable(const QString& path, QString searchTerm)
{
    QVector<Book> bookReturnVector;
    Book bookToAdd;

    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;
    QString formatedSearchTerm = "%" + searchTerm + "%";

    createQuery.prepare("SELECT * FROM INVENTORY WHERE title LIKE ?");
    createQuery.bindValue(0, formatedSearchTerm);

    if(createQuery.exec())
    {
        success = true;

        qDebug() << createQuery.executedQuery();

        while (createQuery.next())
        {
            bookToAdd.isbn = createQuery.value(0).toString();
            bookToAdd.title = createQuery.value(1).toString();
            bookToAdd.author = createQuery.value(2).toString();
            bookToAdd.publisher = createQuery.value(3).toString();
            bookToAdd.publicationYear = createQuery.value(4).toString();
            bookToAdd.genre = createQuery.value(5).toString();
            bookToAdd.desc = createQuery.value(6).toString();
            bookToAdd.msrp = createQuery.value(7).toDouble();
            bookToAdd.quantity = createQuery.value(8).toInt();

            bookReturnVector.push_back(bookToAdd);
        }
    }
    else
    {
        qDebug() << "Retrieve Books Error" << createQuery.lastError();
    }

    return bookReturnVector;
}

bool dbmanager::InsertIntoInventoryTable(const QString& path, Book bookToInsert)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("INSERT INTO INVENTORY('isbn', 'title', 'author', 'publicationYear', 'publisher', 'genre', 'desc', 'msrp', 'quantity') VALUES (?, ?, ?, ?, ?, ? ,?, ?, ?)");
    createQuery.bindValue(0, bookToInsert.isbn);
    createQuery.bindValue(1, bookToInsert.title);
    createQuery.bindValue(2, bookToInsert.author);
    createQuery.bindValue(3, bookToInsert.publicationYear);
    createQuery.bindValue(4, bookToInsert.publisher);
    createQuery.bindValue(5, bookToInsert.genre);
    createQuery.bindValue(6, bookToInsert.desc);
    createQuery.bindValue(7, bookToInsert.msrp);
    createQuery.bindValue(8, bookToInsert.quantity);

    if(createQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Insertion of book failed";

    }

    return success;
}

/* This method was used to originally populate the database. This code will be kept just in case, but isn't really needed anymore

std::string dbmanager::PopulateInventoryTable(const QString& path, QVector<Book> bookVector)
{
    for (Book book : bookVector)
    {
        m_db.setDatabaseName(path);
        QSqlQuery createQuery;
        bool success = false;

        createQuery.prepare("INSERT INTO INVENTORY('isbn', 'title', 'author', 'publicationYear', 'publisher', 'msrp', 'quantity') VALUES (?, ?, ?, ?, ?, ? ,?)");
        createQuery.bindValue(0, book.isbn);
        createQuery.bindValue(1, book.title);
        createQuery.bindValue(2, book.author);
        createQuery.bindValue(3, book.publicationYear);
        createQuery.bindValue(4, book.publisher);
        createQuery.bindValue(5, book.msrp);
        createQuery.bindValue(6, book.quantity);

        if(createQuery.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "Insertion of book failed";
        }
    }



    return "";
}
*/

int dbmanager::PullNumberOfBooks(const QString& path)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;
    int numBooks = 0;

    createQuery.prepare("SELECT DISTINCT isbn FROM Inventory");

    if(createQuery.exec())
    {
        success = true;

        while (createQuery.next())
        {
            numBooks++;
        }
    }
    else
    {
        qDebug() << "Create Book Table Error" << createQuery.lastError();
    }

    return numBooks;
}

std::string dbmanager::CreateUserTable(const QString& path)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("CREATE TABLE IF NOT EXISTS USERS ("  \
                        "username TEXT PRIMARY KEY  NOT NULL," \
                        "password TEXT   NOT NULL);");

    if(createQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Create Book Table Error" << createQuery.lastError();
    }

    return "";
}

std::string dbmanager::CreateShopperTable(const QString& path)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("CREATE TABLE IF NOT EXISTS SHOPPERS ("  \
                        "name TEXT  NOT NULL," \
                        "email TEXT   NOT NULL," \
                        "amountSent REAL  NOT NULL);");

    if(createQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Create Book Table Error" << createQuery.lastError();
    }

    return "";
}

std::string dbmanager::InsertIntoShopperTable(const QString& path, Shopper shopperToInsert)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("INSERT INTO Shoppers('name', 'email', 'amountSent') VALUES (?, ?, ?)");

    createQuery.bindValue(0, shopperToInsert.shopperName);
    createQuery.bindValue(1, shopperToInsert.shopperEmail);
    createQuery.bindValue(2, shopperToInsert.shopperTotalCost);

    if(createQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Create Book Table Error" << createQuery.lastError();
    }

    return "";
}

std::string dbmanager::UpdateQuantityInInventory(const QString& path, QString bookTitle)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("UPDATE INVENTORY SET quantity = quantity - 1 WHERE title = ?");

    createQuery.bindValue(0, bookTitle);

    if(createQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Update Quantity Error" << createQuery.lastError();
    }

    return "";
}

std::string dbmanager::CreateListTable(const QString& path)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("CREATE TABLE IF NOT EXISTS LISTS ("  \
                        "listID int  NOT NULL," \
                        "bookTitle TEXT   NOT NULL," \
                        "bookAuthor TEXT  NOT NULL);");

    if(createQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Create Book Table Error" << createQuery.lastError();
    }

    return "";
}

std::string dbmanager::InsertIntoListTable(const QString& path, QVector<List> list)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;
    int maxId = 0;

    //Get the max list ID
    createQuery.prepare("SELECT MAX(listID) FROM LISTS");

    if(createQuery.exec())
    {
        while (createQuery.next())
        {
            maxId = createQuery.value(0).toInt();
        }

        maxId += 1;
    }

    for (List listItem : list)
    {
        createQuery.prepare("INSERT INTO LISTS('listID', 'bookTitle', 'bookAuthor') VALUES (?, ?, ?)");

        createQuery.bindValue(0, maxId);
        createQuery.bindValue(1, listItem.bookTitle);
        createQuery.bindValue(2, listItem.bookAuthor);

        if(createQuery.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "Create Book Table Error" << createQuery.lastError();
        }
    }
    return "";
}

bool dbmanager::InsertIntoUserTable(const QString& path, User userToInsert)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("INSERT INTO USERS('username', 'password') VALUES (?, ?)");

    createQuery.bindValue(0, userToInsert.user);
    createQuery.bindValue(1, userToInsert.pass);

    if(createQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Insert User Error" << createQuery.lastError();
        success = false;
    }

    return success;
}

bool dbmanager::DeleteFromUserTable(const QString& path, User userToDelete)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("DELETE FROM USERS WHERE username = ?");

    createQuery.bindValue(0, userToDelete.user);

    if(createQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Insert User Error" << createQuery.lastError();
        success = false;
    }

    return success;
}

bool dbmanager::UpdateUserTable(const QString& path, User userToUpdate)
{
    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("UPDATE USERS SET password = ? WHERE username = ?");

    createQuery.bindValue(0, userToUpdate.pass);
    createQuery.bindValue(1, userToUpdate.user);

    if(createQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Update User Error" << createQuery.lastError();
        success = false;
    }

    return success;
}


//Method to verify that the login is correct
bool dbmanager::VerifyLogin(const QString& path, QString username, QString password)
{
    bool isValidLogin = false;

    m_db.setDatabaseName(path);
    QSqlQuery createQuery;
    bool success = false;

    createQuery.prepare("SELECT * FROM USERS WHERE username=? AND password=?");

    createQuery.bindValue(0, username);
    createQuery.bindValue(1, password);

    createQuery.exec();

    while (createQuery.next())
    {
        isValidLogin = true;
    }

    return isValidLogin;
}
