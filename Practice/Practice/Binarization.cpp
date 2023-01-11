#include <iostream>

using namespace std;

void Binarization(int n)
{
    int bin = 0;
    for (int count = 0; n != 0; n /= 2, count++)
    {
        if (n % 2 == 0)
            continue;
        bin = bin * pow(10, count) + n % 2;
    }
}

int main(void)
{
    Binarization(9);

    return 0;
}