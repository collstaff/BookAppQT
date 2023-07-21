#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/QtSql>
#include "BookClass.h"
#include "User.h"
#include "Shopper.h"
#include "List.h"

class dbmanager
{
public:
    dbmanager(const QString& path);

    //Handles Database Connection
    std::string ConnectToDatabase(const QString& path);
    std::string DisconnectFromDatabase(const QString& path);

    //Handles Inventory Table Modification
    int PullNumberOfBooks(const QString& path);
    std::string CreateInventoryTable(const QString& path);
    std::string PopulateInventoryTable(const QString& path, QVector<Book> bookVector);
    bool InsertIntoInventoryTable(const QString& path, Book bookToInsert);
    QVector<Book> SearchInventoryTable(const QString& path, QString searchTerm);
    std::string UpdateQuantityInInventory(const QString& path, QString bookTitle);

    //Handles User Table Modification
    std::string CreateUserTable(const QString& path);
    std::string PopulateUserTable(const QString& path, QVector<User> userVector);
    bool InsertIntoUserTable(const QString& path, User userToInsert);
    bool DeleteFromUserTable(const QString& path, User userToDelete);
    bool UpdateUserTable(const QString& path, User userToUpdate);

    //Handles Shopper Table Modification
    std::string CreateShopperTable(const QString& path);
    std::string PopulateShopperTable(const QString& path, QVector<Shopper> shopperVector);
    std::string InsertIntoShopperTable(const QString& path, Shopper shopperToInsert);

    //Handles List Table
    std::string CreateListTable(const QString& path);
    std::string InsertIntoListTable(const QString& path, QVector<List> list);

    bool VerifyLogin(const QString& path, QString username, QString password);
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
