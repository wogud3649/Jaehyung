#include <iostream>

using namespace std;

// 함수포인터
// 장점 : 시그니처만 맞으면 어떤 함수던 간에 나중에 호출할 수 있다.
// 단점 : 함수 객체랑 비교했을 때 속성(멤버변수)을 가질 수 없다.

// 함수객체
// - 속성을 가질 수 있는 함수
// - 객체만 미리 선언해 두고, 함수 호출을 나중에 할 수 있다.
// - STL -> 알고리즘에 필요하다.

struct Functor
{
	void operator()()
	{
		cout << "HelloWorld!" << endl;
		cout << "속성 : " << _value << endl;
	}

	void operator()(int& a)
	{
		++a;
	}

	int _value = 5;
};

int main()
{
	int aInt = 0;

	Functor functor;
	functor();
	functor._value = 100;
	functor();

	functor(aInt);

	return 0;
}