#include <iostream>
#include <vector>

using namespace std;

void Coke(int empty, int rate, int divider, int& total)
{
    int service = empty / divider * rate;
    if (service == 0)
        return;

    int rest = empty % divider;
    total += service;
    Coke(service + rest, rate, divider, total);
}

int solution(int a, int b, int n) {
    int answer = 0;
    Coke(n, b, a, answer);

    return answer;
}

int main(void)
{
    solution(3, 2, 20);

    return 0;
}