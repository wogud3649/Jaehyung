#include <iostream>

using namespace std;

#include "Sound_Manager.h"

// 과제
// Sound Manager 만들어서
// 각 클래스가 Attack 할 때 사운드 출력

// - 가상함수... 가상함수 테이블
// - RTTI

// CODE
// 
// DATA
// - 생성주기
// -- 생성 : 프로그램 실행
// -- 삭제 : 프로그램 종료
// - 전역변수
// - static 변수
// -> 프로그램에서 단 하나.
// -> 어디서든 접근 가능
// -> 클래스 안에 존재 가능
// 
// STACK
// -- 생성 : 지역이 시작될 때
// -- 삭제 : 지역이 끝날 때
// - 매개변수
// - 반환주소값
// - 지역변수
// 
// HEAP
// -- 생성 : 프로그래머 마음대로
// -- 삭제 : 프로그래머 마음대로
// - 특징
// -- 사용자 메모리, 프로그래머 메모리

// 동적할당
// -> 운영체제에 요청 -> 커널에서 Heap 영역에 메모리 용량 확보

// 짝궁
// - malloc, free
// - new, delete
// - new [], delete []

class Player
{
public:
	Player() : _hp(0) {}
	Player(int hp) : _hp(hp) {}
	~Player() {}

	void PrintInfo()
	{
		cout << _hp << endl;
		cout << _attack << endl;
	}

	void Attack()
	{
		Sound_Manager::GetInstance()->WarriorAttack();
	}

	static int _attack;
private:
	int _hp;
};

int Player::_attack = 5; // -> 클래스 내부에 선언된 static 변수는 전역에서 초기화를 해줘야한다.

// 싱글톤 패턴

static int a = 5; // class 안에도 들어갈 수 있음.

int main()
{
#pragma region 동적할당
	// use after free

	void* ptr = malloc(1000); // 1000 byte 할당
	// void : 공허한
	// void* : 어떠한 자료형이든 올 수 있다.

	Player p1 = Player(100);
	Player* p = new Player(p1);
	Player* p2 = new Player(30);
	Player* p3 = new Player(50);

	//int* intPtr = new int(); // 4 byte 할당
	//cout << *intPtr << endl;
	//*intPtr = 5;
	//cout << *intPtr << endl;

	//int* arrPtr = new int[5];

	//delete[] arrPtr;
	//delete intPtr; // new 메모리 삭제
	//free(ptr); // malloc 메모리 삭제

	delete p; // 허상 포인터  -> dangling pointer

	free(ptr);
#pragma endregion

#pragma region 싱글톤
	Sound_Manager::CreateInstance();
	Player* player1 = new Player(5);
	Player* player2 = new Player(5);
	Player* player3 = new Player(5);

	Sound_Manager::GetInstance()->WarriorAttack();

	Sound_Manager::DeleteInstance();
#pragma endregion
	return 0;
}