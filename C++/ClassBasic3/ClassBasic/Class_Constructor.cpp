#include<iostream>
#include<algorithm>
#include "Player.h"

using namespace std;

// class_Constructor
// 생성자, 소멸자

// 클래스 : 설계도

class Player__
{
public:
	// 기본생성자
	// 호출 시기 : 생성할 떄
	// 하는 일: 초기화
	// -> 암시적으로 호출되는 생성자
	// 없으면 알아서 만들어서 호출 (단 다른 생성자가 하나라도 있으면 만들지 않는다.)
	Player__()
	: _maxHp(100) //빠른 초기화 지역
	{
		// 느린 초기화
		cout << "기본 생성자 호출" << endl;
		this->_hp = 0; // this -> 이 함수를 호출한 객체
		_level = 0;
		_mp = 0;
		_attack = 0;
	}

	// -> 명시적으로 우리가 정의해줘야한다.
	Player__(int hp)
	: _maxHp(_hp)
	{
		cout << "타입변환 생성자 호출" << endl;
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

	// 복사 생성자
	// -> 암시적으로 호출되는 생성자
	Player__(const Player__& other)
	: _maxHp(other._maxHp)
	, _attack(other._attack)
	, _name(other._name)
	{
		cout << "복사생성자 호출" << endl;
		_hp = other._hp;
		_level = other._level;
		_mp = other._mp;
	}

	// 소멸자, 파괴자
	// -> 암시적으로 호출
	~Player__()
	{
		cout << "소멸자 호출" << endl;
	}

	// 멤버 함수
	void PrintInfo()
	{
		cout << "hp : " << _hp << endl;
		cout << "level : " << _level << endl;
		cout << "mp : " << _mp << endl;
	}

	// main
	// [][반환주소값][k1, k2]

	int CheckHp()
	{
		return _hp;
	}
	// main						Attack
	// [][반환주소값][k1, k2]	[Player p 생성][반환주소값][]
	void Attack(Player__* p)
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
	
	string _name; // 문자배열
protected:
	// 멤버 변수
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
		cout << "Knight의 생성자 호출" << endl;
	}

	Knight__(int hp, int level, int mp, int attack)
	// 빠른 초기화에서는 자기 자신의 멤버변수만 초기화할 수 있다.
		: Player__(hp, level, mp, attack)
	{
		_hp = hp;
		_level = level;
		_mp = mp;
		_attack = attack;
		cout << "Knight의 타입변환 생성자 호출" << endl;
	}

	~Knight__()
	{
		cout << "Knight의 소멸자 호출" << endl;
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