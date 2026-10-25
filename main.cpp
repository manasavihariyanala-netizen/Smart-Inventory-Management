
#include <iostream>
#include <vector>
#include <limits>
#include <string>

#include "Shop.h"
#include "Product.h"
#include "FileManager.h"

using namespace std;


// ========================================
// WELCOME SCREEN
// ========================================

void welcomeScreen()
{
    cout << "\n\n";
    cout << "==================================================" << endl;
    cout << "        SMART INVENTORY MANAGEMENT SYSTEM        " << endl;
    cout << "==================================================" << endl;

    cout << "\n        Welcome to Smart Inventory!" << endl;

    cout << "\n        1. Shop Login" << endl;
    cout << "        2. New Shop Registration" << endl;
    cout << "        3. Exit" << endl;

    cout << "\n==================================================" << endl;
}


// ========================================
// SHOP REGISTRATION
// ========================================

bool registerShop(Shop& shop)
{
    cout << "\n==================================================" << endl;
    cout << "              NEW SHOP REGISTRATION              " << endl;
    cout << "==================================================" << endl;

    cout << "\nEnter Shop ID: ";
    cin >> shop.shopId;

    // Check whether Shop ID already exists
    Shop existingShop;

    if (findShop(shop.shopId, existingShop))
    {
        cout << "\nShop ID already exists!" << endl;
        cout << "Please use a different Shop ID." << endl;

        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Shop Name: ";
    getline(cin, shop.shopName);

    cout << "Enter Owner Name: ";
    getline(cin, shop.ownerName);

    cout << "Enter Phone Number: ";
    getline(cin, shop.phoneNumber);

    saveShop(shop);

    cout << "\n==================================================" << endl;
    cout << "        SHOP REGISTERED SUCCESSFULLY!            " << endl;
    cout << "==================================================" << endl;

    cout << "\nWelcome, " << shop.shopName << "!" << endl;

    return true;
}


// ========================================
// SHOP LOGIN
// ========================================

bool loginShop(Shop& shop)
{
    string shopId;

    cout << "\n==================================================" << endl;
    cout << "                  SHOP LOGIN                     " << endl;
    cout << "==================================================" << endl;

    cout << "\nEnter Shop ID: ";
    cin >> shopId;

    if (findShop(shopId, shop))
    {
        cout << "\nLogin successful!" << endl;
        cout << "Welcome back, " << shop.shopName << "!" << endl;

        return true;
    }

    cout << "\nShop ID not found." << endl;
    cout << "Please register your shop first." << endl;

    return false;
}


// ========================================
// SHOP DASHBOARD
// ========================================

void shopDashboard(Shop& shop)
{
    int choice;

    do
    {
        cout << "\n\n";
        cout << "==================================================" << endl;
        cout << "                  SHOP DASHBOARD                 " << endl;
        cout << "==================================================" << endl;

        cout << " Shop: " << shop.shopName << endl;
        cout << " Owner: " << shop.ownerName << endl;

        cout << "==================================================" << endl;

        cout << "\n  1. Add Product" << endl;
        cout << "  2. View Products" << endl;
        cout << "  3. Search Product" << endl;
        cout << "  4. Update Product" << endl;
        cout << "  5. Delete Product" << endl;
        cout << "  6. Low Stock Products" << endl;
        cout << "  7. Shop Information" << endl;
        cout << "  8. Logout" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        // ========================================
        // ADD PRODUCT
        // ========================================

        if (choice == 1)
        {
            Product product;

            product.shopId = shop.shopId;

            cout << "\n---------- ADD PRODUCT ----------" << endl;

            string input;

            cout << "Enter Product ID: ";
            cin >> input;

            try
            {
                product.productId = stoi(input);
            }
            catch (...)
            {
                cout << "Invalid Product ID." << endl;
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Product Name: ";
            getline(cin, product.productName);

            if (product.productName.empty())
            {
                cout << "Product name cannot be empty." << endl;
                continue;
            }
            if (!isValidName(product.productName))
            {
               cout << "Invalid product name. Please enter letters only." << endl;
               continue;
            }

            cout << "Enter Price: ";
            cin >> input;


            try
            {
                product.price = stof(input);
            }
            catch (...)
            {
                cout << "Invalid price." << endl;
                continue;
            }

            cout << "Enter Quantity: ";
            cin >> input;

            try
            {
                product.quantity = stoi(input);
            }
            catch (...)
            {
                cout << "Invalid quantity." << endl;
                continue;
            }

            saveProduct(product);

            cout << "\nProduct added successfully!" << endl;

            if (product.isLowStock())
            {
                cout << "\n*** LOW STOCK ALERT ***" << endl;

                cout << product.productName
                     << " has only "
                     << product.quantity
                     << " items remaining." << endl;
            }
        }


        // ========================================
        // VIEW PRODUCTS
        // ========================================

        else if (choice == 2)
        {
            vector<Product> products = loadProducts(shop.shopId);

            cout << "\n========== YOUR PRODUCTS ==========" << endl;

            if (products.empty())
            {
                cout << "No products available." << endl;
            }
            else
            {
                for (Product product : products)
                {
                    cout << "\n----------------------------------------" << endl;

                    product.displayProduct();

                    if (product.isLowStock())
                    {
                        cout << "*** LOW STOCK ALERT ***" << endl;
                    }
                }
            }
        }


        // ========================================
        // SEARCH PRODUCT
        // ========================================

        else if (choice == 3)
        {
            int searchId;

            cout << "\n---------- SEARCH PRODUCT ----------" << endl;

            cout << "Enter Product ID: ";
            cin >> searchId;

            vector<Product> products = loadProducts(shop.shopId);

            bool found = false;

            for (Product product : products)
            {
                if (product.productId == searchId)
                {
                    cout << "\nProduct found!" << endl;
                    cout << "----------------------------------------" << endl;

                    product.displayProduct();

                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "\nProduct not found." << endl;
            }
        }


        // ========================================
        // UPDATE PRODUCT
        // ========================================

        else if (choice == 4)
        {
            cout << "\n---------- UPDATE PRODUCT ----------" << endl;

            int updateId;

            cout << "Enter Product ID to update: ";
            cin >> updateId;

            vector<Product> products = loadProducts(shop.shopId);

            bool found = false;

            for (Product product : products)
            {
                if (product.productId == updateId)
                {
                    found = true;

                    cout << "\nCurrent Product Details:" << endl;
                    product.displayProduct();

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "\nEnter New Product Name: ";
                    getline(cin, product.productName);

                    string input;

                    cout << "Enter New Price: ";
                    cin >> input;

                    try
                    {
                        product.price = stof(input);
                    }
                    catch (...)
                    {
                        cout << "Invalid price." << endl;
                        break;
                    }

                    cout << "Enter New Quantity: ";
                    cin >> input;

                    try
                    {
                        product.quantity = stoi(input);
                    }
                    catch (...)
                    {
                        cout << "Invalid quantity." << endl;
                        break;
                    }

                    updateProduct(product);

                    cout << "\nProduct updated successfully!" << endl;

                    if (product.isLowStock())
                    {
                        cout << "\n*** LOW STOCK ALERT ***" << endl;
                    }

                    break;
                }
            }

            if (!found)
            {
                cout << "\nProduct not found." << endl;
            }
        }


        // ========================================
        // DELETE PRODUCT
        // ========================================

        else if (choice == 5)
        {
            cout << "\n---------- DELETE PRODUCT ----------" << endl;

            int deleteId;

            cout << "Enter Product ID to delete: ";
            cin >> deleteId;

            bool deleted = deleteProduct(shop.shopId, deleteId);

            if (deleted)
            {
                cout << "\nProduct deleted successfully!" << endl;
            }
            else
            {
                cout << "\nProduct not found." << endl;
            }
        }


        // ========================================
        // LOW STOCK PRODUCTS
        // ========================================

        else if (choice == 6)
        {
            vector<Product> products = loadProducts(shop.shopId);

            cout << "\n========== LOW STOCK PRODUCTS ==========" << endl;

            bool found = false;

            for (Product product : products)
            {
                if (product.isLowStock())
                {
                    cout << "\n----------------------------------------" << endl;

                    product.displayProduct();

                    found = true;
                }
            }

            if (!found)
            {
                cout << "\nNo low-stock products." << endl;
            }
        }


        // ========================================
        // SHOP INFORMATION
        // ========================================

        else if (choice == 7)
        {
            shop.displayShop();
        }


        // ========================================
        // LOGOUT
        // ========================================

        else if (choice == 8)
        {
            cout << "\nLogging out..." << endl;
            cout << "Thank you, " << shop.shopName << "!" << endl;
        }


        // ========================================
        // INVALID CHOICE
        // ========================================

        else
        {
            cout << "\nInvalid choice. Please enter 1 to 8." << endl;
        }

    } while (choice != 8);
}


// ========================================
// MAIN FUNCTION
// ========================================

int main()
{
    int choice;

    while (true)
    {
        welcomeScreen();

        cout << "\nEnter your choice: ";
        cin >> choice;

        // ========================================
        // LOGIN
        // ========================================

        if (choice == 1)
        {
            Shop shop;

            if (loginShop(shop))
            {
                shopDashboard(shop);
            }
        }


        // ========================================
        // REGISTRATION
        // ========================================

        else if (choice == 2)
        {
            Shop shop;

            registerShop(shop);
        }


        // ========================================
        // EXIT
        // ========================================

        else if (choice == 3)
        {
            cout << "\n==================================================" << endl;
            cout << "       Thank you for using Smart Inventory!      " << endl;
            cout << "==================================================" << endl;

            break;
        }


        // ========================================
        // INVALID CHOICE
        // ========================================

        else
        {
            cout << "\nInvalid choice. Please enter 1, 2 or 3." << endl;
        }
    }

    return 0;
}

