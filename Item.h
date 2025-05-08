/* 
 * File:   Item.h
 * Author: David Zuniga
 *
 * Created on April 7, 2025
 */

#include <iostream>
using namespace std;

#ifndef ITEM_H
#define ITEM_H

class Item
{
    private:
        float price;
        int quantity;
        bool inCart;
        string itmName;
    public:
        Item();
        Item(float, int, string);
        float getPrice();
        void setPrice(float);
        int getQuantity();
        void setQuantity(int);
        bool isInCart();
        void setCart(bool);
        string getName();
        void setName(string);
        void print();
        Item operator=(Item &);
};

#endif /* ITEM_H */

