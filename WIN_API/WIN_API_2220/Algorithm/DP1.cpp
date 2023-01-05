#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>

using namespace std;

// ����
// f(n) = f(n-1) + f(n-2) // -> ���� �κ� ����
// nCr = n-1Cr + n-1Cr-1 // ���� �κ� ����

vector<vector<int>> cache(100, vector<int>(100, -1));

int Combination(int n, int r)
{
	// ���� ���
	if (n == r || r == 0)
		return 1;
	
	// ĳ��
	if (cache[n][r] != -1)
		return cache[n][r];
	
	// ���ϱ�
	cache[n][r] = Combination(n - 1, r) + Combination(n - 1, r - 1);
	return cache[n][r];
}

int main()
{
	int lotto = Combination(45, 7);

	vector<int> v = { 1, 2, 3, 4, 5 };

	int count = 1;
	while (true)
	{
		if (std::next_permutation(v.begin(), v.begin() + 4))
		{
			cout << "���� ��° v" << endl;
			count++;
		}
		else
		{
			cout << count << endl;
			break;
		}
	}

	return 0;
}