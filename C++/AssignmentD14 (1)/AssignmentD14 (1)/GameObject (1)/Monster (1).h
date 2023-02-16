#pragma once
class Monster : public Creature
{
public:
	Monster();
	virtual ~Monster();

	virtual void Attack(Creature* other) abstract;
protected:
};