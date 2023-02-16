#include <iostream>

using namespace std;

// Template
// : 찍어내는 틀
// -> 클래스, 함수를 찍어내는 틀

// class : 설계도
// -> 객체를 찍어내는 틀

// 함수 템플릿
template <typename T = int> // 템플릿의 기본인자
T Add(T a, T b)
{
	return a + b;
}

// 템플릿의 특수화
template<>
int* Add(int* a, int* b)
{
	cout << "Ptr를 더했습니다." << endl;
	return a;
}

// 클래스 템플릿
// 주의할 점
// - 빨간줄 안뜸
// - 파일 분할할 수 없음.
template <typename T = int>
class Player
{
public:
	Player()
	{
	}
public:
	T _hp[10];
};

template<>
class Player<double>
{
public:
private:
	double _hp[10];
	int _atk;
};

int main()
{
	int a = 1;
	int b = 2;
	cout << Add(1, 2) << endl;

	Player<int> p;

	return 0;
}