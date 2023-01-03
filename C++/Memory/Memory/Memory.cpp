﻿#include <iostream>
#include <vector>

using namespace std;

class Player
{
};

// Memory의 구조
// 프로그램 실행을 위해 프로그램이 메모리에 로드돼야 하는데
// 이때 프로그램이 운영체제로부터 할당받는 메모리 공간은 대표적으로 4가지이다.
// 1. CODE
// 실행시킬 프로그램의 코드가 저장되는 영역 (텍스트 영역)
// CPU에서 코드영역의 명령어를 하나씩 처리한다
// 2. DATA
// - 전역변수와 정적변수가 저장되는 영역이다
// - 프로그램 시작 시 할당되고 프로그램 종료 시 소멸된다
// - 전역변수 : 어디서든 메모리를 읽을 수 있다
int a = 1; // 어떤 값으로 초기화할 경우 DATA 영역에 저장
int b; // 초기화하지 않고 선언만 할 경우 BSS 영역에 저장
// - 정적변수 : 자료형 앞에 static을 붙여 선언
// -> 프로그램 시작 후 초기화는 단 한번만 실행
static int c; // 초기화하지 않아도 0으로 초기화
// rodata (read only data)
// 3. STACK
// - 지역변수와 매개변수가 저장되는 영역이다
// - 함수가 호출될 때 할당되고 호출 완료 후 소멸된다
// - 스택영역에 저장되는 함수의 호출 정보를 스택프레임이라고 한다
// - 푸시동작으로 데이터를 저장하고 팝동작으로 데이터를 인출한다
// - 후입선출 방식으로 동작
// - 메모리의 높은주소에서 낮은주소 방향으로 할당된다
int main()
{
	// 지역변수 : 지역이 시작될 때 메모리 할당, 지역이 끝나면 메모리 해제
	// {} : 지역
	{
		int b = 2; // 같은 지역 안에서만 메모리를 읽을 수 있다
	}
	// 4.HEAP
	// - 사용자가 직접 관리할 수 있고 관리해야 하는 영역이다
	// - 동적으로 할당되고 해제되는 메모리 공간
	// - 메모리의 낮은주소에서 높은주소 방향으로 할당된다
	// - malloc, free
	// - new, delete
	// - new [], delete []
	void* ptr = malloc(1000); // ptr에 1000만큼의 메모리 영역 할당
	// void* : 어떤 자료형이든 올 수 있음
	Player* p = new Player();
	Player* p2 = new Player[5];
	delete[] p2;
	delete p;
	free(ptr);
	return 0;
}