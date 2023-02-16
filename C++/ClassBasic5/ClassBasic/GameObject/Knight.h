#pragma once
class Knight : public Player
{
public:
	Knight();
	Knight(string name, int hp, int attack);
	~Knight();

	virtual void Attack(Player* player) override; // 가상함수 재정의
	void SetStamina(int amount) { _stamina = amount; }

private:
	int _stamina;
};

