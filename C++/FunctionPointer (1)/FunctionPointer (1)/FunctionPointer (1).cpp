#include <iostream>

using namespace std;

// 함수 포인터 Function Pointer
// 함수이름도 사실상 포인터처럼 동작한다.

// 함수를 미리 담아놓을 수 있는 변수를 선언할 수 있다.
// 콜백함수 : 미리 정의해놓고, 나중에 담고, 나중에 내가 필요한 함수를 자유롭게 호출 가능

// typedef : Type Definition
typedef unsigned int UINT;
typedef void(*FN)(void);
typedef int(*FN2)(int&);

// 멤버함수의 포인터
// 멤버함수 호출 조건
// - 소속
// - 객체
class Pet;
typedef void(Pet::*FN_Pet)(void);

FN fn;
FN2 fn2;

void PrintHello()
{
	cout << "Hello World" << endl;
}

void Test()
{
	cout << "Test" << endl;
}

int AddOne(int& a)
{
	++a;

	return a;
}

class Pet
{
public:
	void SetHp() { _hp = 10000; }
	void Bark() { cout << "왈왈" << endl; }

private:
	int _hp;
};

class Player
{
public:
	void SetFN(FN fn) { _fn = fn; }
	void SetFN_Pet(FN_Pet fn) { _fnPet = fn; }
	void Execute() { _fn(); }
	void CallBackPet(Pet* pet)
	{
		if (_fnPet != nullptr)
			(pet->*_fnPet)();
	}

private:
	FN _fn;
	FN_Pet _fnPet;
};

int main()
{
	UINT uNum = 0;
	int num = 0;
	fn2 = &AddOne;
	fn2(num);

	FN fn1;
	fn1 = &PrintHello;
	fn1();

	fn1 = &Test;
	fn1();

	Player* p = new Player();

	p->SetFN(&PrintHello);
	p->Execute();

	p->SetFN(&Test);
	p->Execute();

	FN_Pet _fnPet;
	Pet* pet = new Pet();
	_fnPet = &Pet::Bark;
	(pet->*_fnPet)();

	p->SetFN_Pet(&Pet::SetHp);
	p->CallBackPet(pet);

	return 0;
}