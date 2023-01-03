#include "Framework.h"

Creature::Creature()
: _name("")
, _hp(0)
, _maxHp(_hp)
, _attackDamage(0)
, _abilityPower(0)
, _defense(0)
, _magicResistance(0)
, _damageTaken(0)
, _isLive(true)
{
}

Creature::Creature(string name, int hp, int attackDamage, int abilityPower , int defense, int magicResistance)
: _name(name)
, _hp(hp)
, _maxHp(hp)
, _attackDamage(attackDamage)
, _abilityPower(abilityPower)
, _defense(defense)
, _magicResistance(magicResistance)
, _damageTaken(0)
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

void Creature::SetAttackDamage(int attackDamage)
{
	_attackDamage = attackDamage;
}

void Creature::SetAbilityPower(int abilityPower)
{
	_abilityPower = abilityPower;
}

void Creature::SetDefense(int defense)
{
	_defense = defense;
}

void Creature::SetMagicResistance(int magicResistance)
{
	_magicResistance = magicResistance;
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

int Creature::GetAttackDamage()
{
	return _attackDamage;
}

int Creature::GetAbilityPower()
{
	return _abilityPower;
}

int Creature::GetDefense()
{
	return _defense;
}

int Creature::GetMagicResistance()
{
	return _magicResistance;
}

int Creature::GetDamageTaken()
{
	return _damageTaken;
}

bool Creature::IsLive()
{
	return _isLive;
}

void Creature::TakeDamage(shared_ptr<Creature> other)
{
	if (this->_isLive)
	{
		if (other->IsLive())
		{
			int tempAd = other->GetAttackDamage() - this->_defense;
			int tempAp = other->GetAbilityPower() - this->_magicResistance;
			if (tempAd < 0)
				tempAd = 0;
			if (tempAp < 0)
				tempAp = 0;
			_damageTaken = (tempAd + tempAp);
			this->_hp -= _damageTaken;
			if (this->_hp <= 0)
			{
				_hp = 0;
				_isLive = false;
			}
			SoundManager::GetInstance()->TakeDamageSound(tempAd, tempAp, shared_from_this());
			if (this->_hp == 0)
			{
				SoundManager::GetInstance()->DeadSound(shared_from_this());
			}
		}
	}
}