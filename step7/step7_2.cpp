#include "global.h"
#include "account.h"
#include "interact.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include<fstream>
#include <sstream>

using namespace std;

bool debug =0;
bool inputMod = 0;
vector<Account *> accounts;
vector<User> users;
int accountCounter = accounts.size();

Date globalDate;

int main() {

    globalDate = Date(2008, 11, 1);//起始日期
    string line;
    ifstream command_txt("commands.txt");
    char cmd;

    while(getline(command_txt,line)){

        if(!line.empty()){

        stringstream ss(line);

        //显示日期和总金额

        if(debug) globalDate.show();

        if(debug) std::cout << "\tTotal: " << Account::getTotal() << "\tcommand> "<<endl;



        char type;

        int index, day;

        double amount, credit, rate, fee;

        string id, desc;

        Account* account;

        Date date1, date2;



        ss >> cmd;

        switch (cmd) {

            case 'a'://增加账户

                ss >> type >> id;

                if (type == 's') {

                    ss >> rate;

                    account = new SavingsAccount(globalDate, id, rate);

                }else {

                    ss >> credit >> rate >> fee;

                    account = new CreditAccount(globalDate, id, credit, rate, fee);

                }

                accounts.push_back(account);

            break;

            case 'd'://存入现金

                ss >> index >> amount;

                getline(ss, desc);

                accounts[index]->deposit(globalDate, amount, desc);

            break;

            case 'w'://取出现金

                ss >> index >> amount;

                getline(ss, desc);

                try{
                    accounts[index]->withdraw(globalDate, amount, desc);
                }catch(accountException e){
                    cout<<e.what()<<"\t账户: "<<e.getErrorAccount().getId()<<endl;
                };

                

            break;

            case 's'://查询各账户信息

                for (size_t i = 0; i < accounts.size(); i++) {

                    std::cout << "[" << i << "] ";

                    accounts[i]->show();

                    std::cout << endl;

                }

            break;

            case 'c'://改变日期

                ss >> day;

                if (day < globalDate.getDay())

                    std::cout << "You cannot specify a previous day";

                    else if (day > globalDate.getMaxDay())

                    std::cout << "Invalid day";

                else

                    globalDate = Date(globalDate.getYear(), globalDate.getMonth(), day);

            break;

            case 'n'://进入下个月

                if (globalDate.getMonth() == 12)

                    globalDate = Date(globalDate.getYear() + 1, 1, 1);

                else

                    globalDate = Date(globalDate.getYear(), globalDate.getMonth() + 1, 1);

                for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)

                    (*iter)->settle(globalDate);

            break;

            case 'u'://创建用户
                string n;
                ss>>n;
                _register(0,n);
            

        }

        }

    }
    
    command_txt.close();
    inputMod = 1;


    bool wantExit = 0;

    

    system("clear");

    User *usingUser;
    int _cmd = 0;

    while (cmd=_init()){
        cin>>_cmd;
        if(_cmd==1){//login
            cout<<"请输入账号: ";
            string inputString;
            cin>>inputString;
            bool found = 0;
            for(int i = 0;i<users.size();i++){
                if(users[i].getName()==inputString) usingUser=&users[i];
                found = 1;
            }
            if(found) {
                userInterface(usingUser);
            }else{
                cout<<"未找到该用户"<<endl;
            }


        }
    
        if(_cmd==2){//reg
            _register(1);
        }
        if(_cmd==0) break;


    }


}
