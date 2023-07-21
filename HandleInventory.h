#ifndef HANDLEINVENTORY_H
#define HANDLEINVENTORY_H

// Method that reads through the book data
#include <QVector>
#include <QFile>
#include <QDir>
#include <algorithm>
#include <random>
#include <QRandomGenerator>

#include "BookClass.h"
#include "qcoreapplication.h"
#include "qdebug.h"

void test_current() {
    qInfo() << QDir::currentPath() << "\n";

    qInfo() << QCoreApplication::applicationFilePath();
}

double AddMsrpQuantity(Book book) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(34.99, 103.97);

    QString finalMsrp = QString::number(QString::number(dis(gen), 'f', 2).toDouble(), 'g', 10);

    book.msrp = finalMsrp.toDouble();

    return book.msrp;
}

int AddQuantityValue(Book book) {
    //TO DO: test this, as I thought random forumla was (rand()% ((56+1) - 2) + 2);
    book.quantity = std::rand() % 56 + 2; // Random quantity between 56 and 2

    return book.quantity;
}

QVector<Book> readInventory() {
    // Create vector of type book and file variable
    QVector<Book> bookVector;
    QString path = QDir::currentPath();
    QFile file("../Wed_29_BookStoreApp/booklist.csv");

    file.open(QIODevice::ReadOnly);
    Book book;

    // Get the header
    QStringList stringList;
    file.readLine();

    while(!file.atEnd()) {
        QString line = file.readLine();
        stringList = line.split(',');
        book.isbn = stringList[0];
        book.title = stringList[1];
        book.author = stringList[2];
        book.publicationYear = stringList[3];
        book.publisher = stringList[4];

        book.msrp = AddMsrpQuantity(book);
        book.quantity = AddQuantityValue(book);

        bookVector.push_back(book);
    }

    return bookVector;
}

#endif // HANDLEINVENTORY_H
