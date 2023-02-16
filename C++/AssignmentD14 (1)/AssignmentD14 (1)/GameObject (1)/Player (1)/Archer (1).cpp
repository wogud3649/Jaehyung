#include "framework.h"

Archer::Archer()
{
}

Archer::Archer(string name)
{
	_name = name;
	_hp = 175;
	_maxHp = _hp;
	_attack = 30;
}

Archer::~Archer()
{
}

void Archer::Attack(Creature* other)
{
	if (_isDead == false)
		if (other->GetDead() == false)
			Sound_Manager::GetInstance()->ArcherAttack(this);
}