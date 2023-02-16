#include "Framework.h"
// 미리 컴파일된 헤더
// 1. framework 클래스 추가
// 2. framework.h 에 먼저 컴파일할 h들 include 해주기
// 3. framework.cpp -> 속성 -> 미리컴파일된 헤더(사용) -> 미리 컴파일된 헤더 : framework.h
// 4. 프로젝트 -> 속성 -> 미리컴파일된 헤더(만들기) -> 미리 컴파일된 헤더 : framework.h

// 과제
// 1. 내가 입력한 숫자 대로 클래스 생성, 컴퓨터는 무작위로 하나의 직업 생성 ( ex)1. Knight, 2. Mage, 3. Archer )
// 2. 내가 생성한 객체와 컴퓨터의 객체와 결투
// 3. 서로 죽을 때까지 싸움 반복

int main()
{
	Player p("hanil", 100, 10);
	Knight k("Knight", 200, 15);
	Mage m("Mage", 80, 30);

	k.AttackMage(&m);
	m.AttackKnight(&k);

	return 0;
}