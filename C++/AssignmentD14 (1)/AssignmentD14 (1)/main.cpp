#include "framework.h"

enum Classes
{
	NONE,
	KNIGHT,
	ARCHER,
	MAGE
};

void CreateMonsters(Creature* monsters[])
{
	for (int i = 0; i < 10; i++)
	{
		monsters[i] = new Goblin();
		monsters[i]->SetHp(rand() % 16 + 25);
		monsters[i]->SetAttack(rand() % 3 + 1);
	}
}

void DeleteMonsters(Creature* monsters[])
{
	for (int i = 0; i < 10; i++)
	{
		delete monsters[i];
		monsters[i] = nullptr;
	}
}

int main()
{
	Sound_Manager::CreateInstance();

	srand((unsigned int)time(nullptr));
	bool playerdead = false;
	int deadcount, num;
	string name;
	Creature* player = nullptr;
	Creature* monsters[10] = { nullptr };
	
	CreateMonsters(monsters);

	cout << "캐릭터의 이름을 입력해 주세요. : ";
	cin >> name;

	cout << "1. Knight, 2. Archer, 3. Mage" << endl;
	cout << "원하는 직업을 선택해 주세요. : ";
	cin >> num;

	switch (num)
	{
	case KNIGHT:
	{
		player = new Knight(name);
		break;
	}
	case ARCHER:
	{
		player = new Archer(name);
		break;
	}
	case MAGE:
	{
		player = new Mage(name);
		break;
	}
	}

	while (true)
	{
		deadcount = 0;
		for (int i = 0; i < 10; i++)
		{
			player->Attack(monsters[i]);
			monsters[i]->Damaged(player);
			if (monsters[i]->GetDead())
				deadcount++;
			else
				i--;
			for (int j = 0; j < 10; j++)
			{
				monsters[j]->Attack(player);
				player->Damaged(monsters[j]);
				if (player->GetDead())
				{
					playerdead = true;
					break;
				}
			}
			cout << endl;
			if (playerdead == true)
				break;
		}
		if (deadcount == 10)
		{
			Sound_Manager::GetInstance()->PlayerWin();
			break;
		}
		if (playerdead == true)
		{
			Sound_Manager::GetInstance()->PlayerLose();
			break;
		}
	}

	DeleteMonsters(monsters);
	delete player;
	player = nullptr;

	Sound_Manager::DeleteInstance();
	return 0;
}