#pragma once
class Knight : public Player
{
public:
	Knight();
	Knight(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance);
	~Knight();

	virtual void Attack(shared_ptr<Creature> other) override;
private:
};

