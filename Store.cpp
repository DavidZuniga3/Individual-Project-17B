#include "Store.h"


Store::Store()
{
    nItems = 0;
}
Store::Store(int n)
{
    nItems = n;
    catalog = new Item[nItems];
}
Store::Store(int n, Item *i)
{
    nItems = n;
    catalog = new Item[nItems];
    setItems(i);
}
void Store::setItems(Item *items)
{
    for(int i = 0; i < nItems; i++)
    {
        catalog[i] = items[i];
    }
}
void Store::addToCart(int i)
{
    catalog[i].setCart(true);
    cout << catalog[i].getName() << " added to cart.\n";

}
void Store::removeFromCart(int i)
{
    catalog[i].setCart(false);
    cout << catalog[i].getName() << " Removed from cart.\n";
}
void Store::buy(int i)
{
    int quant = catalog[i].getQuantity();
    if(catalog[i].isInCart())
    {
        quant--;
        catalog[i].setCart(false);
        cout << catalog[i].getName() << " has been bought for " << "$" << catalog[i].getPrice() << ".\n";
        catalog[i].setQuantity(quant);
    }
}
bool Store::isInCart(int i)
{
    return catalog[i].isInCart();
}
void Store::printItem(int i)
{
    catalog[i].print();
}
Item &Store::getItem(int i)
{
    return catalog[i];
}
Item * Store:: getList()
{
    return catalog;
}

Store::~Store()
{
    delete [] catalog;
}