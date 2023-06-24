#ifndef date_h
#define date_h

int getDaysInMonth(int year, int month);

class Date{

    public:
    
    int year,month,day;
    Date(int y =0,int m =0,int d=0);
    void show();
    int getDay(){return day;};
    int getMonth(){return month;};
    int getYear(){return year;};
    int getMaxDay(){return getDaysInMonth(year,month);};

};

//int Date(int y,int m,int d);
int getDaysDiff(Date date1,Date date2);
bool isLeapYear(int year);

#endif