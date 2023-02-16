#pragma once
class Player : public Creature
{
public:
	Player();
	virtual ~Player();

	virtual void Attack(Creature* other) abstract;
protected:
};