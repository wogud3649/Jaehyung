#include "framework.h"

Creature::Creature() : _name(""), _hp(0), _maxHp(0), _attack(0), _isDead(false)
{
}

Creature::~Creature()
{
}

void Creature::SetName(const string& name)
{
	_name = name;
}

void Creature::SetHp(const int& hp)
{
	_hp = hp;
}

void Creature::SetMaxHp(const int& maxHp)
{
	_maxHp = maxHp;
}

void Creature::SetAttack(const int& attack)
{
	_attack = attack;
}

const string& Creature::GetName()
{
	return _name;
}

const int& Creature::GetHp()
{
	return _hp;
}

const int& Creature::GetMaxHp()
{
	return _maxHp;
}

const int& Creature::GetAttack()
{
	return _attack;
}

const bool& Creature::GetDead()
{
	return _isDead;
}

void Creature::PrintInfo()
{
	cout << "NAME : " << _name << endl;
	cout << "HP : " << _hp << endl;
	cout << "ATTACK : " << _attack << endl;
}

void Creature::Attack(Creature* other)
{
}

void Creature::Damaged(Creature* other)
{
	if (other->GetDead() == false)
	{
		if (_isDead == false)
		{
			_hp -= other->GetAttack();
			if (_hp < 0)
				_hp = 0;
			Sound_Manager::GetInstance()->Damaged(this, other);
			IsDead();
		}
	}
}

void Creature::IsDead()
{
	if (_hp == 0)
	{
		_isDead = true;
		Sound_Manager::GetInstance()->Dead(this);
	}
}