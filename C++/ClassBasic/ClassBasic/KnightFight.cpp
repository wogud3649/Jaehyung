#include<iostream>
#include<algorithm>

using namespace std;

class Player
{
public:
	Player(int hp, int level, int mp, int attack, string name)
	: _maxHp(_hp)
	{
		_hp = hp;
		_level = level;
		_mp = mp;
		_attack = attack;
		_name = name;
	}

	void PrintInfo()
	{
		cout << "name : " << _name << endl;
		cout << "hp : " << _hp << endl;
		cout << "level : " << _level << endl;
		cout << "mp : " << _mp << endl;
	}

	int CheckHp()
	{
		return _hp;
	}

	void Attack(Player* p)
	{
		if (p == nullptr)
			return;

		p->_hp -= _attack;
		cout << this->_name << "이" << p->_name << "을 공격했습니다." << endl;
	}
	void Dead()
	{
		cout << this->_name << "이 사망하였습니다." << endl;
	}
	
protected:
	int _hp;
	int _level;
	int _mp;
	int _attack;
	const int _maxHp;
	string _name;
};

class Knight : public Player
{
public:
	Knight(int hp, int level, int mp, int attack, string name)
	: Player(hp, level, mp, attack, name)
	{
		_hp = hp;
		_level = level;
		_mp = mp;
		_attack = attack;
	}

private:

};

int main()
{
	Knight k1(100, 1, 0, 10, "Knight1");
	Knight k2(120, 1, 0, 7, "Knight2");

	while (k1.CheckHp() > 0 && k2.CheckHp() > 0)
	{
		k1.Attack(&k2);
		if (k2.CheckHp() <= 0)
		{
			k2.Dead();
			break;
		}
		k2.Attack(&k1);
		if (k1.CheckHp() <= 0)
		{
			k1.Dead();
			break;
		}
	}

	k1.PrintInfo();
	k2.PrintInfo();

	return 0;
}