#include "Framework.h"

Creature::Creature()
: _name("")
, _hp(0)
, _maxHp(_hp)
, _attack(0)
, _isLive(true)
{
}

Creature::Creature(string name, int hp, int attack)
: _name(name)
, _hp(hp)
, _maxHp(hp)
, _attack(attack)
, _isLive(true)
{
}

Creature::~Creature()
{
}

void Creature::SetName(string name)
{
	_name = name;
}

void Creature::SetHp(int hp)
{
	_hp = hp;
}

void Creature::SetAttack(int attack)
{
	_attack = attack;
}

string Creature::GetName()
{
	return _name;
}

int Creature::GetHp()
{
	return _hp;
}

int Creature::GetMaxHp()
{
	return _maxHp;
}

int Creature::GetAttack()
{
	return _attack;
}

bool Creature::IsLive()
{
	return _isLive;
}

void Creature::Attack(Creature* other)
{
	//TODO
}

void Creature::Damaged()
{
	//TODO
}
