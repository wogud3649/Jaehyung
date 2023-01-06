#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>

using namespace std;

// ENCHANT

// +0 �����

// ��ȭ�� �ϴµ�
// + 1
// + 2
// + 3

// N ���� �ϰ� �ʹ�... �� �� ��ȭ�ϴ� ��� ������ ��� ����� ��.

int NUM = 99;

vector<int> cache(100, -1);

int Enchant(int num)
{
	// ����
	if (num > NUM)
		return 0;
	if (num == NUM)
		return 1;

	// ĳ��
	if (cache[num] != -1)
		return cache[num];

	// ���ϱ�
	int a = Enchant(num + 1);
	int b = Enchant(num + 2);
	int c = Enchant(num + 3);
	cache[num] = a + b + c;
	return cache[num];
}

int main()
{
	int result = Enchant(0);

	cout << result << endl;

	return 0;
}