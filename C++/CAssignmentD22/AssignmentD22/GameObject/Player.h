#pragma once
class Player : public Creature
{
public:
	Player();
	Player(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance);
	~Player();

protected:
	int _type;
};