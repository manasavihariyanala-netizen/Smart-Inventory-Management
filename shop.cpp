#include "Shop.h"
#include <iostream>
using namespace std;

void Shop::displayShop()
{
    cout << "\n----------------------------------------" << endl;
    cout << "           SHOP INFORMATION" << endl;
    cout << "----------------------------------------" << endl;

    cout << "Shop ID      : " << shopId << endl;
    cout << "Shop Name    : " << shopName << endl;
    cout << "Owner Name   : " << ownerName << endl;
    cout << "Phone Number : " << phoneNumber << endl;
}