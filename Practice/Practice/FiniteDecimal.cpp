#include <iostream>

using namespace std;

int gcd(int x, int y)
{
	if (y == 0)
		return x;
	else
		return gcd(y, x % y);
}

void factorization(int x)
{
	for (int i = 2; x > 1;)
	{
		if (x % i == 0)
		{
			if (i != 2 && i != 5)
			{
				cout << "Infinite" << endl;
				return;
			}
			x /= i;
		}
		else
			i++;
	}
	cout << "Finite" << endl;
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

	b /= result;
	factorization(b);

	return 0;
}