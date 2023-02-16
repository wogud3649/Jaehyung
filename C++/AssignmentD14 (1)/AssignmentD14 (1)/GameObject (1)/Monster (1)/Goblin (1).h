#pragma once
class Goblin : public Monster
{
public:
	Goblin();
	virtual ~Goblin();

	virtual void Attack(Creature* other) override;
private:
};