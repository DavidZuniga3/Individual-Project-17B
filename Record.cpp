#include "Record.h"

Record::Record()
{

}
Record::Record(string f, User u)
{
    fileName = f;
    setUser(u);
}
void Record::setUser(User u)
{
    //sets name
    for(int i = 0; u.name[i] != '\0'; i++)
    {
        info.name[i] = u.name[i];
    }
    info.name[strlen(u.name)] = '\0';

    //sets address
    for(int i = 0; u.address[i] != '\0'; i++)
    {
        info.address[i] = u.address[i];
    }
    info.address[strlen(u.address)] = '\0';

    //sets email
    for(int i = 0; u.email[i] != '\0'; i++)
    {
        info.email[i] = u.email[i];
    }
    info.email[strlen(u.email)] = '\0';

    //sets phone number
    for(int i = 0; u.phoneNum[i] != '\0'; i++)
    {
        info.phoneNum[i] = u.phoneNum[i];
    }
    info.phoneNum[strlen(u.phoneNum)] = '\0';

    info.admin = u.admin;
    //sets purchases and total spent
    info.purchases = u.purchases;
    info.totSpent = u.totSpent;
}

void Record::setFileName(string f)
{
    fileName = f;
}

void Record::writeToFile()
{
    ofstream out(fileName, ios::app | ios::binary);

    out.write(reinterpret_cast<char *>(&info), sizeof(info));

    out.close();
}
void Record::readFromFile()
{
    User temp;
    ifstream in(fileName, ios::in | ios::binary);

    if(!in)
    {
        cout << "Error opening file.\n";
        return;
    }

    in.read(reinterpret_cast<char *>(&temp), sizeof(temp));

    while(!in.eof())
    {
        cout << "Name: " << temp.name << endl;
        cout << "Address: " << temp.address << endl;
        cout << "Email: " << temp.email << endl;
        cout << "Phone Number: " << temp.phoneNum << endl;
        cout << "Admin Status: " << temp.admin << endl;
        cout << "Purchases: " << temp.purchases << endl;
        cout << "Total Spent: " << temp.totSpent << endl;
        cout << endl;

        in.read(reinterpret_cast<char *>(&temp), sizeof(temp));
    }

    in.close();
}

bool Record::searchFor(string str)
{
    User temp;
    bool found = false;
    ifstream in(fileName, ios::in | ios::binary);

    //While not at end of file
    while(!in)
    {
        in.read(reinterpret_cast<char *>(&temp), sizeof(temp));

        if(temp.name == str) //Found record in file
        {
            found = true;
            setUser(temp);
            break;
        }
    }
    in.close();

    return found;
}

void Record::updatePurchases(int p)
{
    info.purchases += p;
}
void Record::updateTotSpent(int t)
{
    info.totSpent += t;
}