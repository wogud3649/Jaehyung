#pragma once
class Knight : public Player
{
public:
	Knight();
	Knight(string name, int hp, int attack);
	~Knight();

	// 전방선언
	void AttackMage(class Mage* mage);

private:

};

