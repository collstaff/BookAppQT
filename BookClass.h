#ifndef BOOKCLASS_H
#define BOOKCLASS_H

// Book class that contains properties about the book
#include <string>
#include <list>
#include <fstream>
#include <set>
#include <qstring.h>
#include <QFile>

class Book {

public:
    QString isbn;
    QString title;
    QString author;
    QString publisher;
    QString publicationYear;
    QString desc;
    QString genre;
    double msrp;
    int quantity;
    std::set<Book*>bookSet;

    std::list<Book*>newBooks;



    /*
    //creates book object, push into books list, seperate method to output to file
    void ExportBookList(std::list<Book> bookList) {
        QFile file;
        std::list<Book> newBooks;

        file.open("booklist.csv", std::ios_base::app);

        for (Book book : bookList) {
            file << book.isbn << ',';
            file << book.title << ',';
            file << book.author << ',';
            file << book.publisher << ',';
            file << book.publicationYear << ',';
            file << book.desc << ',';
            file << book.genre << ',';
            file << book.msrp << ',';
            file << book.quantity << "\n";
        }


        file.close();
    };
    */
};

#endif // BOOKCLASS_H
