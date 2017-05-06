// 402125039 哲學四 葉家瑋

#include <iostream>
#include <iomanip>
using namespace std;

bool inputYrMn(int &year, int &month);
/* Precondition: both year and month are integers
 * Postcondition: function returns true if and only if 1901 <= year <= 2099
 * and 1 <= month <= 12.
 */
void get1stDayOfMonth(int year, int month, int &firstWeekday, int &numOfDays);
/* Precondition: year is an integer between 1901 and 2099. month is an integer
 * between 1 and 12.
 * Postcondition: firstWeekday is the weekday of the first day of given month
 * in given year. numOfDays is the number of days of given month in given year.
 */
void showCalendar(int year, int month);
/* Precondition: year is an integer between 1901 and 2099. month is an integer
 * between 1 and 12.
 * Postcondition: the function prints the calendar of given month in given
 * year.
 */

int main()
/* Precondition: the function requires two integers, the first indicates the
 * year, and the second indicates the month.
 * Postcondition: if input year is between 1901 and 2099, and input month is
 * between 1 and 12, the function prints out the calendar of this month.
 * Otherwise, it prints "Invalid Input!"
 */
{
    int year,
        month;
    cin >> year >> month;

    bool valid = inputYrMn(year, month);
    if (valid)
        showCalendar(year, month);
    else
        cout << "Invalid Input!\n";
    return 0;
}

bool inputYrMn(int &year, int &month)
{
    return 1901 <= year && year <= 2099 && 1 <= month && month <= 12;
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

void showCalendar(int year, int month)
{
    int firstWeekday,
        numOfDays;
    get1stDayOfMonth(year, month, firstWeekday, numOfDays);
    char abbrOfMonth[13][4] = {"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
        "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    cout << "-----------------------------\n"
         << "          " << year << " " << abbrOfMonth[month]
         << "            \n"
         << "-----------------------------\n"
         << " SUN MON TUE WED THU FRI SAT \n";
    int i;
    for (i = 0; i < firstWeekday; i++)
        cout << "    ";
    for (i = 1; i < numOfDays; i++) {
        cout << setw(4) << i;
        if ( i % 7 == 7 - firstWeekday)
            cout << "\n";
    }
    cout << setw(4) << numOfDays << "\n"
         << "-----------------------------\n";

    return;
}

