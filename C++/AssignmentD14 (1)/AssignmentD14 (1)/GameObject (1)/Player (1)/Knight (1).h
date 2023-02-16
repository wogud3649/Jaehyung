#pragma once
class Knight : public Player
{
public:
	Knight();
	Knight(string name);
	virtual ~Knight();

	virtual void Attack(Creature* other) override;
private:
};