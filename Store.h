#ifndef STORE_H
#define STORE_H
#include "Item.h"

class Store
{
    private:
    Item *catalog;
    int nItems;

    public:
    Store();
    Store(int);
    Store(int, Item *);
    void setItems(Item *);
    void addToCart(int);
    void removeFromCart(int);
    void buy(int);
    bool isInCart(int);
    void printItem(int);
    Item &getItem(int);
    Item * getList();
    ~Store();
};

#endif /* STORE_H */
