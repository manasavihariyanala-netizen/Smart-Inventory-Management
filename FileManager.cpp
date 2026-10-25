#include "FileManager.h"
#include <fstream>
#include <sstream>
#include<cctype>

using namespace std;

 bool isValidName(string name)
{
    for (char c : name)
    {
        if (!isalpha(c) && c != ' ')
        {
            return false;
        }
    }
    return true;
}

// ========================================
// SAVE SHOP
// ========================================

void saveShop(const Shop& shop)
{
    ofstream file("shops.txt", ios::app);

    file << shop.shopId << "|"
         << shop.shopName << "|"
         << shop.ownerName << "|"
         << shop.phoneNumber << endl;

    file.close();
}


// ========================================
// FIND SHOP
// ========================================

bool findShop(const string& shopId, Shop& shop)
{
    ifstream file("shops.txt");

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id;
        string name;
        string owner;
        string phone;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, owner, '|');
        getline(ss, phone, '|');

        if (id == shopId)
        {
            shop.shopId = id;
            shop.shopName = name;
            shop.ownerName = owner;
            shop.phoneNumber = phone;

            file.close();
            return true;
        }
    }

    file.close();

    return false;
}


// ========================================
// SAVE PRODUCT
// ========================================

void saveProduct(const Product& product)
{
    ofstream file("products.txt", ios::app);

    file << product.shopId << "|"
         << product.productId << "|"
         << product.productName << "|"
         << product.price << "|"
         << product.quantity << endl;

    file.close();
}


// ========================================
// LOAD PRODUCTS
// ========================================

// ========================================
// LOAD PRODUCTS
// ========================================

vector<Product> loadProducts(const string& shopId)
{
    vector<Product> products;

    ifstream file("products.txt");

    if (!file)
    {
        return products;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string id;
        string productId;
        string name;
        string price;
        string quantity;

        getline(ss, id, '|');
        getline(ss, productId, '|');
        getline(ss, name, '|');
        getline(ss, price, '|');
        getline(ss, quantity, '|');

        if (id.empty() || productId.empty() ||
            name.empty() || price.empty() || quantity.empty())
        {
            continue;
        }

        if (id == shopId)
        {
            Product product;

            product.shopId = id;
            product.productId = stoi(productId);
            product.productName = name;
            product.price = stof(price);
            product.quantity = stoi(quantity);

            products.push_back(product);
        }
    }

    file.close();

    return products;
}


// ========================================
// UPDATE PRODUCT
// ========================================

bool updateProduct(const Product& updatedProduct)
{
    ifstream file("products.txt");

    if (!file)
    {
        return false;
    }

    vector<Product> products;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id;
        string productId;
        string name;
        string price;
        string quantity;

        getline(ss, id, '|');
        getline(ss, productId, '|');
        getline(ss, name, '|');
        getline(ss, price, '|');
        getline(ss, quantity, '|');

        Product product;

        product.shopId = id;
        product.productId = stoi(productId);
        product.productName = name;
        product.price = stof(price);
        product.quantity = stoi(quantity);

        if (id == updatedProduct.shopId &&
            product.productId == updatedProduct.productId)
        {
            product.productName = updatedProduct.productName;
            product.price = updatedProduct.price;
            product.quantity = updatedProduct.quantity;
        }

        products.push_back(product);
    }

    file.close();

    ofstream outputFile("products.txt");

    for (Product product : products)
    {
        outputFile << product.shopId << "|"
                   << product.productId << "|"
                   << product.productName << "|"
                   << product.price << "|"
                   << product.quantity << endl;
    }

    outputFile.close();

    return true;
}


// ========================================
// DELETE PRODUCT
// ========================================

bool deleteProduct(const string& shopId, int productId)
{
    ifstream file("products.txt");

    if (!file)
    {
        return false;
    }

    vector<Product> products;

    string line;

    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id;
        string productIdText;
        string name;
        string price;
        string quantity;

        getline(ss, id, '|');
        getline(ss, productIdText, '|');
        getline(ss, name, '|');
        getline(ss, price, '|');
        getline(ss, quantity, '|');

        Product product;

        product.shopId = id;
        product.productId = stoi(productIdText);
        product.productName = name;
        product.price = stof(price);
        product.quantity = stoi(quantity);

        if (id == shopId && product.productId == productId)
        {
            found = true;
            continue;
        }

        products.push_back(product);
    }

    file.close();

    ofstream outputFile("products.txt");

    for (Product product : products)
    {
        outputFile << product.shopId << "|"
                   << product.productId << "|"
                   << product.productName << "|"
                   << product.price << "|"
                   << product.quantity << endl;
    }

    outputFile.close();

    return found;
}