#include <QString>

#ifndef SHOPPER_H
#define SHOPPER_H

#endif // SHOPPER_H

class Shopper
{

public:
    Shopper(QString name, QString email, QString orderCost)
    {
        shopperName = name;
        shopperEmail = email;
        shopperTotalCost = orderCost;
    }

    QString shopperName;
    QString shopperEmail;
    QString shopperTotalCost;
private:

};
