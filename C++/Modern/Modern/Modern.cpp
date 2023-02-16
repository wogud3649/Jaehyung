#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

// Modern C++
// C++ 11부터~

// auto
// -> 반드시 초기화가 필요하다.
// -> 가독성이 떨어진다.
// 
// 중괄호 초기화
// -> 배열과 일반 변수 초기화하는 방법을 동일하게
// 
// 범위기반 for 문
// -> 많이 쓴다.
// 
// final override
// friend
// 
// using
// 
// enum class
// -> enum은 이름이 겹치면 컴파일에러가 난다.
// -> 이름이 겹쳐야하는 상황이면 enum class를 써야한다.
// -> 취향차이
//
// 람다
// 
// 
// 이동 shift 개념
//
// 
// 스마트 포인터
// 
// 

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

int main()
{
#pragma region auto
	// auto
	// 자료형 추론
	unordered_map<int, int> uMap;
	uMap[0] = { 1 };
	uMap[1] = 2;
	uMap[2] = 3;

	auto iter = uMap.begin();
	for (; iter != uMap.end(); ++iter)
	{
		cout << iter->first << endl;
	}
#pragma endregion
#pragma region 중괄호 초기화
	// 중괄호 초기화
	Player p = { 1, 5 };
	int arr[5] = { 1,2,3,4,5 };
#pragma endregion
#pragma region 범위기반 for문
	// 범위기반 for문
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	for (const auto& value : v)
	{
		cout << value << endl;
	}

	for (const auto& p : uMap)
	{
		cout << p.first << endl;
	}
#pragma endregion
#pragma region using
	//using
	typedef unsigned int UINT2;
	using UINT = unsigned int; // -> template 호환
	UINT t;
#pragma endregion
#pragma region enum class
	// enum class
	ClassType type = ClassType::NONE;
	int a = static_cast<int>(type);
#pragma endregion
	return 0;
}