#ifndef account1

#define account1
#include "date.h"
#include<string>
#include<map>
using namespace std;



class AccountRecord ;


class Accumulater{

    private:

    double accumulation;
    Date lastDate;
    double temp;

    public:

    Accumulater(){};
    void change(Date date,double temp);
    void reset(Date date);

    void changeLastDate(Date date) {lastDate = date;}
    Date getLastDate() {return lastDate;}
    double getAccumulation() {return accumulation;}
}; 



class Account{
    private:
    string id;
    double balance = 0;
    static double totalBalance ;
    Accumulater acc;
    
    
    

    public:

    //Account (Date date,string id);

    //void record (Date date,double amount,string note);

    static std::multimap<Date, AccountRecord> recordMap;

    static double getTotal(){return totalBalance;};
    virtual void show(){};
    double getBalance(){return balance;};
    string getId()   {return id;};
    //void error();

    virtual void settle(Date date){};
    virtual void withdraw(Date date,double amount,string note){};
    virtual void deposit(Date date,double amount,string note){};
   
    
    
    void logId(string i) {id =i;}
    void addTotalBalance(double x){totalBalance+=x;}
    void addBalance(double x){balance+=x;}
    void record(Date date,double amount,string note);
    static void query(Date date1,Date date2);


};


class AccountRecord {
    private:

    Date date;
    Account& account;
    double amount,balance;
    string note;
    public:
    AccountRecord(Date date, Account account,double amount,double balance,string note);
    double getAmount(){return amount;};
    double getBalance(){return balance;};
    string getId()  {return account.getId();};
};


class SavingsAccount: virtual public Account{

    private:
    Accumulater acc;
    
    double rate;
    

    public:
    void changeLastDate(Date date) {acc.changeLastDate(date);}
    
    SavingsAccount(Date date,string id,double rate);
    double getRate() {return rate;};
    void show();

    void settle(Date date);
    void withdraw(Date date,double amount,string note);
    void deposit(Date date,double amount,string note);

    
};


class CreditAccount : virtual public Account{

    private:

    double credit,rate,fee;
    Accumulater acc;
    public:

    void changeLastDate(Date date) {acc.changeLastDate(date);}

    CreditAccount(Date date,string id,double credit,double rate,double fee);

    double getCredit(){return credit;};
    double getRate(){return rate;};
    double getFee(){return fee;};
    double getAvailableCredit(){return credit + getBalance();};
    
    void settle(Date date);
    void withdraw(Date date,double amount,string note);
    void deposit(Date date,double amount,string note);
    void chargeFee(Date date);
    void show();
};


#endif