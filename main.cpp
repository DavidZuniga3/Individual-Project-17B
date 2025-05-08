/* 
 * File:   main.cpp
 * Author: David Zuniga
 * Created on April 30, 2025
 * Purpose: Version 5
 */

 /*TODO 
 Implement admin status, writing to specific 
 files/reading from specific files, clean up code
 */

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include "Item.h"
#include "Store.h"
#include "Record.h"

using namespace std;

/*
 * 
 */
void getUserInfo(User &, string);
bool searchFor(User &, string, string);
void menu(int, Store &, Record &);
void adminMenu(int, Store &);
void checkout(int, Store &, Record &);
void receipt(int, Store &);

int main(int argc, char** argv) {
    
    //The user
    User user;

    //Name for binary file
    string fileName = "Records.bin";

    //Total items
    int numItems = 9;

    //Array of items
    Item *products = new Item[numItems];

    //Setting items' names, prices, and quantities
    for(int i = 0; i < numItems; i++)
    {
        products[i].setName("Item " + to_string(i + 1));
        products[i].setPrice(10.5 * (i+1));
        products[i].setQuantity(25);
    }

    //Puts list of items in store object
    Store selection(numItems, products);

    //Gets information from user
    getUserInfo(user, fileName);

    //Keeps a record of the user
    Record rec(fileName, user);

    //Main menu
    if(user.admin == true)
    {
        adminMenu(numItems, selection);
    }
    else
    {
        menu(numItems, selection, rec);
    }

     //Write and read to file
    // rec.writeToFile();
    rec.readFromFile();
    
    return 0;
}

void getUserInfo(User &user, string fileName)
{
    string admin = "ADMIN";
    //Gets username
    cout << "Enter username: ";
    cin.getline(user.name, nLetters);

    if(searchFor(user, fileName, user.name))
    {
        cout << "Found record.\n";
    }
    else if(user.name == admin)
    {
        user.admin = true;
        Record rec(fileName, user);
        rec.writeToFile();
    }
    else
    {
        //Gets user's address
        cout << endl;
        cout << "Enter Address: ";
        cin.getline(user.address, nLetters);

        //Gets user's email
        cout << endl;
        cout << "Enter Email: ";
        cin.getline(user.email, nLetters);

        //Gets user's phone number
        cout << endl;
        cout << "Enter Phone Number: ";
        cin.getline(user.phoneNum, nLetters);

        Record rec(fileName, user);
        rec.writeToFile();
    }
  
}

bool searchFor(User &user, string fileName, string str)
{
    //Creates binary file just incase one isn't created already
    ofstream out(fileName, ios::app | ios::binary);
    out.close();

    User temp;
    bool found = false;
    ifstream in(fileName, ios::in | ios::binary);

    //While not at end of file
    while(!in.eof())
    {
        in.read(reinterpret_cast<char *>(&temp), sizeof(temp));

        if(temp.name == str) //Found record in file
        {
            found = true;
            user = temp;
            break;
        }
    }
    in.close();

    return found;
}

void menu(int numItems, Store &selection, Record &rec)
{
    int choice;

    cout << "Welcome to our Store, " << rec.getUser().name << ". Would you like to buy anything?\n";
    do
    {
        cout << "Choose from our wild selection\n";
        for(int i = 0; i < numItems; i++)
        {
            cout << i + 1 << ". ";
            selection.printItem(i); // Item options
        }
        cout << numItems + 1 << ". " << "Checkout\n"; //Checkout option
        cout << numItems + 2 << ". " << "Quit\n";  //Quit option

        cin >> choice;
        if(choice >= 1 && choice <= numItems) //choice Within range
        {
            if(selection.isInCart(choice - 1)) //If item is already in cart
            {
                cout << selection.getItem(choice - 1).getName() << " is already in your cart.\n";
            }
            else //Otherwise add item to cart
            {
                selection.addToCart(choice - 1);
            }
        }
        else if(choice == numItems + 1) //Checkout option
        {
            checkout(numItems, selection, rec);
        }
        else if(choice == numItems + 2) //Quit option
        {
            cout << "Quitting.\n";
        }
        else //Error, choice is not valid
        {
            cout << "Error.\n";
        }
    }
    while(choice != numItems + 2); //While choice is not quit option
}
void adminMenu(int numItems, Store &selection)
{
    int choice;

    cout << "Welcome to our Store, Admin. Would you like to change anything?\n";
    do
    {
        cout << "1. Change price\n" << "2. Change Name\n" << "3.Change quantity\n" << "4. Quit\n";
        cin >> choice;

        if(choice >= 1 && choice <= 3)
        {
            for(int i = 0; i < numItems; i++)
            {
                cout << i + 1 << ". ";
                selection.printItem(i); // Item options
            }
            if(choice == 1)
            {
                int index;
                float change;
                cout << "Enter Item number: ";
                cin >> index;
                cout << "what would you like to change the price to? ";
                cin >> change;
                selection.getItem(index - 1).setPrice(change);
                selection.printItem(index - 1);
            }
            else if(choice == 2)
            {
                int index;
                string change;
                cout << "Enter Item number: ";
                cin >> index;
                cout << "what would you like to change the Name to? ";
                cin >> change;
                selection.getItem(index - 1).setName(change);
                selection.printItem(index - 1);
            }
            else if(choice == 3)
            {
                int index;
                int change;
                cout << "Enter Item number: ";
                cin >> index;
                cout << "what would you like to change the Quantity to? ";
                cin >> change;
                selection.getItem(index - 1).setQuantity(change);
                selection.printItem(index - 1);
            }
        }
        else if(choice == 4)
        {
            cout << "Quitting.\n";
        }
        else
        {
            cout << "Error\n";
        }
    }
    while(choice != 4); //While choice is not quit option
}

void checkout(int n, Store &s, Record &rec)
{
    bool confirm = false;
    char choice;
    float tot = 0;

    cout << "Shopping Cart\n";
    cout << "---------------\n";
    for(int i = 0; i < n; i++)
    {
        if(s.isInCart(i)) // Items that are in the cart
        {
            rec.updatePurchases(i);
            //Prints items that are in the cart
            cout << i + 1 << ". ";
            cout << s.getItem(i).getName() << setw(10) << "$" <<s.getItem(i).getPrice() << endl;
            //adds item price to total
            tot += s.getItem(i).getPrice();
        }
    }
    //Prints total amount due
    cout << "---------------\n";
    cout << "Total: " << "$" << tot << endl;
    rec.updateTotSpent(tot);
    //Prompts user to confirm their purchase
    while(!confirm)
    {
        cout << "Would You Like To Confirm your Purchase? y/n\n";
        cin >> choice;
        
        //Prints out a receipt
        if(choice == 'Y' || choice == 'y')
        {
            receipt(n, s);
            confirm = true;
        }
        //Goes back to main menu
        else if(choice == 'N' || choice == 'n')
        {
            cout << "Have a good day.\n";
            confirm = true;
        }
    }
}

void receipt(int n, Store &s)
{
    //Prints what items were bought
    for(int i = 0; i < n; i++)
    {
        s.buy(i);
    }
}