#pragma once
class Archer : public Player
{
public:
	Archer();
	Archer(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance);
	~Archer();

	virtual void Attack(shared_ptr<Creature> other) override;

private:
};

