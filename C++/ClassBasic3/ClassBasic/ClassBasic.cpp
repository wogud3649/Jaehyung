// 과제
// 객체지향 공부
// Sort 공부
// [5][4][3][2][1] BubbleSort 후에

#include <iostream>
#include <algorithm>

using namespace std;

// 객체지향의 3속성
// 1. 은닉성(캡슐화)
// - 밖에서 함부로 접근하면 안되는 속성을 가리기 위해 쓴다.
// - 접근하면 안되는 속성(private)을 접근할 수 있게하는 멤버함수(public)를 제공해줘야한다.

// 2. 상속성
// - is - a 관계 성립

// 3. 다형성
// - 오버로딩 (멤버함수 오버로딩, 연산자 오버로딩)
// - 오버라이딩 (부모의 함수를 자식의 함수에서 재정의하는 것)
// --> 가상함수(X)
// - 추상 클래스(X)

// struct 와 class의 차이는
// struct 는 암시적으로 public
// class 는 암시적으로 private

// class -> 사용자 정의 자료형
// class -> 설계도
// class 멤버변수, 멤버함수
// 멤버변수 : 속성
// 멤버함수 : 기능

// * 멤버함수 호출 조건:
// 1. 소속
// 2. 객체

// 접근 지정자
// public : 외부 O, 자식 O
// protected : 외부 X, 자식 O
// private : 외부 X, 자식 X

class Car
{
public:
	void DriveCar()
	{
		_handle = 1;
	}

	void PrintEngine()
	{
		// private 멤버변수에 접근할 수 있는 것은 멤버함수 뿐이다.
		_engine = 5;
		cout << _engine << endl;
	}

	void GoCarCenter()
	{
		if (CheckEngine())
		{
			cout << "엔진 이상무" << endl;
		}
		else
		{
			cout << "엔진 고장" << endl;
		}
	}

	int _handle;
	int _door;

private:
	bool CheckEngine()
	{
		return !(_engine == 0);
	}
	int _engine;
	int _light;
};

// 동물은 고양이다. (X)
// 고양이는 동물이다. (O)
// Animal is a Cat (X)
// Cat is an Animal (O)

class Animal
{
public:
	virtual void Eat() { cout << "밥먹기" << endl; }
	void PrintLegs() { cout << "0" << endl; }

protected:
	int _hp;
};

class Cat : public Animal
{
public:
	void Print() { cout << _hp << endl; }

	virtual void Eat() override { cout << "핥아서 먹기" << endl; } // 함수 오버라이딩 : 부모의 Eat 함수를 자식에서 재정의

	void SetLegs(int value) { _legs = value; }

	void PrintLegs() { cout << _legs << endl; }
	void PrintLegs(int a) { cout << _legs << endl; }
	void PrintLegs(int a, int b) { cout << _legs << endl; }

private:
	int _legs;
};

int main()
{
	Car car;
	car._handle = 0;

	car.Car::DriveCar();
	car.Car::PrintEngine(); // -> PrintEngine은 _engine에 접근하기 위한 인터페이스다.
	// 인터페이스는 접근하는 창고

	Animal dog;
	Cat cat0;
	Cat cat1;
	Cat cat2;
	Cat cat3;

	cat0.SetLegs(4);

	dog.PrintLegs();
	cat0.PrintLegs();

	Animal* cats[4] = { nullptr };
	cats[0] = &cat0;
	cats[1] = &cat1;
	cats[2] = &cat2;
	cats[3] = &cat3;

	Cat cat4;
	Animal* ptrA = &cat4;
	(*ptrA).Eat();

	return 0;
}