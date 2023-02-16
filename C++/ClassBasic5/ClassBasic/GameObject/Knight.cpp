#include "Framework.h"

Knight::Knight()
: Player()
, _stamina(0)
{
}

Knight::Knight(string name, int hp, int attack)
: Player(name, hp, attack)
, _stamina(0)
{
}

Knight::~Knight()
{
}

void Knight::Attack(Player* player)
{
	cout << "Knight Attack" << endl;
	if (_stamina > 0)
	{
		--_stamina;
		player->TakeDamage(_attack * 2);
	}
	else
		player->TakeDamage(_attack);
}
