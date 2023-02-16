#include <iostream>
#include <vector>

using namespace std;

// vector
// capacity : 최대수용량
// size : 실제 크기
// offset : 배열의 첫번째 주소

// vector
// 장점
// 1. 접근할 때 걸리는 시간이 1

// 단점
// 1. 중간 삽입, 삭제가 비효율적이다.
// -> 첫 인덱스 삭제, 삽입은 최대 비효율(최대 N번)

void PrintV(const vector<int>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
}
int main()
{
	vector<int> v;
	v.reserve(10);

	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	v.pop_back();

	PrintV(v);

	return 0;
}