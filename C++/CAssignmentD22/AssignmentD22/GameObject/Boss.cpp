#include "Framework.h"

Boss::Boss()
: Monster()
{
}

Boss::Boss(string name, int hp, int attackDamage, int abilityPower, int defense, int magicResistance)
: Monster(name, hp, attackDamage, abilityPower, defense, magicResistance)
{
}

Boss::~Boss()
{
}
