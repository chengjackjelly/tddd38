#ifndef TIME_H
#define TIME_H
#include <string>
#include <iostream>
using std::string;
class Time
{
public:
    Time();
    Time(int hour, int minute, int second);
    bool is_valid();
    string to_string(bool is_printed_in_24) const;
    bool is_am();
    Time operator+(int seconds);
    bool operator==(const Time &other) const;

private:
    int hour;
    int minute;
    int second;
};
std::ostream &operator<<(std::ostream &out, const Time &f);
#endif