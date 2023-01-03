#include "Framework.h"

Goblin::Goblin()
: Monster()
{
}

Goblin::Goblin(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance)
: Monster(name, hp, attackDamage, abilityPower, defense, magicResistance)
{
}

Goblin::~Goblin()
{
}

void Goblin::Attack(shared_ptr<Creature> other)
{
	if (this->_isLive)
		if (other->IsLive())
			SoundManager::GetInstance()->GoblinAttackSound(shared_from_this(), other);
}