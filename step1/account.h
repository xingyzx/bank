#ifndef account

#define account

class SavingsAccount{

private:
    int id,lastDate;
    double balance,rate,accumulation;

public:
    SavingsAccount(int date,int id,double rate);
    void show();
    void settle(int date);
    void deposit(int date,double amount);
    void withdraw(int date,double amount);

};



#endif