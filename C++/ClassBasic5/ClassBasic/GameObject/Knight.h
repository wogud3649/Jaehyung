#pragma once
class Knight : public Player
{
public:
	Knight();
	Knight(string name, int hp, int attack);
	~Knight();

	virtual void Attack(Player* player) override; // �����Լ� ������
	void SetStamina(int amount) { _stamina = amount; }

private:
	int _stamina;
};

