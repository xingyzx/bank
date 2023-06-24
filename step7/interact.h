#ifndef interact_h

#define interact_h


int _init(); //初始化
User __login();
void _register(bool input,string inputuserName="");
void addAccount(User *user);

void userInterface(User *user);
void loginCallOut(User *user);
void usingDeposit(User *user);
void usingWithdraw(User *user);





#endif