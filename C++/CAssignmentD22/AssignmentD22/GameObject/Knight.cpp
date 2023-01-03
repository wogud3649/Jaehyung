#include "Framework.h"

Knight::Knight()
: Player()
{
	_type = KNIGHT;
}

Knight::Knight(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance)
: Player(name, hp, attackDamage, abilityPower, defense, magicResistance)
{
	_type = KNIGHT;
}

Knight::~Knight()
{
}

void Knight::Attack(shared_ptr<Creature> other)
{
	if (this->_isLive)
		if (other->IsLive())
			SoundManager::GetInstance()->KnightAttackSound(shared_from_this(), other);
}