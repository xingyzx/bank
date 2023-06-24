
#include<iostream>
#include<cmath>
#include "account.h"
#include "date.h"
using namespace std;


double SavingsAccount::totalBalance = 0.0;

SavingsAccount::SavingsAccount(Date date,std::string id,double rate) : lastDate(date),id(id),rate(rate) {
    date.formed();
    cout<<'\t'<<"#"<<id<<" created"<<endl;
}

void SavingsAccount::show(){
    cout<<id<<'\t'<<"Balance: "<<balance;
}

void SavingsAccount::deposit(Date date,double amount,string note) {

    amount = floor(amount * 100 + 0.5) / 100;
    accumulation += getDaysDiff(lastDate.year,lastDate.month,lastDate.day,date.year,date.month,date.day)*balance;
    lastDate = date;

    balance+=amount;
    date.formed();
    cout<<'\t'<<"#"<<id<<'\t'<<amount<<'\t'<<balance<<'\t'<<note<<endl;
    SavingsAccount::totalBalance+=amount;
}

void SavingsAccount::settle(Date date){


    accumulation += getDaysDiff(lastDate.year,lastDate.month,lastDate.day,date.year,date.month,date.day)*this->balance;
    lastDate = date;
    balance += floor(((accumulation/366)*rate) * 100 + 0.5) / 100;   
    date.formed();  
    cout<<'\t'<<"#"<<id<<'\t'<<floor(((accumulation/366)*rate) * 100 + 0.5) / 100<<'\t'<<balance<<'\t'<<"interest"<<endl;
    SavingsAccount::totalBalance+=floor(((accumulation/366)*rate) * 100 + 0.5) / 100;   

    }

void SavingsAccount::withdraw(Date date,double amount,string note){

    amount = floor(amount * 100 + 0.5) / 100;
        
    accumulation += getDaysDiff(lastDate.year,lastDate.month,lastDate.day,date.year,date.month,date.day)*this->balance;
    lastDate = date;
    balance-=amount;
    lastDate.formed();
    cout<<'\t'<<"#"<<id<<'\t'<<"-"<<amount<<'\t'<<balance<<'\t'<<note<<endl;
    SavingsAccount::totalBalance-=amount;
}


double SavingsAccount::getTotal(){
    return SavingsAccount::totalBalance;
}