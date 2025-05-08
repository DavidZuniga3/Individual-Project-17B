const int nLetters = 50;

struct User
{
    char name[nLetters];
    char address[nLetters];
    char email[nLetters];
    char phoneNum[nLetters];
    bool admin = false;
    int purchases = 0;
    int totSpent = 0;
};

