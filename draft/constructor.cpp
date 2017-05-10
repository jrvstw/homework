#include <iostream>
using namespace std;

class dayOfYear
{
    public:
        dayOfYear(int a, int b = 1);
        int getMonth();
        int getDay();
    private:
        int month;
        int day;
};

dayOfYear::dayOfYear(int a, int b)
    :month(a), day(b)
{
    if (month > 12)
        cout << "Error\n";
}

int dayOfYear::getMonth()
{
    return month;
}

int dayOfYear::getDay()
{
    return day;
}

int main()
{
    dayOfYear kk(15, 3);
    //kk = dayOfYear(3,4);
    cout << kk.getMonth() << kk.getDay()<< endl;

    return 0;
}

