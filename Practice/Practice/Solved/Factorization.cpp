#include <iostream>

using namespace std;

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

	factorization(a);

	return 0;
}