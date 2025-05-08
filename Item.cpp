#include "Item.h"

Item::Item()
{
    price = 0;
    inCart = false;
    quantity = 0;
}

Item::Item(float p, int q, string i)
{
    price = p;
    quantity = q;
    itmName = i;
    inCart = false;
}

float Item::getPrice()
{
    return price;
}

void Item::setPrice(float p)
{
    price = p;
}

int Item::getQuantity()
{
    return quantity;
}

void Item::setQuantity(int q)
{
    quantity = q;
}

bool Item::isInCart()
{
    return inCart;
}
void Item::setCart(bool status)
{
    inCart = status;
}
string Item::getName()
{
    return itmName;
}
void Item::setName(string i)
{
    itmName = i;
}
void Item::print()
{
    cout << itmName << " ($" << price << ") Qty: " << quantity << endl;
            
}

Item Item::operator=(Item &right)
{
    price = right.price;
    quantity = right.quantity;
    inCart = right.inCart;
    itmName = right.itmName;

    return *this;
}
