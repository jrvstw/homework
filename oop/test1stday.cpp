// 402125039 哲學四 葉家瑋
// this is the driver program for the function "get1stDayOfMonth"

#include <iostream>
using namespace std;

void get1stDayOfMonth(int year, int month, int &firstWeekday, int &numOfDays);

int main()
{
    int year,
        month;
    cin >> year >> month;

    int firstWeekday,
        numOfDays;
    get1stDayOfMonth(year, month, firstWeekday, numOfDays);
    cout << firstWeekday << "\n" << numOfDays << "\n";
    return 0;
}

void get1stDayOfMonth(int year, int month, int &firstWeekday, int &numOfDays)
{
    int daysOfMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int offset[13] = {0, 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    bool isLeapYear = ((year % 4) == 0);
    firstWeekday = (2 + (year - 1901) + (year - 1901) / 4
                    + offset[month] + (isLeapYear && month > 2)) % 7;
    numOfDays = (isLeapYear && month == 2)? 29: daysOfMonth[month];
    return;
}

