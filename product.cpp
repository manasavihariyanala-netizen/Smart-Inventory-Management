#include "Product.h"
#include <iostream>
using namespace std;

void Product::displayProduct()
{
    cout << "Product ID   : " << productId << endl;
    cout << "Product Name : " << productName << endl;
    cout << "Price        : " << price << endl;
    cout << "Quantity     : " << quantity << endl;
}

bool Product::isLowStock()
{
    if (quantity <= 10)
    {
        return true;
    }

    return false;
}
