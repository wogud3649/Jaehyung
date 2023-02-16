#include "framework.h"

Knight::Knight()
{
}

Knight::Knight(string name)
{
	_name = name;
	_hp = 250;
	_maxHp = _hp;
	_attack = 15;
}

Knight::~Knight()
{
}

void Knight::Attack(Creature* other)
{
	if (_isDead == false)
		if (other->GetDead() == false)
			Sound_Manager::GetInstance()->KnightAttack(this);
}