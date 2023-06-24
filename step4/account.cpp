
#include<iostream>
#include<cmath>
#include "account.h"
#include "date.h"
using namespace std;

double Account::totalBalance = 0;


void Accumulater::change(Date date,double temp){
    accumulation+=temp;
    changeLastDate(date);
}


void Accumulater::reset(Date date){
    accumulation=0;
    changeLastDate(date);
}

/*
Account::Account(Date date,string id): id(id){
    acc.changeLastDate(date);
}
*/



SavingsAccount::SavingsAccount(Date date,std::string id,double rate) : rate(rate) {
    changeLastDate(date);
    logId(id);
    date.show();
    cout<<'\t'<<"#"<<id<<" created"<<endl;
}

void SavingsAccount::show(){
    cout<<getId()<<'\t'<<"Balance: "<<getBalance();
}

void SavingsAccount::deposit(Date date,double amount,string note) {

    amount = floor(amount * 100 + 0.5) / 100;
    acc.change(date,(getDaysDiff(acc.getLastDate(),date))*getBalance());
    //accumulation += getDaysDiff(lastDate.year,lastDate.month,lastDate.day,date.year,date.month,date.day)*balance;
    //lastDate = date;

    addBalance(amount);
    date.show();
    cout<<'\t'<<"#"<<getId()<<'\t'<<amount<<'\t'<<getBalance()<<'\t'<<note<<endl;
    addTotalBalance(amount);
}

void SavingsAccount::settle(Date date){

    bool newYear = 0;
    if(acc.getLastDate().year!=date.year){newYear = 1;}

    if (newYear) {
    acc.change(date,(getDaysDiff(acc.getLastDate(),date))*getBalance());

    //accumulation += getDaysDiff(lastDate.year,lastDate.month,lastDate.day,date.year,date.month,date.day)*this->balance;
    //lastDate = date;
    addBalance(floor(((acc.getAccumulation()/366)*rate) * 100 + 0.5) / 100);   
    date.show();  
    cout<<'\t'<<"#"<<getId()<<'\t'<<floor(((acc.getAccumulation()/366)*rate) * 100 + 0.5) / 100<<'\t'<<getBalance()<<'\t'<<"interest"<<endl;
    addTotalBalance(floor(((acc.getAccumulation()/366)*rate) * 100 + 0.5) / 100);   
    }
}

void SavingsAccount::withdraw(Date date,double amount,string note){

    amount = floor(amount * 100 + 0.5) / 100;
    acc.change(date,(getDaysDiff(acc.getLastDate(),date))*getBalance());

    //accumulation += getDaysDiff(lastDate.year,lastDate.month,lastDate.day,date.year,date.month,date.day)*this->balance;
    //lastDate = date;
    addBalance(-amount);
    acc.getLastDate().show();
    cout<<'\t'<<"#"<<getId()<<'\t'<<"-"<<amount<<'\t'<<getBalance()<<'\t'<<note<<endl;
    addTotalBalance(-amount);
}


CreditAccount::CreditAccount(Date date,string id,double credit,double rate,double fee): credit(credit),rate(rate),fee(fee){
    changeLastDate(date);
    logId(id);
    date.show();
    cout<<'\t'<<"#"<<id<<" created"<<endl;
}


void CreditAccount::deposit(Date date,double amount,string note) {

    amount = floor(amount * 100 + 0.5) / 100;
    acc.change(date,(getDaysDiff(acc.getLastDate(),date))*getBalance());
    //accumulation += getDaysDiff(lastDate.year,lastDate.month,lastDate.day,date.year,date.month,date.day)*balance;
    //lastDate = date;

    addBalance(amount);
    date.show();
    cout<<'\t'<<"#"<<getId()<<'\t'<<amount<<'\t'<<getBalance()<<'\t'<<note<<endl;
    addTotalBalance(amount);
}


void CreditAccount::withdraw(Date date,double amount,string note){

    amount = floor(amount * 100 + 0.5) / 100;
    acc.change(date,(getDaysDiff(acc.getLastDate(),date))*getBalance());

    //accumulation += getDaysDiff(lastDate.year,lastDate.month,lastDate.day,date.year,date.month,date.day)*this->balance;
    //lastDate = date;
    addBalance(-amount);
    acc.getLastDate().show();
    cout<<'\t'<<"#"<<getId()<<'\t'<<"-"<<amount<<'\t'<<getBalance()<<'\t'<<note<<endl;
    addTotalBalance(-amount);
}

void CreditAccount::settle(Date date){

    bool newYear = 0;
    if(acc.getLastDate().year!=date.year){newYear = 1;}
   

    acc.change(date,(getDaysDiff(acc.getLastDate(),date))*getBalance());

    //accumulation += getDaysDiff(lastDate.year,lastDate.month,lastDate.day,date.year,date.month,date.day)*this->balance;
    //lastDate = date;
    addBalance(floor(((acc.getAccumulation())*rate) * 100 + 0.5) / 100);   
      
    if((floor(((acc.getAccumulation())*rate) * 100 + 0.5) / 100)!=0){
        date.show();
        cout<<'\t'<<"#"<<getId()<<'\t'<<(floor(((acc.getAccumulation())*rate) * 100 + 0.5) / 100)<<'\t'<<getBalance()<<'\t'<<"interest"<<endl;
    }
    
    addTotalBalance(floor(((acc.getAccumulation())*rate) * 100 + 0.5) / 100); 

    acc.reset(date);

    if(newYear) chargeFee(date);
    
    
}

void CreditAccount::show(){
    cout<<getId()<<'\t'<<"Balance: "<<getBalance()<<'\t'<<"Available credit: "<<getAvailableCredit();
}

void CreditAccount::chargeFee(Date date){
    withdraw(date,50,"annual fee");
}