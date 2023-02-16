#include <iostream>

using namespace std;

// 수를 입력받는다.
// 5
// *
// **
// ***
// ****
// *****

// 3
// *
// **
// ***

int main()
{
	int num;
	int star, aInt=0;
	cin >> star;

	while (true)
	{
		for (int i = aInt; i >= 0; i--)
		{
			cout << "*";
		}
		if (aInt == star-1)
		{
			break;
		}
		cout << endl;
		aInt++;
	}

	// 이중 for 문 -> 이차원 for 문
	for (int y = 0; y < num; y++)
	{

	}
	return 0;
}