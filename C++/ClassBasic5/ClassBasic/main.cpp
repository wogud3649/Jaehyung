#include "Framework.h"

// 캐스팅
// Casting : 자료형 변환

// int -> float
// 1 -> 1.0f => 안전한 캐스팅
// float -> int
// 1.5f -> 1 => 불안전한 캐스팅

// short -> int
// 32767 -> 32767 => 안전한 캐스팅
// int -> short
// 21억 -> short => 불안전한 캐스팅

// p1 = (Player)k1; // 업캐스팅
// k1 = (Knight)p1; // 불안전한 캐스팅, 다운 캐스팅

// c++ 캐스팅 4총사
// static_cast (95%)
// - 논리적으로 말이 되면 OK
// 
// const_cast (?)
// - const 붙은 걸 떼고, 붙이고
// 
// dynamic_cast (4.9999...%)
// - RTTI를 이용해서 런타임에 타입추론을 한다.
// - vftable이 있어야 한다. -> 가상함수가 하나라도 존재해야 한다.

// reinterpret_cast (?)
// - 강제로 땡깡 부리는 애

// 문자열

// data
// - data
// - bss
// - rodata : 리터럴 상수

int main()
{
#pragma region 캐스팅과 RTTI
	Player p1;
	Knight k1;

	p1 = static_cast<Player>(k1);

	srand((unsigned int)time(nullptr));
	// Player -> Knight
	Player* arr[2];

	arr[0] = new Player("hanil", 50, 5);
	arr[1] = new Knight("한일", 100 ,10);
	// dynamic_cast<Knight*>(arr[1])->SetStamina(5);

/*	arr[0]->Attack(arr[1]);
	arr[1]->Attack(arr[0]);*/ // -> Knight의 Attack
	// -> 실행 중에 타입을 추론하면 어떨까?
	// -> RTTI (Run Time Type Information)

	// vft (virtual function table)
	// -> RTTI 기능을 쓰게 해주는 열쇠

	// arr[1] 은 Knight를 가리키는 Player* 이다.
	// -> 내가 하고 싶은 건 Knight의 함수를 쓰고 싶다.
	dynamic_cast<Knight*>(arr[1])->SetStamina(5);
	
	for (int i = 0; i < 2; i++)
	{
		delete arr[i];
	}
#pragma endregion

	char str[6] = { 'h','a','n','i','l','\0' }; // 문자열은 항상 뒤가 0으로 끝나는 성질로 알아듣는다.
	const char* str1 = "Hello World!"; // "문자열" -> 리터럴 상수 rodata에서 사용하므로 메모리를 덜 사용한다.
	char str2[13] = "Hello World!"; // rodata에 있는 것을 복사하여 메모리에 할당한다.

	char* str3 = const_cast<char*>(str1);

	cout << str << endl;

	return 0;
}