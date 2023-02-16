#include "Archer.h"
#include "Pet.h"

Archer::Archer(Pet* pet) : _pet(pet)
{
	
}

Archer::Archer(int hp) : Player(hp)
{
}

Archer::~Archer()
{
	// Áñ°Å¿ü´Ù ³» Æê :(
	if (_pet != nullptr)
		delete _pet;
}

void Archer::AddHp(int value)
{
	Player::AddHp(value);

	// Á×¾úÀ¸¸é Æêµµ ³¯¸°´Ù
	if (IsDead())
	{
		delete _pet;
	}
}
