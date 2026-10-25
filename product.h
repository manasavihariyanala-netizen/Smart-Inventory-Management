#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Product
{
public:
    string shopId;
    int productId;
    string productName;
    float price;
    int quantity;

    void displayProduct();
    bool isLowStock();
};

#endif