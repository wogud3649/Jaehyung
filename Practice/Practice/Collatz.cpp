#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

void Collatz(long long num, int& count)
{
    if (count == 500)
    {
        count = -1;
        return;
    }
    if (num == 1)
        return;

    count++;
    if (num % 2 == 0)
        Collatz(num / 2, count);
    else
        Collatz(num * 3 + 1, count);
}

int solution(int num) {
    long long temp = num;
    int answer = 0;

    Collatz(num, answer);

    return answer;
}

int main()
{
    solution(6);

    return 0;
}