#include "Framework.h"

// ĳ����
// Casting : �ڷ��� ��ȯ

// int -> float
// 1 -> 1.0f => ������ ĳ����
// float -> int
// 1.5f -> 1 => �Ҿ����� ĳ����

// short -> int
// 32767 -> 32767 => ������ ĳ����
// int -> short
// 21�� -> short => �Ҿ����� ĳ����

// p1 = (Player)k1; // ��ĳ����
// k1 = (Knight)p1; // �Ҿ����� ĳ����, �ٿ� ĳ����

// c++ ĳ���� 4�ѻ�
// static_cast (95%)
// - �������� ���� �Ǹ� OK
// 
// const_cast (?)
// - const ���� �� ����, ���̰�
// 
// dynamic_cast (4.9999...%)
// - RTTI�� �̿��ؼ� ��Ÿ�ӿ� Ÿ���߷��� �Ѵ�.
// - vftable�� �־�� �Ѵ�. -> �����Լ��� �ϳ��� �����ؾ� �Ѵ�.

// reinterpret_cast (?)
// - ������ ���� �θ��� ��

// ���ڿ�

// data
// - data
// - bss
// - rodata : ���ͷ� ���

int main()
{
#pragma region ĳ���ð� RTTI
	Player p1;
	Knight k1;

	p1 = static_cast<Player>(k1);

	srand((unsigned int)time(nullptr));
	// Player -> Knight
	Player* arr[2];

	arr[0] = new Player("hanil", 50, 5);
	arr[1] = new Knight("����", 100 ,10);
	// dynamic_cast<Knight*>(arr[1])->SetStamina(5);

/*	arr[0]->Attack(arr[1]);
	arr[1]->Attack(arr[0]);*/ // -> Knight�� Attack
	// -> ���� �߿� Ÿ���� �߷��ϸ� ���?
	// -> RTTI (Run Time Type Information)

	// vft (virtual function table)
	// -> RTTI ����� ���� ���ִ� ����

	// arr[1] �� Knight�� ����Ű�� Player* �̴�.
	// -> ���� �ϰ� ���� �� Knight�� �Լ��� ���� �ʹ�.
	dynamic_cast<Knight*>(arr[1])->SetStamina(5);
	
	for (int i = 0; i < 2; i++)
	{
		delete arr[i];
	}
#pragma endregion

	char str[6] = { 'h','a','n','i','l','\0' }; // ���ڿ��� �׻� �ڰ� 0���� ������ ������ �˾Ƶ�´�.
	const char* str1 = "Hello World!"; // "���ڿ�" -> ���ͷ� ��� rodata���� ����ϹǷ� �޸𸮸� �� ����Ѵ�.
	char str2[13] = "Hello World!"; // rodata�� �ִ� ���� �����Ͽ� �޸𸮿� �Ҵ��Ѵ�.

	char* str3 = const_cast<char*>(str1);

	cout << str << endl;

	return 0;
}