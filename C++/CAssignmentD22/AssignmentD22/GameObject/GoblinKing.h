#pragma once
class GoblinKing : public Boss
{
public:
	GoblinKing();
	GoblinKing(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance);
	~GoblinKing();

	virtual void Attack(shared_ptr<Creature> other);
	virtual void TakeDamage(shared_ptr<Creature> other);
	
	int GetAttackNum();
	vector<pair<shared_ptr<Creature>, int>>& GetDamageTable();

private:
	vector<pair<shared_ptr<Creature>, int>> _damageTable;
	int attackNum;
};