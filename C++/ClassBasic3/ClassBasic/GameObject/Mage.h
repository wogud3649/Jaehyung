#pragma once
class Mage : public Player
{
public:
	Mage();
	Mage(string name, int hp, int attack);
	~Mage();

	void AttackKnight(Knight* knight);
private:
};

