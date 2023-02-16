#include <iostream>

using namespace std;

class Pet
{
public:
	Pet() : _hp(0), _atk(0) {}
	Pet(int hp, int atk) : _hp(hp), _atk(atk) {}
	~Pet() {}

private:
	int _hp;
	int _atk;
};

class Player
{
public:
	Player() : _hp(0), _atk(0), _pet(nullptr)
	{
		_pet = new Pet();
	}

	Player(int hp, int atk, int petHp, int petAtk)
	: _hp(hp)
	, _atk(atk)
	, _pet(new Pet(petHp, petAtk))
	{
	
	}

	// 암시적으로 생성된 복사생성자는 얕은 복사를 한다.
	Player(const Player& other)
	: _hp(other._hp)
	, _atk(other._atk)
	{
		// deep copy
		// -> 내부에서 동적할당해서 생성한다면
		// -> 복사할 때 포인터 그대로 복사하면 지울 때 에러...
		// => 새로 복사해서 생성
		_pet = new Pet(*other._pet);
	}
	~Player()
	{
		if (_pet != nullptr)
			delete _pet;
	}

	void DeletePet()
	{
		delete _pet;
		_pet = nullptr;
	}

	void CreatePet()
	{
		if (_pet == nullptr)
			_pet = new Pet();
	}
private:
	int _hp;
	int _atk;
	Pet* _pet;
};

int main()
{
	Player* p1 = new Player(100, 50, 30 ,5);
	Player* p2 = new Player();
	p2->DeletePet();
	p2->CreatePet();

	Player* p3 = new Player(*p1);

	delete p3;
	delete p2;
	delete p1;
	return 0;
}

// 디버그 3가지
// 중단점
// 조사식
// 호출스택