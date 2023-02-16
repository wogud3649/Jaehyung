#pragma once
class Creature
{
public:
	Creature();
	Creature(string name, int hp, int attack);
	virtual ~Creature();

	void SetName(string name);
	void SetHp(int hp);
	void SetAttack(int attack);

	string GetName();
	int GetHp();
	int GetMaxHp();
	int GetAttack();
	bool IsLive();

	virtual void Attack(Creature* other) abstract;
	void Damaged();

protected:
	string _name;
	int _hp;
	int _maxHp;
	int _attack;
	bool _isLive;
};

