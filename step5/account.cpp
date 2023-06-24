
#include<iostream>
#include<cmath>
#include <map>
#include "account.h"
#include "date.h"
using namespace std;

double Account::totalBalance = 0;
std::multimap<Date, AccountRecord> Account::recordMap;


AccountRecord::AccountRecord(Date date, Account account,double amount,double balance,string note):date(date), account(account),amount(amount),balance(balance),note(note) {}



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

void Account::record(Date date,double amount,string note){

    recordMap.insert(std::make_pair(date,AccountRecord(date,*this,amount,getBalance(),note)));

}

void Account::query(Date date1,Date date2){
    if(date1<date2){

        for (auto it = recordMap.begin(); it != recordMap.end(); ++it) {
            Date datetmp= it->first;
            if(date1<datetmp&&datetmp<date2){

                
                AccountRecord ar = it->second;

                datetmp.show();
                cout<<'\t'<<ar.getId()<<'\t'<<ar.getAmount()<<'\t'<<ar.getBalance()<<endl;
                

            }

        }


    }else{
        cout<<"非法数值"<<endl;
    }

}

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

    record(date,amount,note);

}

void SavingsAccount::settle(Date date){

    bool newYear = 0;
    if(acc.getLastDate().getYear()!=date.getYear()){newYear = 1;}

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

    record(date,amount,note);

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

    record(date,amount,note);

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

    record(date,amount,note);

}

void CreditAccount::settle(Date date){

    bool newYear = 0;
    if(acc.getLastDate().getYear()!=date.getYear()){newYear = 1;}
   

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