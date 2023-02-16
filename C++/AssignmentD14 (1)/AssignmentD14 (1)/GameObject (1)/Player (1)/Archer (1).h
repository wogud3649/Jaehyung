#pragma once
class Archer : public Player
{
public:
	Archer();
	Archer(string name);
	virtual ~Archer();

	virtual void Attack(Creature* other) override;
private:
};