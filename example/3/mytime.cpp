#include "mytime.h"

Time::Time(int hour,int minute):hour(hour),minute(minute){}
Time::Time():hour(0),minute(0){}
Time Time::operator-(const Time &t)
{
    int h = this->hour - t.hour;
    int m = this->minute - t.minute;
    if(m < 0)
    {
        m = 60+m;
        h--;
    }
    return Time(h,m);
}
Time Time::operator+(const Time &t)
{
    int h = this->hour + t.hour;
    int m = this->minute +t.minute;
    if(m >= 60)
    {
        m -= 60;
        h++;
    }
    return Time(h,m);
}
bool Time::operator>(const Time &t)
{
    return (*this -t).getDeltaTime() > 0;
}
bool Time::operator>=(const Time &t)
{
    return (*this -t).getDeltaTime() >= 0;
}
bool Time::operator<(const Time &t)
{
    return (*this -t).getDeltaTime() <= 0;
}
bool Time::operator<=(const Time &t)
{
    return (*this -t).getDeltaTime() <= 0;
}
bool Time::operator==(const Time &t)
{
    return (*this -t).getDeltaTime() == 0;
}
int Time::getDeltaTime()
{
    return this->hour*60 + this->minute;
}
QDebug operator<<(QDebug debug, const Time &t)
{
debug<<"Time "<<t.hour<<":"<<t.minute;
return debug;
}

