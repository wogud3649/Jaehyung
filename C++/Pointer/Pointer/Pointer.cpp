#include <iostream>

using namespace std;

// 포인터
// Pointer -> 가리키는 애
// (자료형)* (변수 이름) = (초기값);
// 크기 = 32비트 환경에서 4바이트, 64비트에서 8바이트
// (자료형) : 포탈을 타고 들어갔을 때 그 데이터의 자료형 -> 힌트

// 포인터의 연산자
// &(변수이름) : 주소 연산자 (해당변수의 주소값을 반환한다)
// *(포인터) : 간접 연산자 (해당 포인터가 가리키는 주소로 이동한다.. 포탈연산자)

// a * b : -> 곱하기 연산
// *a -> 간접 연산자
// (포인터)-> : 간접멤버연산자... *(포인터).

// 포인터의 위험성
// 포인터가 가리키는 주소값을 마음대로 바꿀 수 있다. -> 메모리 오염

// 스택프레임 : [매개변수][반환주소값][지역변수]

// main								Add
// [void][반환주소값][a=5,aPtr=&a]	[int b = a][반환주소값][]

// Call by Value : 값전달, 값으로 호출

void Add(int a)
{
	a += 1;
}

// main								Add
// [void][반환주소값][a=5,aPtr=&a]	[int* b = &a][반환주소값][]
// Call by Address : 주소전달, 주소로 호출
void Add(int* a)
{
	(*a) += 1;
}

struct Player
{
	float _hp;
	int _level;
};

// p... 8바이트
void PrintPlayer(Player p)
{
	cout << p._hp << endl;
	cout << p._level << endl;
}

void PrintPlayer(const Player* const p) /// Plyaer의 정보 출력 -> 읽기전용
{
	cout << p->_hp << endl;
	cout << p->_level << endl;
}

void SetPlayer(Player* const p, int hp, int level)
{
	p->_hp = hp;
	p->_level = level;
}

int main(void)
{
	int a = 5;
	int* aPtr = &a;

	*aPtr = 10;

	Add(a);
	
	float b = 1.0f;
	float* bPtr = (float*)&b; // () -> cast
	(*bPtr) = 1.0f;

	Player  p1;
	p1._hp = 10;
	p1._level = 1;

	Player* pPtr = &p1; // pPtr 은 p1 의 첫번째 주소를 가리킨다.

	SetPlayer(pPtr, 50, 30);
	PrintPlayer(p1);


	return 0;
}