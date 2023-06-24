//step5.cpp

#include "account.h"
#include "global.h"

#include <iostream>

#include <vector>

#include <algorithm>

#include<fstream>

#include <sstream>

using namespace std;


bool debug =0;

bool inputMod = 0;




int main() {

    Date date(2008, 11, 1);//起始日期

    vector<Account *> accounts;//创建账户数组，元素个数为0

    string line;

    ifstream command_txt("commands.txt");

    char cmd;

    while(getline(command_txt,line)){

        if(!line.empty()){

        stringstream ss(line);

        //显示日期和总金额

        if(debug) date.show();

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

                    account = new SavingsAccount(date, id, rate);

                }else {

                    ss >> credit >> rate >> fee;

                    account = new CreditAccount(date, id, credit, rate, fee);

                }

                accounts.push_back(account);

            break;

            case 'd'://存入现金

                ss >> index >> amount;

                getline(ss, desc);

                accounts[index]->deposit(date, amount, desc);

            break;

            case 'w'://取出现金

                ss >> index >> amount;

                getline(ss, desc);

                try{
                    accounts[index]->withdraw(date, amount, desc);
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

                if (day < date.getDay())

                    std::cout << "You cannot specify a previous day";

                    else if (day > date.getMaxDay())

                    std::cout << "Invalid day";

                else

                    date = Date(date.getYear(), date.getMonth(), day);

            break;

            case 'n'://进入下个月

                if (date.getMonth() == 12)

                    date = Date(date.getYear() + 1, 1, 1);

                else

                    date = Date(date.getYear(), date.getMonth() + 1, 1);

                for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)

                    (*iter)->settle(date);

            break;

            case 'q'://查询一段时间内的账目

                try{

                date1 = Date::read();

                date2 = Date::read();
                }catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                    break;
                }

                Account::query(date1, date2);

            break;

        }

        }

    }
    command_txt.close();
    std::cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;

    inputMod = 1;

    do {

        //显示日期和总金额

        date.show();

        std::cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";

        getline(std::cin,line);

        std::ofstream file("commands.txt", std::ios_base::app);  //以追加模式打开
    
        if (file.is_open()) {  // 检查文件是否成功打开
            file << line<<endl;;  // 将内容写入文件
        
            file.close();  // 关闭文件
            if(debug) std::cout << "写入文件成功" << std::endl;
        } else {
            if(debug) std::cout << "无法打开文件" << std::endl;
        }

        stringstream command(line);

        char type;

        int index, day;

        double amount, credit, rate, fee;

        string id, desc;

        Account* account;

        Date date1, date2;



        command >> cmd;

        switch (cmd) {

            case 'a'://增加账户

                command >> type >> id;

                if (type == 's') {

                    command >> rate;

                    account = new SavingsAccount(date, id, rate);

                }else {

                    command >> credit >> rate >> fee;

                    account = new CreditAccount(date, id, credit, rate, fee);

                }

                accounts.push_back(account);

            break;

            case 'd'://存入现金

                command >> index >> amount;

                command>>desc;

                accounts[index]->deposit(date, amount, desc);

            break;

            case 'w'://取出现金

                command >> index >> amount;

                command>>desc;


                try{
                    accounts[index]->withdraw(date, amount, desc);
                }catch(accountException e){
                    cout<<e.what()<<"\t账户: "<<e.getErrorAccount().getId();
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

                command >> day;

                if (day < date.getDay())

                    std::cout << "You cannot specify a previous day";

                    else if (day > date.getMaxDay())

                    std::cout << "Invalid day";

                else

                    date = Date(date.getYear(), date.getMonth(), day);

            break;

            case 'n'://进入下个月

                if (date.getMonth() == 12)

                    date = Date(date.getYear() + 1, 1, 1);

                else

                    date = Date(date.getYear(), date.getMonth() + 1, 1);

                for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)

                    (*iter)->settle(date);

            break;

            case 'q'://查询一段时间内的账目

                try{

                date1 = Date::read();

                date2 = Date::read();
                }catch (const std::exception& e) {
                    std::cout << e.what() << std::endl;
                    break;
                }

                Account::query(date1, date2);

            break;

        }

    } while (cmd != 'e');






    return 0;

}

