#include "framework.h"

World::World()
: _player(nullptr)
{
	for (int i = 0; i < 10; i++)
	{
		_goblins[i] = nullptr;
	}
}

World::~World()
{
	delete _player;

	for (int i = 0; i < 10; i++)
	{
		delete _goblins[i];
	}
}

void World::SetTypeAndName()
{
	cout << "�̸��� �Է��� �ּ���. : ";
	cin >> _name;

	cout << "1. Knight, 2. Archer, 3. Mage" << endl;
	cout << "���ϴ� ������ ������ �ּ���. : ";
	cin >> _type;
}

void World::Init()
{
	SetTypeAndName();

	switch (_type)
	{
	case 1: 
	case 2: 
	case 3: 
	default: 
	}
}