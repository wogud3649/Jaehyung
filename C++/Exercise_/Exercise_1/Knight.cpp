#include "Knight.h"
#include <iostream>
using namespace std;

// [사양서] 기본값 Hp=100, Attack=10
Knight::Knight() : _hp(100), _attack(10)
{

}

Knight::Knight(int hp, int attack) : _hp(hp), _attack(attack)
{

}

Knight::~Knight()
{

}

void Knight::PrintInfo()
{
	cout << "HP: " << _hp << endl;
	cout << "ATT: " << _attack << endl;
}