#include <iostream>

using namespace std;

int gcd(int x, int y)
{
	if (y == 0)
		return x;
	else
		return gcd(y, x % y);
}

int main()
{
	int a = 15;
	int b = 37;
	int result;
	if (a > b)
		result = gcd(a, b);
	else
		result = gcd(b, a);

	return 0;
}