#ifndef date_h
#define date_h

class Date{

    public:
    
    int year,month,day;
    Date(int y,int m,int d);
    void formed();

};

//int Date(int y,int m,int d);
int getDaysDiff(int startYear, int startMonth, int startDay, int endYear, int endMonth, int endDay);


#endif