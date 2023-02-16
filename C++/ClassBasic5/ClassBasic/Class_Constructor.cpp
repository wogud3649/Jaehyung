#include<iostream>
#include<algorithm>
#include "Player.h"

using namespace std;

// class_Constructor
// ������, �Ҹ���

// Ŭ���� : ���赵

class Player__
{
public:
	// �⺻������
	// ȣ�� �ñ� : ������ ��
	// �ϴ� ��: �ʱ�ȭ
	// -> �Ͻ������� ȣ��Ǵ� ������
	// ������ �˾Ƽ� ���� ȣ�� (�� �ٸ� �����ڰ� �ϳ��� ������ ������ �ʴ´�.)
	Player__()
	: _maxHp(100) //���� �ʱ�ȭ ����
	{
		// ���� �ʱ�ȭ
		cout << "�⺻ ������ ȣ��" << endl;
		this->_hp = 0; // this -> �� �Լ��� ȣ���� ��ü
		_level = 0;
		_mp = 0;
		_attack = 0;
	}

	// -> ��������� �츮�� ����������Ѵ�.
	Player__(int hp)
	: _maxHp(_hp)
	{
		cout << "Ÿ�Ժ�ȯ ������ ȣ��" << endl;
		_hp = hp;
		_level = 5;
		_mp = 10;
		_attack = 0;
	}
	
	Player__(int hp, int level, int mp, int attack)
		: _hp(hp)
		, _level(level)
		, _mp(mp)
		, _attack(attack)
		, _maxHp(hp)
	{

	}

	// ���� ������
	// -> �Ͻ������� ȣ��Ǵ� ������
	Player__(const Player__& other)
	: _maxHp(other._maxHp)
	, _attack(other._attack)
	, _name(other._name)
	{
		cout << "��������� ȣ��" << endl;
		_hp = other._hp;
		_level = other._level;
		_mp = other._mp;
	}

	// �Ҹ���, �ı���
	// -> �Ͻ������� ȣ��
	~Player__()
	{
		cout << "�Ҹ��� ȣ��" << endl;
	}

	// ��� �Լ�
	void PrintInfo()
	{
		cout << "hp : " << _hp << endl;
		cout << "level : " << _level << endl;
		cout << "mp : " << _mp << endl;
	}

	// main
	// [][��ȯ�ּҰ�][k1, k2]

	int CheckHp()
	{
		return _hp;
	}
	// main						Attack
	// [][��ȯ�ּҰ�][k1, k2]	[Player p ����][��ȯ�ּҰ�][]
	void Attack(Player__* p)
	{
		if (p == nullptr)
			return;

		p->_hp -= _attack;
		cout << this->_name << "��" << p->_name << "�� �����߽��ϴ�." << endl;
	}
	void Dead()
	{
		cout << this->_name << "�� ����Ͽ����ϴ�." << endl;
	}
	
	string _name; // ���ڹ迭
protected:
	// ��� ����
	int _hp;
	int _level;
	int _mp;
	int _attack;
	const int _maxHp;
};

class Knight__ : public Player__
{
public:
	Knight__()
	{
		cout << "Knight�� ������ ȣ��" << endl;
	}

	Knight__(int hp, int level, int mp, int attack)
	// ���� �ʱ�ȭ������ �ڱ� �ڽ��� ��������� �ʱ�ȭ�� �� �ִ�.
		: Player__(hp, level, mp, attack)
	{
		_hp = hp;
		_level = level;
		_mp = mp;
		_attack = attack;
		cout << "Knight�� Ÿ�Ժ�ȯ ������ ȣ��" << endl;
	}

	~Knight__()
	{
		cout << "Knight�� �Ҹ��� ȣ��" << endl;
	}

private:

};

int main()
{
	//Player p(5);
	//p.PrintInfo();

	//Player p2(p); // Player p2 = p;
	//p2.PrintInfo();

	Knight__ k1(100, 1, 0, 10);
	k1._name = "Knight1";
	Knight__ k2(120, 1, 0, 7);
	k2._name = "Knight2";
	
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