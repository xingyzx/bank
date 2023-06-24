
#include<iostream>

#include "global.h"
#include "account.h"
#include <fstream>
#include <map>

using namespace std;

int _init(){
    
    
    cout<<"银行"<<endl;
    cout<<"请输入序号"<<endl;
    cout<<"1. 登陆"<<endl;
    cout<<"2. 注册"<<endl;

    
    

    return 1 ;

}

void _register(bool input,string inputUserName=""){
    if(input){
        cout<<"请输入账号名称：";
        
        cin>>inputUserName;
    }
    users.push_back(User(inputUserName));
    if(inputMod) {cout<<"注册成功"<<endl;

     std::ofstream file("commands.txt", std::ios_base::app);  //以追加模式打开
    
        if (file.is_open()) {  // 检查文件是否成功打开
            file << "u "<<inputUserName<<endl;
        
            file.close();  // 关闭文件
            if(debug) std::cout << "写入文件成功" << std::endl;
        } else {
            if(debug) std::cout << "无法打开文件" << std::endl;
        }
    }
}

void addAccount(User *user){
    
    accountCounter=accounts.size()+1;
    cout<<"注册账户类型："<<endl;
    cout<<"1. 信用类"<<endl;
    cout<<"2. 借记类"<<endl;

    int cmd;
    std::cin>>cmd;
    
    if(cmd == 1) {  //credit
        int availableCredit;
        cout<<"请输入额度: ";
        std::cin>>availableCredit;
        CreditAccount* account = new CreditAccount(globalDate,"C"+user->getName()+to_string(accountCounter) ,availableCredit,0.0007,120);
        accounts.push_back(account);
        cout<<"该账户月利率为0.0007, 年费为120"<<endl;

        std::ofstream file("commands.txt", std::ios_base::app);  //以追加模式打开
    
        if (file.is_open()) {  // 检查文件是否成功打开
            file << "a c "<<"C"+user->getName()+to_string(accountCounter)<<" "<<availableCredit<<" 0.0007 120"<<endl;;  // 将内容写入文件
        
            file.close();  // 关闭文件
            if(debug) std::cout << "写入文件成功" << std::endl;
        } else {
            if(debug) std::cout << "无法打开文件" << std::endl;
        }
        
    }
    if(cmd == 2) {
        SavingsAccount* account_ = new SavingsAccount(globalDate,"S"+user->getName()+to_string(accountCounter),0.0020);
        accounts.push_back(account_);
        std::cout<<"该账户年利率为0.0020"<<endl;

        std::ofstream file("commands.txt", std::ios_base::app);  //以追加模式打开
    
        if (file.is_open()) {  // 检查文件是否成功打开
            file << "a s "<<"S"+user->getName()+to_string(accountCounter)<<" "<<" 0.0020"<<endl;;  // 将内容写入文件
        
            file.close();  // 关闭文件
            if(debug) std::cout << "写入文件成功" << std::endl;
        } else {
            if(debug) std::cout << "无法打开文件" << std::endl;
        }
        
    }



}



User __login(){

    cout<<"请输入账号：";
    string inputString;
    std::cin>>inputString;
    bool isfound = 0;

    if(users.size()==0) return User("NOUSER");

    for(int i = 0;i<users.size();i++){
        if(inputString==users[i].getName()) {
            isfound = 1;
            return users[i];
        }
        if(!isfound) return User("null");
    }

    

    

}

void loginCallOut(User *user){

    double needToPay = 0;
    for(int i = 0; i<accounts.size();i++){
        if(accounts[i]->getId().substr(1,user->getName().length())==user->getName()){
            needToPay+=accounts[i]->getBalance();
        }
    }

    cout<<"需还款："<<needToPay<<endl;

}


void usingDeposit(User *user){
    multimap<int,Account*> countAccount;
    cout<<"使用哪个账户？"<<endl;
    int count = 0;
    for(int i = 0;i<accounts.size();i++){
        if(accounts[i]->getId().substr(1,user->getName().length())==user->getName()){
            cout<<++count<<'\t'<<accounts[i]->getId()<<'\t'<<accounts[i]->getBalance()<<endl;
            countAccount.insert(std::make_pair(count,accounts[i]));
        }
    }
    if(count == 0) {cout<<"无账户，请添加"<<endl;}
    int a = 0;
    cin>>a;
    for (auto it = countAccount.begin(); it != countAccount.end(); ++it) {
        if( it->first== a) {
            int amount;
            cout<<"请输入金额：";
            cin>>amount;
            string note;
            cout<<"请输入备注：";
            cin>>note;
            it->second->deposit(globalDate,amount,note);
    }
    }
}

void usingWithdraw(User *user){
    multimap<int,Account*> countAccount;
    cout<<"使用哪个账户？"<<endl;
    int count = 0;
    for(int i = 0;i<accounts.size();i++){
        if(accounts[i]->getId().substr(1,user->getName().length())==user->getName()){
            cout<<++count<<'\t'<<accounts[i]->getId()<<'\t'<<accounts[i]->getBalance()<<endl;
            countAccount.insert(std::make_pair(count,accounts[i]));
        }
    }
    if(count == 0) {cout<<"无账户，请添加"<<endl;}
    int a = 0;
    cin>>a;
    for (auto it = countAccount.begin(); it != countAccount.end(); ++it) {
        if( it->first== a) {
            int amount;
            cout<<"请输入金额：";
            cin>>amount;
            string note;
            cout<<"请输入备注：";
            cin>>note;
            it->second->withdraw(globalDate,amount,note);
    }
    }
}


void userInterface(User *user){

    loginCallOut(user);

    cout<<"1. 添加账户"<<endl
    <<"2. 存钱"<<endl
    <<"3. 取钱"<<endl
    <<"0. 返回"<<endl
    <<"请输入序号：";

    int a = 0;
    cin>>a;

    switch(a){
        case 0: break;
        case 1:addAccount(user);break;
        case 2:usingDeposit(user);break;
        case 3:usingWithdraw(user);break;


    }
    

};

