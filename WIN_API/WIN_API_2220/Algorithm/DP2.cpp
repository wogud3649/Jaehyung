#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>

using namespace std;

// LIS (Longest Increasing Sequence) : 부분 증가 수열에서 제일 긴 수열의 길이를 찾는다.

// Seq : 1, 2, 9, 5, 8, 10
// 1 2 5 (0) : 부분 수열
// 5 8 10 (0)
// 10 5 1 (X)

// 증가 부분 수열
// 1 2 5 (O)
// 2 9 5 (O)
// 1 2 5 8 10 -> 5

vector<int> seq = { 4,6,1,2,9,5,8,10 };
vector<int> cache(100, -1);

int LIS(int pos)
{
	// 기저사항
	if (pos == seq.size() - 1)
		return 1;

	// 캐시
	int& ref = cache[pos];
	if (ref != -1)
		return ref;

	ref = 1;
	// 구하기
	// LIS(0) = LIS(1) + 1;
	for (int next = pos + 1; next < seq.size(); next++)
	{
		if (seq[pos] < seq[next])
		{
			ref = max(ref, LIS(next) + 1);
		}
	}

	return ref;
}

int main()
{
	int lis = 0;

	for (int i = 0; i < seq.size(); i++)
	{
		lis = max(lis, LIS(i));
	}

	cout << lis << endl;

	return 0;
}