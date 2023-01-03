#pragma once
class Creature : public enable_shared_from_this<Creature>
{
public:
	Creature();
	Creature(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance);
	virtual ~Creature();

	void SetName(string name);
	void SetHp(int hp);
	void SetAttackDamage(int attackDamage);
	void SetAbilityPower(int abilityPower);
	void SetDefense(int defense);
	void SetMagicResistance(int magicResistance);

	string GetName();
	int GetHp();
	int GetMaxHp();
	int GetAttackDamage();
	int GetAbilityPower();
	int GetDefense();
	int GetMagicResistance();
	int GetDamageTaken();
	bool IsLive();

	virtual void Attack(shared_ptr<Creature> other) abstract;
	virtual void TakeDamage(shared_ptr<Creature> other);

protected:
	string _name;
	int _hp;
	int _maxHp;
	int _attackDamage;
	int _abilityPower;
	int _defense;
	int _magicResistance;
	int _damageTaken;
	bool _isLive;
};

