#include "framework.h"

Mage::Mage()
{
}

Mage::Mage(string name)
{
	_name = name;
	_hp = 100;
	_maxHp = _hp;
	_attack = 40;
}

Mage::~Mage()
{
}

void Mage::Attack(Creature* other)
{
	if (_isDead == false)
		if (other->GetDead() == false)
			Sound_Manager::GetInstance()->MageAttack(this);
}