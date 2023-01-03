#pragma once
class Mage : public Player
{
public:
	Mage();
	Mage(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance);
	~Mage();

	virtual void Attack(shared_ptr<Creature> other) override;

private:
};

