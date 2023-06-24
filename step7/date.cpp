#include<iostream>
#include <sstream>
#include<string>
#include <stdexcept>
#include "date.h"
#include "account.h"

Date::Date(int y,int m,int d): year(y),month(m),day(d){
    if (month>12) throw std::runtime_error( "月份非法！");
    if (day>getDaysInMonth(year,month)) throw std::runtime_error("天数非法！");
}


bool Date::operator < (const Date& date) const
{
        if (year < date.year)
        return true;
    else if (year == date.year && month < date.month)
        return true;
    else if (year == date.year && month == date.month && day < date.day)
        return true;
    else
        return false;
};

void Date::show(){

    std::cout<<Date::year<<"-"<<Date::month<<"-"<<Date::day;

};

Date Date::read(){
    
    std::string dateString;
    
    std::cin>>dateString;
    std::stringstream ss(dateString);
    char delimiter;
    int a,b,c,d,e,f;
    ss >> a>> delimiter >> b >> delimiter >> c>>delimiter>>d>>delimiter>>e>>delimiter>>f;


    return Date(a,b,c);

}

bool isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 != 0 || year % 400 == 0) {
            return true;
        }
    }
    return false;
}

// 获取某年某月的天数
int getDaysInMonth(int year, int month) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}


int getDaysDiff(Date date1,Date date2) {
    int y1,m1,d1,y2,m2,d2;
    y1 = date1.getYear(); m1 = date1.getMonth(); d1 = date1.getDay();y2 = date2.getYear(); m2 = date2.getMonth(); d2 = date2.getDay();
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (y1 > y2 || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2)) {
        std::swap(y1,y2);
        std::swap(m1,m2);
        std::swap(d1,d2);
    }
    int ans = 0;
    while (y1 < y2 || m1 < m2) {
        ans += daysInMonth[m1 - 1];
        if (m1 == 2 && y1 % 4 == 0 && (y1 % 100 != 0 || y1 % 400 == 0)) ans++;
        m1++;
        if (m1 > 12) {
            m1 = 1;
            y1++;
        }
    }
    return ans + d2 - d1;
}
