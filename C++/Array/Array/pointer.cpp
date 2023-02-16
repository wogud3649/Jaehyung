#include <iostream>

using namespace std;

// 포인터와 참조 차이
// -> 1. 포인터는 nullptr로 초기화가 가능하다. => 없는 값을 만들 수 있다.
// -> 2. 원본을 수정할 수 있다.
// -> 3. 어셈블리어 관점에선 구조가 동일하다.

struct Player
{
	int _hp;
	int _mp;
};

void SetPlayer(Player* p, int hp, int mp)
{
	p->_hp = hp;
	p->_mp = mp;
}

// 읽기 전용 : 수정이 불가능한
void PrintPlayer(const Player& p)
{
	cout << p._hp << endl;
	cout << p._mp << endl;
}

int main()
{
	Player myPlayer;
	myPlayer._hp = 0;
	myPlayer._mp = 0;
	
	SetPlayer(&myPlayer, 10, 5);
	// hp = 10
	// mp = 5
	PrintPlayer(myPlayer);

	return 0;
}