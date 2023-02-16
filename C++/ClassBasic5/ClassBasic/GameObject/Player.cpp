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

// :: �������������� ... �Ҽӿ�����
void Player::Attack(Player* player)
{
	cout << "Player Attack!" << endl;
	player->TakeDamage(_attack);
}

void Player::TakeDamage(int amount)
{
	_hp -= amount;

	cout << _name << "��" << amount << "��ŭ�� �������� �Ծ����ϴ�." << endl;
	if (_hp < 0)
		_hp = 0;
}

bool Player::IsDead()
{
	if (_hp <= 0)
	{
		cout << _name << "�� �׾����ϴ�." << endl;
		return true;
	}

	return false;
}
