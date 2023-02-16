#include "framework.h"

Goblin::Goblin()
{
	_name = "goblin";
	_hp = 40;
	_maxHp = _hp;
	_attack = 3;
}

Goblin::~Goblin()
{
}

void Goblin::Attack(Creature* other)
{
	if (_isDead == false)
		if (other->GetDead() == false)
			Sound_Manager::GetInstance()->GoblinAttack(this);
}