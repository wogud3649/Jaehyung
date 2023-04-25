#pragma once
class Creature
{
public:
	Creature();
	virtual ~Creature();

	virtual void Update() abstract;
	virtual void Render() abstract;

protected:
	int _maxHp = 100;
	int _curHp = _maxHp;

	int _maxDamage = 15;
	int _minDamage = 5;

	bool _isAlive = false;
};

