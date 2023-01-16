#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

string solution(int a, int b) {
    string answer = "";
    string days[7] = {
    "THU",
    "FRI",
    "SAT",
    "SUN",
    "MON",
    "TUE",
    "WED"
    };
    int day = b;

    switch (a)
    {
    case 2:
    {
        day += 31;
        break;
    }
    case 3:
    {
        day += 60;
        break;
    }
    case 4:
    {
        day += 91;
        break;
    }
    case 5:
    {
        day += 121;
        break;
    }
    case 6:
    {
        day += 152;
        break;
    }
    case 7:
    {
        day += 182;
        break;
    }
    case 8:
    {
        day += 213;
        break;
    }
    case 9:
    {
        day += 244;
        break;
    }
    case 10:
    {
        day += 274;
        break;
    }
    case 11:
    {
        day += 305;
        break;
    }
    case 12:
    {
        day += 335;
        break;
    }
    default:
        break;
    }

    return days[day % 7];
}

int main(void)
{
    solution(5, 24);

    return 0;
}