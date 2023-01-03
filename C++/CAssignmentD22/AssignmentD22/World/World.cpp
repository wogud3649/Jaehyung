#include "Framework.h"

World::World()
: _bossAttackNum(0)
, _players()
, _goblinKing(nullptr)
{
	Init();
	RaidBoss();
}

World::~World()
{
}

void World::SetPlayers()
{
	_players.reserve(10);
	_players.resize(10);
	int count = 0;
	int type;
	string name;
	for (auto& player : _players)
	{
		type = rand() % 3 + 1;
		name = "Player" + to_string(++count);
		switch (type)
		{
		case KNIGHT:
		{
			player = make_shared<Knight>(name, 400 + rand() % 51, 20 + rand() % 6, 0, 40 + rand() % 6, 40 + rand() % 6);
			break;
		}
		case ARCHER:
		{
			player = make_shared<Archer>(name, 300 + rand() % 51, 30 + rand() % 6, 0, 30 + rand() % 6, 10 + rand() % 6);
			break;
		}
		case MAGE:
		{
			player = make_shared<Mage>(name, 200 + rand() % 51, 10 + rand() % 6, 40 + rand() % 6, 10 + rand() % 6, 40 + rand() % 6);
			break;
		}
		}
	}
}

void World::SetBoss()
{
	_goblinKing = make_shared<GoblinKing>("GoblinKing", 1000, 120, 0, 15, 0);
} 

void World::Init()
{
	SetPlayers();
	SetBoss();
}

void World::RaidBoss()
{
	shared_ptr<GoblinKing> dynamic_goblinKing = dynamic_pointer_cast<GoblinKing>(_goblinKing);
	while (true)
	{
		for (auto& player : _players)
		{
			if (player->IsLive())
			{
				player->Attack(_goblinKing);
				dynamic_goblinKing->TakeDamage(player);
			}
		}
		if (_goblinKing->IsLive() == false)
			break;
		cout << endl;

		dynamic_goblinKing->Attack(nullptr);
		if (dynamic_goblinKing->GetDamageTable().empty())
			break;
		for (int i = 0; i < dynamic_goblinKing->GetAttackNum(); i++)
		{
			dynamic_goblinKing->GetDamageTable()[i].first->TakeDamage(_goblinKing);
		}
		cout << endl;
	}
}