#ifndef account

#define account
#include "date.h"
#include<string>
using namespace std;
class SavingsAccount{

private:
    static double totalBalance;
    Date lastDate;
    double balance,rate,accumulation;
    string id;

public:
    
    SavingsAccount(Date date,string id,double rate);
    void show();
    void settle(Date date);
    void deposit(Date date,double amount,string note);
    void withdraw(Date date,double amount,string note);

    static double getTotal();

};



#endif