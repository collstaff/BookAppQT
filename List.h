#include <QString>

#ifndef LIST_H
#define LIST_H

#endif // LIST_H

class List
{

public:
    List(QString title, QString author)
    {
        bookTitle = title;
        bookAuthor = author;

    }

    QString bookTitle;
    QString bookAuthor;
private:

};
