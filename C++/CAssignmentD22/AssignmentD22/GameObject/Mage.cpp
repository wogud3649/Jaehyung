#include "Framework.h"

Mage::Mage()
: Player()
{
	_type = MAGE;
}

Mage::Mage(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance)
: Player(name, hp, attackDamage, abilityPower, defense, magicResistance)
{
	_type = MAGE;
}

Mage::~Mage()
{
}

void Mage::Attack(shared_ptr<Creature> other)
{
	if (this->_isLive)
		if (other->IsLive())
			SoundManager::GetInstance()->MageAttackSound(shared_from_this(), other);
}