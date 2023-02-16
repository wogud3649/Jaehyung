#pragma once
class Mage : public Player
{
public:
	Mage();
	Mage(string name);
	virtual ~Mage();

	virtual void Attack(Creature* other) override;
private:
};

