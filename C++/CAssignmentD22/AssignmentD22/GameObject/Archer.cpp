#include "Framework.h"

Archer::Archer()
: Player()
{
	_type = ARCHER;
}

Archer::Archer(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance)
: Player(name, hp, attackDamage, abilityPower, defense, magicResistance)
{
	_type = ARCHER;
}

Archer::~Archer()
{
}

void Archer::Attack(shared_ptr<Creature> other)
{
	if (this->_isLive)
		if (other->IsLive())
			SoundManager::GetInstance()->ArcherAttackSound(shared_from_this(), other);
}