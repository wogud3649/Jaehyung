#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class Player
{
public:
	friend class Pet; // -> Pet은 Player의 private 영역의 멤버함수, 멤버변수를 쓸 수 있게 된다.

	Player(int a, int b)
	{
		cout << "타입변환 생성자" << endl;
	}

	virtual void Attack() { cout << "Attack" << endl; };
private:
	int _hp;
};

class Knight : public Player
{
public:
	Knight()
	: Player(10, 5)
	{

	}
	virtual void Attack() final override { cout << "Knight Attack!" << endl; }; // 이 이상으로 override 하지 않는다.
};

class Pet
{
public:
	void Set(Player* p) { this->p = p; }
	void Act()
	{
		p->_hp = 0;
	}

private:
	Player* p;
};

enum class ClassType
{
	NONE,
	KNIGHT,
	MAGE,
	ARCHER
};

enum class PetType
{
	NONE,
	KNIGHT_PET,
	MAGE_PET,
	ARCHER_PET
};

struct AggroInfo
{
	int damage;
	Knight* knight;

	bool operator<(const AggroInfo& other)
	{
		if (damage < other.damage)
			return true;
		return false;
	}
};

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	// map/ unordered_map
	// 중복된 키값이 있으면 나중에 들어온 값을 무시함.

	vector<AggroInfo> v;
	for (int i = 0; i < 10; i++)
	{
		AggroInfo temp;
		temp.damage = rand() % 100;
		temp.knight = new Knight();
		v.push_back(temp);
	}

	std::sort(v.begin(), v.end());

	return 0;
}