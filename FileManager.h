#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Shop.h"
#include "Product.h"
#include <string>
#include <vector>

using namespace std;

// Save shop information
void saveShop(const Shop& shop);

// Find shop using Shop ID
bool findShop(const string& shopId, Shop& shop);

// Save product information
void saveProduct(const Product& product);

// Load products belonging to a shop
vector<Product> loadProducts(const string& shopId);

// Update an existing product
bool updateProduct(const Product& updatedProduct);

// Delete a product
bool deleteProduct(const string& shopId, int productId);
bool isValidName(string name);

#endif