#include "../include/Timex.h"
#include <iostream>

Time::Time() : hour(0), minute(0), second(0) {}

Time::Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second) {}

bool Time::is_valid()
{
    return ((this->hour >= 0 && this->hour <= 23) && (this->minute >= 0 && this->minute <= 59) && (this->second >= 0 && this->second <= 59));
}
Time Time::operator+(int seconds)
{
    int new_hour = this->hour + seconds / 3600;
    seconds = seconds % 3600;
    int new_minute = this->minute + seconds / 60;
    seconds = seconds % 60;
    int new_second = this->second + seconds;

    new_minute += new_second / 60;
    new_second = new_second % 60;
    new_hour += new_minute / 60;
    new_minute = new_minute % 60;
    new_hour = new_hour % 24;
    Time result{new_hour, new_minute, new_second};
    return result;
}
bool Time::operator==(const Time &other) const
{
    return other.hour == this->hour && other.minute == this->minute && other.second == this->second;
}
std::ostream &operator<<(std::ostream &out, const Time &t)
{
    return out << t.to_string(true);
}
string Time::to_string(bool is_printed_in_24) const
{
    string result;
    if (is_printed_in_24)
    {

        result = std::to_string(this->hour) + ":" + std::to_string(this->minute) + ":" + std::to_string(this->second);
        return result;
    }
    return result;
}