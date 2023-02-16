#include <iostream>

using namespace std;

// 과제
// 1. 리펙토링
// 2. 배열에 관해서 조사

// 포인터 vs 참조(Reference)

// 참조
// C++
// 1. 별명
// 1. int aRef = a;
// ==> aRef는 a의 별명이다.

// 어셈블리어
// 포인터와 동일한 구조.

// 참조의 장점
// 1. 쓰기 편하다.
// 2. 안정성

// 참조의 단점
// 1. 쓰기 편하다.
// 2. 초기화가 무조건 필요하다.
// 3. nullptr로 초기화할 수 없다. => 없는 값을 만들 수가 없다.

// 포인터와 참조의 공통점
// 1. 원본에 접근이 가능하다.
// 2. 동작은 둘다 포인터와 동일하게 동작한다. (어셈블리어 관점)
// 3. 크기는 32비트 환경에서 4바이트, 64비트 환경에서 8바이트

// 포인터와 참조의 차이점
// 1. 포인터는 nullptr로 없는 값을 만들 수 있다/ ref는 없는 값이란게 없다.
// 2. ref 는 c++관점에서 별명이라고 해석한다.

struct Player
{
	int _hp;
	int _level;
};

// Call by Value
void PrintPlayer(Player p)
{
	cout << p._hp << endl;
	cout << p._level << endl;
}

// Call by Address
// 원본 수정
void PrintPlayer(Player* ptr)
{
	cout << ptr->_hp << endl;
	cout << ptr->_level << endl;
}

// Call by Reference
// 원본 수정
// 원본 수정을 막아보자 -> const Player& p... 읽기전용
void PrintPlayer(const Player& ref)
{
	cout << ref._hp << endl;
	cout << ref._level << endl;
}

int main(void)
{
	int a = 5;
	int* aPtr = &a;
	int& aRef = a;

	int* bPtr = nullptr;
	// int& bRef; (x)

	aRef = 3;

	int b = 5;
	int* bPtr_ = &b;

	int** bPtrPtr_ = &bPtr_;
	int*& bPtrRef_ = bPtr_;

	*(*bPtrPtr_) = 10;
	cout << b << endl;



	return 0;
}