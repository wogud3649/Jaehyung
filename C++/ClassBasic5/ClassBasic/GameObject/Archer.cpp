#include "Framework.h"

Archer::Archer()
{
}

Archer::Archer(string name, int hp, int attack)
{
}

Archer::~Archer()
{
}

void Archer::Attack(Player* player)
{
	int archerAttack = rand() % 3 + 1;

	cout << "Archer�� ����!!!" << endl;
	player->TakeDamage(_attack * archerAttack);
}
