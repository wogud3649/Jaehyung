#pragma once
class Boss : public Monster
{
public:
	Boss();
	Boss(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance);
	~Boss();


protected:
};