
#include<iostream>
#include<cmath>
#include "account.h"
using namespace std;




    SavingsAccount::SavingsAccount(int date,int id,double rate) : lastDate(date),id(id),rate(rate) {
        cout<<lastDate<<'\t'<<"#"<<id<<" is created"<<endl;
    }

    void SavingsAccount::show(){
        cout<<"#"<<id<<'\t'<<"Balance: "<<balance;
    }

    void SavingsAccount::deposit(int date,double amount) {
        
        amount = floor(amount * 100 + 0.5) / 100;
        accumulation += (date-lastDate)*balance;
        lastDate = date;
        
        balance+=amount;
        cout<<lastDate<<'\t'<<"#"<<id<<'\t'<<amount<<'\t'<<balance<<endl;
        
    }

    void SavingsAccount::settle(int date){

        
        accumulation += (date - lastDate)*balance;
        lastDate = date;
        balance += floor(((accumulation/365)*rate) * 100 + 0.5) / 100;     
        cout<<date<<'\t'<<"#"<<id<<'\t'<<floor(((accumulation/365)*rate) * 100 + 0.5) / 100<<'\t'<<balance<<endl;
        //accumulation = 0;

    }

    void SavingsAccount::withdraw(int date,double amount){

        amount = floor(amount * 100 + 0.5) / 100;
        
        accumulation += (date-lastDate)*balance;
        lastDate = date;
        balance-=amount;
        cout<<lastDate<<'\t'<<"#"<<id<<'\t'<<"-"<<amount<<'\t'<<balance<<endl;
    }

;

