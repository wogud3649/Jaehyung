#pragma once
class Monster : public Creature
{
public:
	Monster();
	Monster(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance);
	~Monster();

protected:
};

