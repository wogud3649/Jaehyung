#include <iostream>

using namespace std;

// ���� �Է¹޴´�.
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

	// ���� for �� -> ������ for ��
	for (int y = 0; y < num; y++)
	{

	}
	return 0;
}