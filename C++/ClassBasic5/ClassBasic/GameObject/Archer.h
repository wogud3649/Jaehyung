#pragma once
class Archer : public Player
{
public:
	Archer();
	Archer(string name, int hp, int attack);
	~Archer();

	virtual void Attack(Player* player) override;

private:
};

