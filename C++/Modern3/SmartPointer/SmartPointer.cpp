#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

class Player
{
public:
	Player()
	: _hp(0)
	{
		cout << "플레이어 생성" << endl;
	}
	
	Player(int hp)
	: _hp(hp)
	{
		cout << "플레이어 타입생성자 호출, 생성" << endl;
	}

	~Player()
	{
		cout << "플레이어 소멸" << endl;
	}

	void Attack()
	{
		if (_target.expired() == false)
		{
			_target.lock()->_hp -= 5;
			cout << "Player Attack!" << endl;
		}
	}

public:
	int _hp = 0;

	weak_ptr<Player> _target;
};

struct RefCountBlock
{
	int refCount = 1;
};

template<typename T>
class SharedPtr
{
public:
	SharedPtr() : _block(nullptr), _ptr(nullptr) {}
	SharedPtr(T* ptr) : _block(nullptr), _ptr(ptr)
	{
		_block = new RefCountBlock();
		cout << "RefCountBlock : " << _block->refCount << endl;
	}
	SharedPtr(const SharedPtr<Player>& other)
	: _ptr(other._ptr)
	, _block(other._block)
	{
		if (_ptr != nullptr)
		{
			_block->refCount++;
			cout << "RefCount : " << _block->refCount << endl;
		}
	}
	~SharedPtr()
	{
		if (_ptr != nullptr)
		{
			_block->refCount--;
			cout << "RefCount : " << _block->refCount << endl;

			if (_block->refCount <= 0)
			{
				delete _block;
				delete _ptr;
				_ptr = nullptr;
			}
		}
	}

	SharedPtr& operator=(const SharedPtr& other)
	{
		_ptr = other._ptr;
		_block = other._block;

		if (_ptr != nullptr)
		{
			_block->refCount++;
			cout << "RefCount : " << _block->refCount << endl;
		}
		return (*this);
	}

	T* operator->()
	{
		if (_ptr != nullptr)
			return _ptr;
		return nullptr;
	}

public:
	RefCountBlock* _block;
	T* _ptr;
};

void PlayerAttack(shared_ptr<Player> p)
{
	p->Attack();
}

int main()
{
	shared_ptr<Player> player1 = make_shared<Player>(10);
	shared_ptr<Player> player2 = make_shared<Player>(5);

	player1->_target = player2;
	player2->_target = player1;

	player1->Attack();
	player2->Attack();

	// SharedPtr<Player> t = SharedPtr < Player>(new Player());
	// PlayerAttack(t);
	// shared_ptr<Player> s_ptr = make_shared<Player>();
	// s_ptr->Attack();
	// s_ptr.get()->Attack();

	// 가비지 컬렉션
	// 지울 후보들을 나중에 한번에 지운다.
	// C++ 처럼 delete 할 필요가 없음.

	// shared_ptr의 순환고리 => weak_ptr
	// player1->_target = nullptr;
	// player2->_target = nullptr;

	unique_ptr<Player> up = make_unique<Player>(100);
	up->Attack();

	vector<shared_ptr<Player>> players;

	for (int i = 0; i < 10; i++)
	{
		shared_ptr<Player> temp = make_shared<Player>(i * 5);
		players.push_back(temp);
	}

	unordered_map<int, shared_ptr<Player>> playerMap;

	int count = 0;
	for (auto ptr : players)
	{
		pair<int, shared_ptr<Player>> temp(count, ptr);
		playerMap.insert(temp);
		count++;
	}

	// players를 정렬하는데 hp가 높은 순으로 정렬해주세요
	std::sort(players.begin(), players.end(), [](const shared_ptr<Player>& a, const shared_ptr<Player>& b)->bool
		{
			if (a->_hp > b->_hp)
				return true;
			return false;
		});

	return 0;
}