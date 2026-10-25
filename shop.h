#ifndef SHOP_H
#define SHOP_H

#include <string>
using namespace std;

class Shop
{
public:
    string shopId;
    string shopName;
    string ownerName;
    string phoneNumber;

    void displayShop();
};

#endif