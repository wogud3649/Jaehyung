#include <iostream>
#include <vector>

using namespace std;

int factors(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
            sum += i;
    }
    return sum;
}

int main()
{
    factors(12);
    return 0;
}