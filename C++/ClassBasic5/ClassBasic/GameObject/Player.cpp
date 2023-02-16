#include "Framework.h"

Player::Player()
: _name("")
, _hp(0)
, _attack(0)
{

}

Player::Player(string name, int hp, int attack)
: _name(name)
, _hp(hp)
, _attack(attack)
{
}

// :: 범위지정연산자 ... 소속연산자
void Player::Attack(Player* player)
{
	cout << "Player Attack!" << endl;
	player->TakeDamage(_attack);
}

void Player::TakeDamage(int amount)
{
	_hp -= amount;

	cout << _name << "이" << amount << "만큼의 데미지를 입었습니다." << endl;
	if (_hp < 0)
		_hp = 0;
}

bool Player::IsDead()
{
	if (_hp <= 0)
	{
		cout << _name << "이 죽었습니다." << endl;
		return true;
	}

	return false;
}
