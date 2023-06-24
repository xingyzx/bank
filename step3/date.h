#ifndef date_h
#define date_h

class Date{

    public:
    
    int year,month,day;
    Date(int y =0,int m =0,int d=0);
    void formed();

};

//int Date(int y,int m,int d);
int getDaysDiff(Date date1,Date date2);
bool isLeapYear(int year);
int getDaysInMonth(int year, int month);

#endif