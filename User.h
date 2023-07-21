#include <QString>

#ifndef USER_H
#define USER_H

#endif // USER_H

class User
{
public:
    User(QString username, QString password)
    {
        user = username;
        pass = password;
    }

    QString user;
    QString pass;
private:

};
