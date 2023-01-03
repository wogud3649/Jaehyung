#pragma once
class Goblin : public Monster
{
public:
	Goblin();
	Goblin(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance);
	~Goblin();

	virtual void Attack(shared_ptr<Creature> other) override;

private:
};