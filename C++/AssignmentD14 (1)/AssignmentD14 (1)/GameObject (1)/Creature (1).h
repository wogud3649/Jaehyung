#pragma once
class Creature
{
public:
	Creature();
	virtual ~Creature();

	void SetName(const string& name);
	void SetHp(const int& hp);
	void SetMaxHp(const int& maxHp);
	void SetAttack(const int& attack);

	const string& GetName();
	const int& GetHp();
	const int& GetMaxHp();
	const int& GetAttack();
	const bool& GetDead();

	void PrintInfo();
	virtual void Attack(Creature* other) abstract;
	void Damaged(Creature* other);
	void IsDead();
	
protected:
	string _name;
	int _hp;
	int _maxHp;
	int _attack;
	bool _isDead;
};