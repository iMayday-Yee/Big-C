#ifndef TIME_H
#define TIME_H
#include<QDebug>

class Time
{
public:
    int hour;
    int minute;
    Time(int h,int m);
    Time();
    friend QDebug operator<<(QDebug debug, const Time &t);
    Time operator-(const Time &t);
    Time operator+(const Time &t);
    bool operator>(const Time &t);
    bool operator>=(const Time &t);
    bool operator<(const Time &t);
    bool operator<=(const Time &t);
    bool operator==(const Time &t);
    int getDeltaTime();
};

#endif // TIME_H
