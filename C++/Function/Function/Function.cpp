#include <iostream>

using namespace std;

// Function

// f(x) = y
// x는 매개변수, y는 치역

// 함수 시그니쳐
// int Add(int a, int b)
// 반환형식 : int 
// 함수이름 : Add
// 매개변수 : int a, int b

// void : 공허한,

void PrintHello(void)
{
	cout << "Hello World!" << endl;
}

// 함수 오버로딩
// - 함수 이름은 같아도 매개변수 타입으로 여러개의 함수를 정의할 수 있다.

int Add(int a, int b)
{
	return a + b;
}

float AddFloat(float a, float b)
{
	return a + b;
}

int Add(int a)
{
	return a + 5;
}
// 기본인자
int Add(int a, int b, int c, int d = 15)
{
	return a + b + c + d;
}

// Stack
// 지역변수, 반환주소값, 매개변수

// 스택프레임
// [매개변수][반환주소값][지역변수]


int Add(int a, int b, int c, int d, int e)
{
	return Add(a, b, c, d) + e;
}

// 재귀함수 : 자기가 자기자신을 호출하는 함수
// f(x) = f(x-1) + f(x-2);
// 팩토리얼
// 5! = 5 x 4 x 3 x 2 x 1;
// => 5 x 4!
// => 5 x 4 x 3!...

// 스택오버플로우 : 컴파일 도중 스택영역 초과

int Factorial(int num)
{
	// 기저사항
	if (num == 1)
		return 1;

	return num * Factorial(num - 1);
}

int main(void)
{
	int aInt = Add(1, 2);
	int bInt = Add(1);
	int cInt = Add(1, 2, 3, 4);
	int dInt = Add(1, 2, 3, 4, 5);
	float aFloat = Add(1.0f, 2.0f);
	PrintHello();

	int check = Factorial(10000);
	cout << check << endl;
	return 0;
}