#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include "User.h"

using namespace std;

class Record
{
    private:
        User info;
        string fileName;
    public:
        Record();
        Record(string, User);
        void updatePurchases(int);
        void updateTotSpent(int);
        void setFileName(string);
        void setUser(User);
        string getFileName(){return fileName;}
        void writeToFile();
        void readFromFile();
        bool searchFor(string);
        User getUser(){return info;}
};

#endif /* RECORD_H */
