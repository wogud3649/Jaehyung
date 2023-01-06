#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>

using namespace std;

// ENCHANT

// +0 집행검

// 강화를 하는데
// + 1
// + 2
// + 3

// N 강을 하고 싶다... 이 때 강화하는 대로 나오는 모든 경우의 수.

int NUM = 99;

vector<int> cache(100, -1);

int Enchant(int num)
{
	// 기저
	if (num > NUM)
		return 0;
	if (num == NUM)
		return 1;

	// 캐쉬
	if (cache[num] != -1)
		return cache[num];

	// 구하기
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