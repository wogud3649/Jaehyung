#pragma once
class Player
{
public:
	//struct PlayerInfo
	//{
	//	string name;
	//	int hp;
	//	int attack;
	//};

	Player();
	Player(string name, int hp, int attack);

	virtual void Attack(Player* player); // 가상함수

	void TakeDamage(int amount);

	bool IsDead();

	const string& GetName() { return _name; }
	int GetHp() { return _hp; }
	int GetAttack() { return _attack; }

	//void SetPlayer(const PlayerInfo& p) { _name = p.name; }
	void SetName(const string& name) { _name = name; }
	void SetHp(int hp) { _hp = hp; }
	void SetAttack(int attack) { _attack = attack; }

protected:
	int _hp;
	int _attack;
	string _name;
};